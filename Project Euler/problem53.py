factorial = [1]
fact = 1
for x in xrange(1, 101):
    fact *= x
    factorial.append(fact)
    
def choose(n, r):
    return factorial[n]/(factorial[n - r]*factorial[r])
    
count = 0
for x in xrange(1, 101):
    for y in xrange(1, x + 1):
        if choose(x, y) > 1000000:
            count += 1

print count
