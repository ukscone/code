def permutations(p):
    seen = {}
    
    def permute(n):
        n = list(n)
        
        if len(n) == 1:
            return [n]
        
        key = frozenset(n)
        if key in seen:
            return seen[key]
            
        ps = []
        
        for x in n:
            sublist = n[:]
            sublist.remove(x)
            subps = permute(sublist)
            for p in subps:
                q = [x] + p 
                ps.append(q)
                
        seen[key] = ps[:]
        
        return ps[:]
        
    results = permute(p)
    
    return results
    
if __name__ == '__main__':
    print findperms("1234")
