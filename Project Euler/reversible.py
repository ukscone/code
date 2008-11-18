evens = set(['0', '2', '4', '6', '8'])

def isreversible(x):
    
    xstr = str(x)
    
    if xstr[-1] == '0': return False
    
    a = str(int(xstr[::-1]) + x)
    
    for x in a:
        if int(x) % 2 == 0 : return False
     
    return True
    
def isreversible2(x):
    
    xstr = str(x)
    
    if xstr[-1] == '0': return False
        
    a = set(str(int(xstr[::-1]) + x))
    
    for x in evens:
        if x in a: return False
        
    return True
 
#doesn't work   
def isreversible3(x):
    a = x
    y = 0
    count = len(str(x)) - 1
    if x % 10 != 0:
        while x > 0:
            y += x % 10 * 10 ** count
            x /= 10
            count -= 1
    else:
        return False
    a += y
    
    a = str(a)
    
    for x in a:
        if int(x) % 2 == 0 : return False
     
    return True
