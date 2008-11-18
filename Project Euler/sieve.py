def sieve(limit):
    marked = [0] * limit
    
    marked[0] = marked[1] = 1
    
    for x in xrange(4, limit, 2):
        marked[x] = 1

    for x in xrange(3, limit, 2):
        if marked[x] == 0:
            for y in xrange(x*2, limit, x):
                marked[y] = 1

    return marked
