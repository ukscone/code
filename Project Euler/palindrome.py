def ispalindrome(n):
    number = str(n)
    limit = len(number)
    for x in xrange(limit/2):
        if number[x] != number[limit - x - 1]:
            return False
    return True
    
def binary(n):
    temp = ''
    while n > 0:
        x = n & 1
        temp += str(x)
        n /= 2
    temp = temp[::-1]
    return temp
    
pals = []
    
for x in xrange(1000000):
    if ispalindrome(x) and ispalindrome(binary(x)): pals.append(x)
    
print sum(pals)
