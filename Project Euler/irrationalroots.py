from decimal import *

setcontext(Context(prec=105, traps=[Overflow, DivisionByZero, InvalidOperation]))

def sumOfDigits(x):
    total = 0
    x = str(x)[:101]
    
    for y in x:
        if y != '.':
            total += int(y)
    
    return total

total = 0

for x in xrange(1, 100):
    x = Decimal(x)
    x = x.sqrt()
    if x % 1:
        total += sumOfDigits(x)

print total        
