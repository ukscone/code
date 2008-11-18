from gcf import gcf
from getdivisors import getdivisors

def reduced(n, d):
	gfactor = gcf(n, d)
	return (n/(d*1.0), n/gfactor, d/gfactor)

fractions = []

for d in xrange(1000000, 500000, -1):
    for n in xrange(d * 3/7 - 1, d * 3/7 + 1):
                lowestterms = reduced(n, d)
                fractions.append(lowestterms)
    print d

fractions.sort()

last = []
for x, n, d in fractions:
    if n==3 and d==7:
        print last
        break
    last = [n, d]
