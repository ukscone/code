def find(p1, p2, depth, length = 0, path = []):
    """assumes infinite grid in all directions"""
    
    if abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]) > depth - length:
        return 0
        
    if length  == depth and p1 == p2:
        return 1
    
    path.append(p1)
    count = 0
    
    count += find([p1[0] + 1, p1[1]], p2, depth, length + 1, path)
    count += find([p1[0] - 1, p1[1]], p2, depth, length + 1, path)
    count += find([p1[0], p1[1] + 1], p2, depth, length + 1, path)
    count += find([p1[0], p1[1] - 1], p2, depth, length + 1, path)
    
    return count
    
if __name__ == "__main__":
    print find([0, 0], [2, 1], 5)
