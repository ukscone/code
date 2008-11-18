from sieve import *

primebits = sieve(1000000)
primes = []
primesums = []

for x in xrange(1000000):
    if primebits[x] == 0:
        primes.append(x)
        
limit = len(primes)/2
max = 0

for x in xrange(limit):
    sum = 0
    count = 0
    for y in xrange(x, limit):
        sum += primes[y]
        count += 1
        if sum > 999999: break
        if primebits[sum] == 0:
            primesums.append((sum, count))
            if count > max: max = count
    if limit - x < max: break
    print x
    
print 'out'
    
for (x, y) in primesums:
    if y == max: print x
