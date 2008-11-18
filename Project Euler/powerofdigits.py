powers = [0, 1, 32, 243, 1024, 3125, 7776, 16807, 32768, 59049]

def sumOfPowers(x):
    digits = []

    while x != 0:
        digits.append(x%10)
        x /= 10
    
    total = 0    
    for x in digits:
        total += powers[x]
    
    return total



count = 0

for x in xrange(3, 1000000):
    if sumOfPowers(x) == x: count += x

print count
