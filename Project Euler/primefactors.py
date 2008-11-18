from sievebool import sieve

prime = sieve(1000000)
primes = [x for x in xrange(len(prime)) if prime[x]]

def primefactors(n):
    if n in primes:
        return {n: 1}
    factors = {}
    target = n
    for x in primes:
        if x > target:
            break
        mult = 0
        if not n % x:
            while not n % x:
                mult += 1
                n /= x
            factors[x] = mult
    return factors
