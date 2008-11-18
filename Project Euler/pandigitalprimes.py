from sieve import sieve

def ispandigital(x):
    numstring = str(x)
    length = len(numstring)
    if len(set(numstring)) < length: return False
    for x in xrange(length):
        if int(numstring[x]) > length or numstring[x] == '0': return False
    return True

primes = sieve(7654321)

pandigital = set()

for x in xrange(len(primes)):
    if primes[x] == 0 and ispandigital(x):
        pandigital.add(x)
        
print max(pandigital)
