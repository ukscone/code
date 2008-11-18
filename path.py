def find(p1, p2, depth, length = 0, path = []):
    """Prints out all paths of a given length between given points.  
    Points are only allowed to be visited once."""
    
    if abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]) > depth - length:
        return 0
        
    if p1 in path:
        return 0
        
    if length  == depth and p1 == p2:
        path.append(p1)
        print path
        return 1
    
    path.append(p1)
    
    count = 0
    
    count += find([p1[0] + 1, p1[1]], p2, depth, length + 1, path[:])
    count += find([p1[0] - 1, p1[1]], p2, depth, length + 1, path[:])
    count += find([p1[0], p1[1] + 1], p2, depth, length + 1, path[:])
    count += find([p1[0], p1[1] - 1], p2, depth, length + 1, path[:])
    
    return count
    
if __name__ == "__main__":
    print find([0, 0], [2, 1], 7)
