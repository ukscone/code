from math import sqrt

current = 1
add = 2

def numdivisors(num):
    target = num
    count = 0
    test = 1
    while test < target:
        if num % test == 0:
            if test == sqrt(num): count += 1
            else: count += 2
            target = num / test
        test += 1
    return count
    
while numdivisors(current) <= 500:
    current += add
    add += 1
    if add % 10000 == 0:
        print current, add, numdivisors(current)
    
print current, add
