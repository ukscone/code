def wordval(n):
    total = 0
    for x in list(n):
        total += ord(x) - 64
    return total

names = open('/home/jonathan/Desktop/names.txt').read()

namelist = names.split('","')
namelist[0] = namelist[0][1:]
namelist[-1] = namelist[-1][:-1]

namelist.sort()

total = 0

limit = len(namelist)

for x in xrange(0, limit):
    total += ((x + 1) * wordval(namelist[x]))
    
print total
