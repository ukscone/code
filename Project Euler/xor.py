data = [[int(entry) for entry in line.split(",")] for line in open('cipher1.txt', 'r')][0]

out = open('cipherout.txt', 'w')
x = 0
for a in xrange(97, 123):
 for b in xrange(97, 123):
  for c in xrange(97, 123):
    if x == 4423:
        key = [a, b, c] * (len(data)/3 + 1)
    
        out.write(''.join([chr(data[x] ^ key[x]) for x in xrange(len(data))]) + '\n')
    x += 1
