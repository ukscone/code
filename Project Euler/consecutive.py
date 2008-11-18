from sieve import *

primebits = sieve(1000000)
primes = []
sums = []
primesums = []

for x in xrange(1000000):
    if primebits[x] == 0:
        primes.append(x)

print len(primes)

for x in xrange(len(primes)/2):
    for y in xrange(x+1, len(primes)/2):
        sum = 0
        for j in xrange(x, y):
            sum += primes[j]
            if sum > 1000000:
                sum = 0
                break
        sums.append(sum)
    print x, len(primes)/2
    
print 'hi'    
  
for x in sums:
    if x in primes:
        primesums.append(x)
        
max = 0
for x in primesums:
    if x > max: max = x
