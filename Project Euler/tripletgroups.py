from pythagoreantriplet import findtriplets

triplets = findtriplets(1000)

repeats = {}

for triplet in triplets:
    p = sum(triplet)
    
    if p < 1000:
        if p in repeats:
            repeats[p] += 1
        else:
            repeats[p] = 1
        
maxreps = max(repeats.values())

for x in repeats.keys():
    if repeats[x] == maxreps:
        print x
        break
