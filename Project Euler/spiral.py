def diag1(n):
    total = 0
    for x in xrange(1, n + 1):
        if x % 2 == 0: total += x**2 + 1
        else: total += x**2
    return total
