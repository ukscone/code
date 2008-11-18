def stripcrap(lines, pat):
    for line in lines:
        if pat.match(line):
            yield line[7:].strip()
        elif line != '\n':
            yield line.strip()
            
f = open("kjv12.txt")
l = (line for line in f)
import re
p = stripcrap(l, re.compile('\d{3}:\d{3}'))

for x in xrange(15):
    print p.next()
