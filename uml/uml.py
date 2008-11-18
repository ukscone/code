#!/usr/bin/python

from os import listdir, system, remove, chdir
import sys, getopt
from klass import Klass
from patterns import *

#pointers
#angle brackets
#template stuff

def usage():
    print """
  Usage: uml.py [OPTIONS] [PATH]

  This script supports both long and short options.
      -h, --help                       Print this message.
      -g NAME, --graphname=NAME        Specify the name of the graph.
      -t FILETYPE, --type=FILETYPE     Specify output type:
                                         svg, png, bmp, or ps. (default svg)
      -f SIZE, --fontsize=SIZE         Specify font size. (default 15)
      -w WIDTH, --width=WIDTH          Specify pen width. (default 2.0)
      -k, --keeptemps                  Keep dot and log files after processing.
                                         This is useful for manual editing
                                           after the script has run.
                                         (Type 'man dot' for instructions on
                                           processing dot files.) """
    
def main(argv):
    graphname = 'UMLDiagram'
    fontsize = 15
    penwidth = 2.0
    filetype = 'svg'
    keeptemps = False
    directory = '.'
    printfriendly = ''
    
    try:
        opts, args = getopt.getopt(argv, 'hg:t:f:w:pk', ['help', 
                'graphname=', 'type=', 'fontsize=', 'width=', 'printfriendly', 'keeptemps'])
    except getopt.GetoptError, err:
        print "uml.py: " + str(err)
        print "Try `uml.py --help' for more information."
        sys.exit(2)
    for opt, arg in opts:
        if opt in ('-h', '--help'):
            usage()
            sys.exit()
        elif opt in ('-g', '--graphname'):
            graphname = arg
        elif opt in ('-t', '--type'):
            filetype = arg
        elif opt in ('-f', '--fontsize'):
            fontsize = arg
        elif opt in ('-w', '--width'):  
            penwidth = arg
        elif opt in ('-p', '--printfriendly'):
            printfriendly = 'page="8.5,11"'
        elif opt in ('-k', '--keeptemps'):
            keeptemps = True
            
    if args:
        directory = "".join(args)
       
    try: 
        chdir(directory)
    except OSError, err:
        print "uml.py: " + str(err)
        print "Try `uml.py --help' for more information."
        sys.exit(2)

    
    klasses = []
    filenames = [f for f in listdir('.') if filepat.match(f)]

    for filename in filenames:
        f = [file for file in open(filename)]
        classes = [classpat.match(line) for line in f if classpat.match(line)]
        operations = [operpat.match(line) for line in f if operpat.match(line)]
        attributes = [attrpat.match(line) for line in f if attrpat.match(line)]
        if len(classes) > 1:
            print 'This script only supports one class per file.'
            print 'File %s contains more than one class.' % filename
            print len(classes)
        name, parents = classes[0].groups()
        parents = parents.strip()
        temp = Klass(name)
        for parent in parents.split(', '):
            parent = parent.strip().split(' ')[-1]
            temp.add_parent(parent)
        for match in operations:
                g = match.groups()
                temp.add_operation(g[1], g[2], g[3])
        for match in attributes:
                g = match.groups()
                temp.add_attribute(g[0], g[1])
        klasses.append(temp)
                
    prepstring = 'digraph %s {\n\tfontsize = %s\n\trankdir = BT\n\t%s\n\n\t' % (graphname, fontsize, printfriendly) +\
                 'node [\n\t\tfontsize = %s\n\t\tshape = "record"\n\t]\n\n\t' % fontsize +\
                 'edge [\n\t\tpenwidth = %s\n\t\tarrowhead = "empty"\n\t]\n\n' % penwidth
    endstring = '}'

    out = open('temp.dot', 'w')
    try:
        out.write(prepstring)
        for klass in klasses:
            out.write('\n' + klass.uml_out() + '\n')
        for klass in klasses:
            out.write(klass.parents_out() + '\n')
        out.write(endstring)
    finally:
        out.close()
        
    system('dot -T%s -o %s.%s temp.dot > temp.log' % (filetype, graphname, filetype))
    if not keeptemps: 
        remove('temp.dot')
        remove('temp.log')

if __name__ == "__main__":
    main(sys.argv[1:])
