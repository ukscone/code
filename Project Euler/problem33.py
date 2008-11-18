solutions = []

def false_cancel(n, d):
	n = [str(n)]
	d = [str(int(d))]
	
	cancelled = False
	for digit in n:
		if digit in d:	
			cancelled = True
			n.remove(digit)
			d.remove(digit)
	
	if not cancelled:
		return 0
	
	n = int(''.join(n))
	d = int(''.join(d))*1.0
	
	return n/d

d = 12.0

while len(solutions) < 4:
	print d, len(solutions)
	for n in xrange(10, int(d)):
		if false_cancel(n, d) == n/d:
			solutions.append((n, d))
	d += 1
			
print solutions
