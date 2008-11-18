factorial = [1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880]

def sumOfFactorials(x):
    digits = []

    while x != 0:
        digits.append(x%10)
        x /= 10
    
    total = 0    
    for x in digits:
        total += factorial[x]
    
    return total



count = 0

for x in xrange(3, 50000):
    if sumOfFactorials(x) == x: count = x

print count
