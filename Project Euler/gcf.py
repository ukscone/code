def gcf(n, d):
	if d == 0:
		return n
	return gcf(d, n % d)
