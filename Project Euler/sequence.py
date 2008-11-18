def lenseq(seed):

    def next(n):
        if n % 2 == 0: return n/2
        else: return 3*n + 1
        
    x = seed
    count = 0
        
    while x != 1:
        x = next(x)
        count += 1
        
    return count
    
if __name__ == '__main__':
    length = []
    for x in range(1, 1000000):
        length.append(lenseq(x))
    print length.index(max(length)) + 1
