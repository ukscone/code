def catprod(n):
    x = ''
    y = 1
    prods = set()
    while len(x) <= 9:
        x += str(n*y)
        y += 1
        prods.add(x)
    
    return set(item for item in prods if len(item) == 9 and '0' not in item)

     
def ispandigital19(x):
    if len(set(x)) == 9: return True
    return False
    
pans = set()
    
for x in xrange(1, 9999):
    catprods = catprod(x)
    for y in catprods:
        if ispandigital19(y):
            pans.add(y)
    print x

print max(pans)
