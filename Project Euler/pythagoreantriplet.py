from math import *

def findtriplets(limit):
    triplets = []
    
    for a in range(1, limit):
        for b in range(a, limit):
            c = sqrt(a**2 + b**2)
            if c % 1 == 0:
                triplets.append((a, b, int(c)))
    
    return triplets
