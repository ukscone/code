from sievebool import sieve

print "Building primes..."
primes = sieve(1000000)
primelist = []
for x in xrange(len(primes)):
    if primes[x]:
        primelist.append(x)

def istruncatableL(n):
    n = str(n)[1:]
    while n:
        if not primes[int(n)]:
            return False
        n = n[1:]
    return True
    
def istruncatableR(n):
    n /= 10
    while n > 0:
        if not primes[n]:
            return False
        n /= 10
    return True
        

count = 0
total = 0
print "Testing..."
for x in primelist:    
    if istruncatableL(x) and istruncatableR(x):
        count += 1
        total += x
        print x, count
        if count == 15:
            break
        
print total - (2 + 3 + 5 + 7)
