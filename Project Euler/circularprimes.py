from sievebool import sieve
from rotations import rotations

primes = sieve(1000000)
primes = set([x for x in xrange(len(primes)) if primes[x]])

def allRotationsArePrime(prime):
    for rotation in rotations(prime):
        if not int(rotation) in primes:
            return False
    return True

circular = []

for prime in primes:
    if allRotationsArePrime(prime):
        circular.append(prime)
    print prime, len(circular)
        
print len(circular)
