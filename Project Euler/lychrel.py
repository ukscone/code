def reverse(x):
    return int(str(x)[::-1])
    
def ispalindrome(n):
    number = str(n)
    limit = len(number)
    for x in xrange(limit/2):
        if number[x] != number[limit - x - 1]:
            return False
    return True    
        
count = 0
for x in xrange(1, 10000):
    a = x
    lychrel = True
    for y in xrange(50):
        b = reverse(a)
        if ispalindrome(a + b):
            lychrel = False
            break
        a += b
    if lychrel: count += 1
    print x
    
print count
