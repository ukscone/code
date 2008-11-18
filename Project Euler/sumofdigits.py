def sumOfDigits(x):
    total = 0

    while x != 0:
        total += x % 10
        x /= 10
    
    return total



sums = set()

for a in xrange(100):
    for b in xrange(100):
        sums.add(sumOfDigits(a**b))
        
print max(sums)
