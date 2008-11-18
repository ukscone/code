#findpath takes a graph, a starting position, and a maximum depth
from maxpathfinder import findpath

#read in data
triangle = [[int(entry) for entry in line.split()] for line in open('triangle.txt')]

depth = 25
pos = (0, 0)
total = triangle[0][0]

while pos[0] < len(triangle) - 1:
    path = findpath(triangle, pos, maxdepth = depth)
    total += path[0] - triangle[pos[0]][pos[1]]
    pos = path[1]

print total
