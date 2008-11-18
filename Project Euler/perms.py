def findperms(p):
    """takes an iterable, returns a set of strings"""

    seen = {}

    def permute(n):
        """takes a list, string, or int, returns a list of lists"""
        
        n = list(n)
        
        #if length of subset is 1, it is its only permutation
        if len(n) == 1 or len(set(n)) == 1:
            return [n]
        
		#check if we have already computed permutations of this string before
        key = frozenset(n)
        if key in seen:
            return seen[key]            
     
        perms = []
        
        for x in n:
            sublist = n[:]
            sublist.remove(x)
            permutations = permute(sublist)[:]
            for y in permutations:
                y.insert(0, x)
                perms.append(y[:])
                
        seen[frozenset(n)] = perms[:]
        
        return perms
        
    results = permute(p)    
    for x in xrange(len(results)):
        results[x] = ''.join(results[x])
    
    return set(results)
    
if __name__ == '__main__':
	print findperms("1234")

#sets are wrong, a multiset is needed
