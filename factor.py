def factor(target):
    """Factors target number.  Returns a list."""

    limit = target
    test = 3

    primes = [2]
    factors = []
    
    if target <= 1: return []
    
    if target % 2 == 0:
        while limit % 2 ==0:
            limit = limit / 2
            factors.append(2)

    while test <= limit:
        prime = True
        for prime in primes:
            if test % prime == 0: prime = False
        if prime: 
            primes.append(test)
            while limit % test == 0:
                limit = limit / test
                factors.append(test)
        
        test += 2
        
    return factors
