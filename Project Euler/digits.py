def isperm(n, x, y, z, a, b):
    
    stringn = str(n)
    stringx = str(x)
    stringy = str(y)
    stringz = str(z)
    stringa = str(a)
    stringb = str(b)
    
    if not (len(stringn) == len(stringx) == len(stringy) == len(stringz) == len(stringa) == len(stringb)) : return False
        
    if set(stringn) == set(stringx) == set(stringy) == set(stringz) == set(stringa) == set(stringb): return True
    else: return False
    
x = 2

while True:
    if isperm(x, 2*x, 3*x, 4*x, 5*x, 6*x): 
        print x
        break
    x += 1
