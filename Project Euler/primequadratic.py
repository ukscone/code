from sievebool import sieve

primes = sieve(1000000)
primes = set([x for x in xrange(len(primes)) if primes[x]])

def lenseries(a, b):
    if b not in primes: return 0
    
    count = 0
    
    while (True):
        if count**2 + a*count + b not in primes: break
        count += 1
    return count
    
maxlength = 0

prod = 0

for a in xrange(-999, 1000):
    for b in xrange(-999, 1000):
        length = lenseries(a, b)
        if length > maxlength:
            maxlength = length
            prod = a * b
            
print prod
