def rotations(instr):
    if not type(instr) == list:
        instr = list(str(instr))
    
    allrots = [str(''.join(instr))]
    
    for x in xrange(len(instr) - 1):
        instr.insert(0, instr[-1])
        instr = instr[:-1]
        allrots.append(''.join(instr))
    
    return allrots
