from math import sqrt

def ispent(x):
    if (1 + sqrt(1 + 24*x))/6.0 % 1 == 0:
        return True
    return False
    
def ishex(x):
    if (1 + sqrt(1 + 8*x))/4.0 % 1 == 0:
        return True
    return False

x = 280
while 1:
    tri = x*(x+1)/2
    if ispent(tri) and ishex(tri):
        print tri
        break
    x += 1
