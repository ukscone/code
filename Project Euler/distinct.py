from sievebool import sieve

prime = sieve(1000000)
primes = [x for x in xrange(len(prime)) if prime[x]]

def primefactorset(n):
    factors = set()
    for x in primes:
        if x > n/2:
            break
        if not n % x:
            factors.add(x)
    return factors
   
def istheanswer(x):
    if len(primefactorset(x)) != 4:
        return False
    if len(primefactorset(x+1)) != 4:
        return False
    if len(primefactorset(x+2)) != 4:
        return False
    if len(primefactorset(x+3)) != 4:
        return False
    return True
    
x = 1
while not istheanswer(x):
    x += 1

print x
