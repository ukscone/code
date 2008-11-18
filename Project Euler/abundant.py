from math import sqrt
from getdivisors import getdivisors

limit = 28123
    
abundants = []

for x in xrange(12, limit + 1):
    if sum(getdivisors(x)) > x:
        abundants.append(x)
        
print abundants[0]
    
abundantset = set(abundants)        
targets = set()

for x in xrange(1, limit + 1):
    for y in xrange(0, len(abundants)):
        if abundants[y] < x and ((x - abundants[y]) in abundantset):
            targets.add(x)

print len(targets)
            
sums = 0            
            
for x in xrange(1, limit + 1):
    if x not in targets:
        sums += x

print sums
