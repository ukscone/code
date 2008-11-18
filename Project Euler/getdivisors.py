from math import sqrt

def getdivisors(num):
    target = num
    divisors = [1]
    test = 2
    while test < target:
        if num % test == 0:
            divisors.append(test)
            if test != sqrt(num): 
                divisors.append(num / test)
            target = num / test
        test += 1
    return divisors
