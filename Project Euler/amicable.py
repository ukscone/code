from getdivisors import getdivisors

def sumofdivisors(x):
    return sum(getdivisors(x))
    
checked = [0] * 10000
pairs = []

for x in xrange(10000):
    print x
    if checked[x] == 0:
        y = sumofdivisors(x)
        if y < 9999: checked[y] = 1
        if x == sumofdivisors(y):
            pairs.append((x, y))

sum = 0
            
for x, y in pairs:
    if x != y:
        if x < 10000:
            sum += x
        if y < 10000:
            sum += y
    
print sum
