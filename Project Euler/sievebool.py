def sieve(limit):
    prime = [True] * limit
    
    prime[0] = prime[1] = False
    
    for x in xrange(4, limit, 2):
        prime[x] = False

    for x in xrange(3, limit, 2):
        if prime[x] == True:
            for y in xrange(x*2, limit, x):
                prime[y] = False

    return prime
