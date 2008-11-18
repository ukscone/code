from sievebool import sieve
from itertools import ifilter

class DivisorIter():
    
    def __init__(self, n, primelist = None):
        self.number = n
        self.target = n
        self.current = 2
        if primelist:
            self.primes = primelist
        else:
            prime = sieve(n)
            self.primes = [x for x in xrange(n) if prime[x]]
        self.primeIter = ifilter(None, self.primes)
        
    def next(self):
        if self.current > self.target:
            return 0
        while self.target % self.current:
            self.current = self.primeIter.next()
        self.target /= self.current
        return self.current
