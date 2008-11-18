import Reversi
class Positional(Reversi.Strategy):
    def getNextMove(self, player, moves):
        # Move to the most preferred location
        # E.g. the corners are most preferred because they can't be retaken
        #      squares next to corners are least preferred because opponent might take the corner
        #
        # dictionary of preferences
        preference = {(0,0):10, (0,1):0, (0,2):9, (0,3):8,
        (1,1):0, (1,2):3, (1,3):4, (2,2):7, (2,3):6, (3,3):5}
        bestMove = None
        bestScore = -1
        for move in moves:
            x,y,bs = move
            # rotations and reflections are similar, so reduce to just 1/8 of the board
            if x>3: x=7-x
            if y>3: y=7-y
            if x>y: x,y = y,x
            ## score this position
            score = preference[x,y]
            if score > bestScore:
                bestScore = score
                bestMove = move
        return bestMove

strategies = (Reversi.Random(),Reversi.Greedy(),Positional())
board = Reversi.Board(strategies)
board.play()
