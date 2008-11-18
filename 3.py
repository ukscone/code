def primes(limit)

    i = 7

    primes = [2, 3, 5]

    while len(primes) <= limit:
        prime = True
        for x in primes:
            if i % x == 0: prime = False
        if prime: primes.append(i)
        i += 2

    return primes

