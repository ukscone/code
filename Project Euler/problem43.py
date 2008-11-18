from permute import permutations

primes = [2, 3, 5, 7, 11, 13, 17]

def isananswer(p):
    for x in xrange(7):
        if int(p[x + 1: x + 4]) % primes[x] != 0: 
            return False
    return True
    
print isananswer("1406357289")

shortpans = permutations("123456789")
pans = []
for x in shortpans:
    for y in xrange(8):
        new = x[:]
        new.insert(y + 1, '0')
        pans.append(new)
        
pans = [''.join(pan) for pan in pans]

print "weeding"

results = [int(pan) for pan in pans if isananswer(pan)]
        
print sum(results)
