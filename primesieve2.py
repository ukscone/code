def primesieve2(limit):
    
    composite = [4, 6]
    primes = []
        
    for current in range(3, limit, 2):
        if current not in composite:
            primes.append(current)
            for x in range(current, limit/current + 1):
                composite.append(current*x)
               
    return [2] + primes
