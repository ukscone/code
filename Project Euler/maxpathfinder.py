def findpath(graph, (row, col) = (0, 0), maxdepth = -1):
    """returns (sum, (row, col))"""
    
    #Don't go past the bottom of the graph
    if len(graph) - (row + 1) < maxdepth:
        depth = len(graph) - (row + 1)
    else:
        depth = maxdepth
    
    #Base case
    if maxdepth == 0:
        return (graph[row][col], (row, col))
        
    #If maxdepth is -1, they want the whole thing
    if maxdepth == -1:
        depth = len(graph) - 1
        
    #Traverse down-left and down-right
    l = findpath(graph, (row + 1, col), depth -1)
    r = findpath(graph, (row + 1, col + 1), depth -1)
    
    if l[0] > r[0]:  return (l[0] + graph[row][col], l[1])
    else:            return (r[0] + graph[row][col], r[1])
