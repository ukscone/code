from random import randint as rand

location = 0
doubles = 0

def roll():
    global location, doubles
    die1 = rand(1, 4)
    die2 = rand(1, 4)
    if die1 == die2:
        doubles += 1
    else:
        doubles = 0
    
    location += die1 + die2
    location %= 40
    
def chanceCard():
    global location
    card = chance.pop()
    chance.insert(0, card)
    location = chanceFuncs[card](location)
    
def communityChestCard():
    global location
    card = communityChest.pop()
    communityChest.insert(0, card)
    location = chestFuncs[card](location)
    
def goToJail():
    global location
    location = 10
    
def nextRailway(loc):
    if loc == 7:
        return 15
    if loc == 22:
        return 25
    if loc == 36:
        return 5
    
def nextUtility(loc):
    if loc == 7 or loc == 36:
        return 12
    if loc == 22:
        return 28 
    
chanceSet = set([7, 22, 36])
communityChestSet = set([2, 17, 33])

communityChest = [1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
chestFuncs = [lambda x: x, lambda x: 0, lambda x: 10]

chance = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0]
chanceFuncs = [lambda x: x, lambda x: 0, lambda x: 10, lambda x: 11, lambda x: 24, lambda x: 39, lambda x: 5, nextRailway, nextRailway, nextUtility, lambda x: x-3]

turns = 0
visits = [0] * 40

while turns < 1000000:
    roll()
    
    if doubles == 3:
        goToJail()
        doubles = 0
        
    if location in chanceSet:
        chanceCard()
    if location in communityChestSet:
        communityChestCard()
    if location == 30:
        goToJail()

    visits[location] += 1
    turns += 1

print zip(visits, range(len(visits)))
visits.sort()
print visits
