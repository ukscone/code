x = 1
string = ''

while len(string) < 1000000:
    string += str(x)
    x += 1
    
print int(string[9]) * int(string[99]) * int(string[999]) * int(string[9999]) * int(string[99999]) * int(string[999999])
