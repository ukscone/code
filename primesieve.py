from math import sqrt

def primesieve(limit):
    
    primelist = range(3, limit + 1, 2)
    
    x = 0
    
    while primelist[x] < sqrt(limit):
        i = primelist[x]*primelist[x]
        while i <= primelist[-1]:
            if i in primelist: primelist.remove(i)
            i += primelist[x]
        x += 1
    
    
    return [2] + primelist
