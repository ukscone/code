cubes = set([125])
x = 5
digits = 3
y = 3
cube = 125
g = 1
	
def expand():
	cubes.clear()
	trackcube = cube
	trackx = x
	while len(str(trackcube)) == digits:
		cubes.add(trackcube)
		trackx += 1
		trackcube = trackx**3
	
def isperm(n, z):
	a = str(n)
	b = list(str(z))
	for x in a:
		if x in b:
			b.remove(x)
		else:
			return False
	return True
	
def numpermscube(n):
	count = 0
	for z in cubes:
		if isperm(n, z): count += 1
	return count
	
expand()
	
while g != 5:
	x += 1
	cube = x**3
	y = len(str(cube))
	if y > digits: 
		digits = y
		expand()
	cubes.add(cube)
	g = numpermscube(cube)
	print x, cube, g 

print cube
