import os, sys, optparse, logging, string

DVD_SIZE = 4700000000
CD_SIZE = 736294912

def main():
    """The main function."""

    psParser = optparse.OptionParser(usage = "%prog [options] <max size>", version="Sortsize 1.0\nThis program is released under the GNU GPL v2.")
    psParser.add_option("-m", "--minimum", dest = "minimum", help = "find files of minimum SIZE bytes [default: %default]", metavar = "SIZE")
    psParser.add_option("-g", "--margin", dest = "margin", help = "leave a margin of at most SIZE bytes [default: %default]", metavar = "SIZE")
    psParser.add_option("-c", "--compatible", action = "store_true", dest = "compatible", help = "print a copy-compatible file list [default: %default]")
    psParser.add_option("-v", "--verbose", action = "store_true", dest = "verbose", help = "verbose mode [default: %default]")
    psParser.add_option("-l", "--logged", action = "store_true", dest = "logging", help = "enable logging in sortsize.log (the log is somewhat terse but does not slow the script down significantly when disabled) [default: %default]")
    psParser.add_option("-f", "--fuse", type = "int", dest = "fuse", help = "consider files with the same beginning N characters as one big file (for example \"file1\", \"file2\", \"file3\" become \"file\") [default: %default]", metavar = "N")
    psParser.add_option("-s", "--size", action = "store_true", dest = "size", help = "sort files by size instead of by name [default: %default]")
    psParser.set_defaults(minimum = "1", margin = "0", compatible = False, verbose = False, size = False, logging = False, fuse = 4)
    (opOptions, arArguments) = psParser.parse_args()

    # Check arguments
    if len(arArguments) == 1:
        intMaxSize = fnTransform(arArguments[0])
        intMinSize = fnTransform(opOptions.minimum)
        intMargin = fnTransform(opOptions.margin)
        if intMaxSize != None and intMinSize != None and intMargin != None :
            if opOptions.logging:
                logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s %(levelname)s %(message)s',
                    filename='sortsize.log',
                    filemode='w')
            # Import Psyco if available
            try:
                import psyco
                psyco.full()
            except ImportError:
                print("WARNING: Psyco not found! This script will run MUCH more slowly without it.")
            fnFind(intMaxSize, intMinSize, intMargin, opOptions.compatible, opOptions.verbose, opOptions.size, opOptions.logging, opOptions.fuse)
            if opOptions.logging: logging.shutdown()
        else:
            psParser.print_help()
    else:
        psParser.print_help()

def fnFind(intMaximum, intMinimum, intMargin, blnListFiles = False, blnVerbose = False, blnSortBySize = False, blnLogging = False, intFuse = 0):
    """Finds the combination of files that is larger than intMinimum and
    smaller than intMaximum."""
    # Retrieve a list of (filesize, filename) tuples for files with size
    # larger than intMinimum (that also excludes directories) and sort it.
    lstSizes = [(os.stat(x)[6], x) for x in os.listdir(".") if intMaximum >= os.stat(x)[6] >= intMinimum]
    if len(lstSizes) == 0:
        print("There are no suitable files here.")
        sys.exit()
    if intFuse > 0:
        lstSizes.sort(cmp=lambda x,y: cmp(x[1].lower(), y[1].lower()))
        lstFused = []
        tplPrevious = (0L, "")
        for intSize, strName in lstSizes:
            if tplPrevious[1][:intFuse].lower() == strName[:intFuse].lower():
                tplPrevious = (tplPrevious[0] + intSize, tplPrevious[1] + "\n" + strName)
            else:
                if tplPrevious[0] != 0L: lstFused.append(tplPrevious)
                tplPrevious = (intSize, strName)
        lstFused.append(tplPrevious)
        lstSizes = lstFused [:]
        del lstFused

    lstSizes.sort()

    if blnLogging: logging.debug("lstSizes = %r" % lstSizes)
    # Find the maximum number of files we can fit in the specified size.
    intCurrentSize = intMaxFiles = 0
    for intCounter in range(len(lstSizes)):
        intCurrentSize += lstSizes[intCounter][0]
        if intCurrentSize >= intMaximum:
            intMaxFiles = intCounter
            break

    del intCurrentSize

    if intMaxFiles:
        if blnVerbose: print("You can fit at most %s files in %s bytes, now to find which ones." % (intMaxFiles, fnDotify(intMaximum)))
        if blnLogging: logging.debug("Searching for up to %s files of %s bytes." % (fnDotify(intMaxFiles), fnDotify(intMaximum)))
        intMaxSize = 0
        blnFinishedAll = False

        # Optimisation.
        intFilelistLength = len(lstSizes)

        for intCounter in range(1, intMaxFiles + 1):
            if blnFinishedAll:
                print("Filled all available space.\n")
                break
            if blnVerbose: print("Checking for %s file combinations..." % intCounter)

            # Check if the total size of the current number of files is smaller than the maximum.
            intCurrentSize = 0

            for intCounter2 in range(intFilelistLength - intCounter, intFilelistLength):
                intCurrentSize += lstSizes[intCounter2][0]

            if intCurrentSize <= intMaximum:
                if intCurrentSize > intMaxSize:
                    intMaxSize = intCurrentSize
                    if blnLogging: logging.debug("New maximum size: %s of %s." % (fnDotify(intMaxSize), fnDotify(intMaximum)))
                    lstFiles = range(intFilelistLength - intCounter, intFilelistLength)
                    if intMaxSize + intMargin >= intMaximum:
                        if blnLogging: logging.debug("Ended searching with size %s of %s. lstBuffer = %r" % (fnDotify(intMaxSize), fnDotify(intMaximum), lstBuffer))
                        blnFinishedAll = True
                continue

            # Initialise the counter list with the numbers of the first n elements.
            lstBuffer = [intTemp for intTemp in range(intCounter)]
            lstCurrentSizes = [0] * intCounter
            lstCurrentSizes[0] = lstSizes[0][0]

            for intCounter2 in range(1, intCounter):
                    lstCurrentSizes[intCounter2] = lstCurrentSizes[intCounter2 - 1] + lstSizes[intCounter2][0]

            # More optimisations.
            intFirstElement = intFilelistLength - intCounter

            # Iterate.
            blnFinished = False

            while not blnFinished:
                # Determine the size of the current combination.
                if intMaximum >= lstCurrentSizes[-1] > intMaxSize:
                    intMaxSize = lstCurrentSizes[-1]
                    if blnLogging: logging.debug("New maximum size: %s of %s. lstBuffer = %r" % (fnDotify(intMaxSize), fnDotify(intMaximum), lstBuffer))
                    # Create a copy of lstBuffer, not a reference.
                    lstFiles = lstBuffer[:]
                    if intMaxSize + intMargin >= intMaximum:
                        if blnLogging: logging.debug("Ended searching with size %s of %s. lstBuffer = %r" % (fnDotify(intMaxSize), fnDotify(intMaximum), lstBuffer))
                        blnFinishedAll = True
                        break

                # Increment the list.
                blnFlag = False
                intCounterIndex = -1

                while True:
                    try:
                        # If the current file is the last in the list,
                        if lstBuffer[intCounterIndex] == intFilelistLength + intCounterIndex:
                            # Set it to -1 and go to the previous one.
                            lstBuffer[intCounterIndex] = -1
                            intCounterIndex -= 1
                            blnFlag = True
                        else:
                            # Otherwise, increment it.
                            lstBuffer[intCounterIndex] += 1
                            try:
                                # Update the current file's size.
                                lstCurrentSizes[intCounterIndex] = lstCurrentSizes[intCounterIndex - 1] + lstSizes[lstBuffer[intCounterIndex]][0]
                            except IndexError:
                                # If we get an error, it means we have reached the first file, so update that.
                                lstCurrentSizes[0] = lstSizes[lstBuffer[0]][0]
                            # If we have set something to -1,
                            if blnFlag:
                                blnFlag = False
                                # Update it and all subsequent ones.
                                for intCounter2 in range(lstBuffer.index(-1), len(lstBuffer)):
                                    # Set it to its previous plus one.
                                    lstBuffer[intCounter2] = lstBuffer[intCounter2 - 1] + 1
                                    # Update size.
                                    lstCurrentSizes[intCounter2] = lstCurrentSizes[intCounter2 - 1] + lstSizes[lstBuffer[intCounter2]][0]
                                    # If the files up to here are larger than the maximum,
                                    if lstCurrentSizes[intCounter2] > intMaximum:
                                        # Set it to the last one so that it will be incremented.
                                        lstBuffer[intCounterIndex] = intFilelistLength + intCounterIndex
                                        # Break the for loop and do another while.
                                        break
                                else:
                                    # If we are done, break the while loop.
                                    break
                            else:
                                # Otherwise, break the while loop.
                                break
                    except IndexError:
                        blnFinished = True
                        break
    else:
        if blnLogging: logging.debug("All files fit.")
        lstFiles = range(len(lstSizes))

    if blnLogging: logging.debug("Finished searching with size %s of %s. lstBuffer = %r" % (fnDotify(intMaxSize), fnDotify(intMaximum), lstBuffer))

    # Print the files
    intCurrentSize = 0
    lstFileList = []
    print "Files:"
    if blnLogging: logging.debug("lstFiles = %r" % lstFiles)
    for intIndex in lstFiles:
        lstFileList.append((lstSizes[intIndex][1], lstSizes[intIndex][0]))

    if blnSortBySize:
        lstFileList.sort(key=lambda x: x[1])
    else:
        lstFileList.sort(cmp=lambda x,y: cmp(x[0].lower(), y[0].lower()))

    for strFilename, intFilesize in lstFileList:
        if blnListFiles:
            print strFilename
        else:
            print "%s %s" % (string.join(["    " + strItem.ljust(50) for strItem in strFilename.split("\n")], "\n"), ("(" + fnDotify(intFilesize)).rjust(17) + " bytes)")
        intCurrentSize += intFilesize
    print "\nTotal: %s/%s bytes (%s%%)." % (fnDotify(intCurrentSize), fnDotify(intMaximum), str(intCurrentSize * 100 / intMaximum))

def fnTransform(strBytes):
    """Expands strings containing "g", "m", "k", "d" or "c" to their numerical counterparts."""
    strBytes = strBytes.strip()
    if strBytes[-1].lower() == "g":
        return(fnIsInt(strBytes[:-1]) * 1024 ** 3)
    elif strBytes[-1].lower() == "m":
        return(fnIsInt(strBytes[:-1]) * 1024 ** 2)
    elif strBytes[-1].lower() == "k":
        return(fnIsInt(strBytes[:-1]) * 1024)
    elif strBytes[-1].lower() == "d":
        return(fnIsInt(strBytes[:-1]) * DVD_SIZE)
    elif strBytes[-1].lower() == "c":
        return(fnIsInt(strBytes[:-1]) * CD_SIZE)
    else:
        return(fnIsInt(strBytes))

def fnDotify(intNumber):
    """Adds commas separating the thousands in numbers."""
    strNumber = str(intNumber)
    for intCounter in range(len(strNumber) - 3, 0, -3):
        strNumber = strNumber[:intCounter] + "," + strNumber[intCounter:]
    return(strNumber)

def fnIsInt(strString):
    """Checks if a number is an integer. Returns the number if it is, None
    otherwise."""
    try:
        return(int(strString))
    except ValueError:
        return(None)

main()
