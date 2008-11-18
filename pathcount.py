def numpaths(p1, p2):
    """Grid is bounded by corners p1 and p2.  p2 should be up and to the right of p2.  Only productive movements are allowed."""
    
    if p1[0] > p2[0] or p1[1] > p2[1]: return 0
    
    if p1 == p2: return 1
    
    count = 0
    
    count += numpaths((p1[0], p1[1] + 1), p2)
    count += numpaths((p1[0] + 1, p1[1]), p2)
    
    return count
