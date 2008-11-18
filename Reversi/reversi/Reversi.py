# Reversi.py - (c) 2001 Brent Burley
# Permission granted for any use.  No warranty.  Enough said.
from Tkinter import *
import random, re

# Constants
GridSize = 50 # size in pixels of each square on playing board
PieceSize = GridSize - 8 # size in pixels of each playing piece
Offset = 2 # offset in pixels of board from edge of canvas
BoardColor = '#008000' # color of board - medium green
HiliteColor = '#00a000' # color of highlighted square - light green
PlayerColors = ('', '#000000', '#ffffff') # rgb values for black, white
PlayerNames = ('', 'Black', 'White') # Names of players as displayed to the user
Compass = ((-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1))
	  # eight compass directions as (dx, dy)
MoveDelay = 1000 # pause 1000 msec (1 sec) between moves

class BoardState:
    '''Holds one state of the board.
       getPlayer() and getPieces() return information about the state.
       getMoves() computes legal moves that can be made from this state.
    '''
    def __init__(self, boardstate=None):
        "Creates a new board state.  If a board state is supplied, it is copied"
        if boardstate:
            # copy an existing board state
            self._pieces = boardstate._pieces.copy()
            self._open = boardstate._open.copy()
            self._player = boardstate._player
            self._passed = boardstate._passed
        else:
            # create a new board state
            # Note: x goes from 0 to 7, y goes from 0 to 7
            # _pieces is a list of pieces on the board; _pieces[x,y] = player no: 1 or 2
            # this is the opening state - 2 pieces for each player in center of board
            self._pieces = {(3,3):2,(3,4):1,(4,3):1,(4,4):2} 
            # _open is a list of open spaces next to occupied spaces
            # it is used to narrow the search space for legal moves
            # _open[x,y] = 1 means space is open
            self._open = {(2,2):1,(2,3):1,(2,4):1,(2,5):1,
                          (3,2):1,                (3,5):1,
                          (4,2):1,                (4,5):1,
                          (5,2):1,(5,3):1,(5,4):1,(5,5):1}
            self._player = 1 # black always starts first
            self._passed = 0 # indicates if last player passed (for determing game over)
    def getPlayer(self):
        "Returns player whose turn it is"
        return self._player
    def getPieces(self):
        "Returns current pieces on board as dictionary: pieces[x,y] = player"
        return self._pieces
    def getMoves(self):
        '''Returns a list of valid next moves and board states.
           Each item is (x,y,newBoardState). x,y in range 0-7.
           If the only legal move is a pass, there will be one entry with x=y=None.
           If there is no legal move (game over), the list will be empty.
        '''
        result = []
        # examine open spaces for legal moves
        for x,y in self._open.keys():
            boardState = self._placePiece(x, y)
            if boardState: result.append((x,y,boardState))
        if not result:
            # no moves found, game might be over
            if self._passed:
                # last player already passed, indicate game over
                return ()
            # copy board state, set state to passed, and change players
            boardState = BoardState(self)
            boardState._passed = 1
            boardState._changePlayers()
            result.append((None, None, boardState))
        return result
        # remove new piece from open space list
        del newboard._open[x,y]
        # add new open spaces surrounding piece
    def _placePiece(self, x, y):
        # Tries to place a piece at given location.  Returns new BoardState if legal.
        newboard = None
        player = self._player
        # check every direction for pieces to flip
        for dx,dy in Compass:
            tx = x + dx; ty = y + dy # (tx, ty) is the testing location
            # count number of flippable pieces in this direction
            flipcount = 0
            while 1:
                c = self._pieces.get((tx, ty))
                if c is None: flipcount = 0; break # found a blank square, stop looking
                if c == player: break # found another one of our pieces, stop looking
                flipcount = flipcount + 1
                tx = tx + dx; ty = ty + dy # advance test pointer
            if flipcount:
                # we found some pieces to flip, make a new board state
                if not newboard:
                    newboard = self._getNewBoard(x, y)
                    newboard._passed = 0
                for i in range(flipcount):
                    # walk backwards for last test position and flip pieces
                    tx = tx - dx; ty = ty - dy
                    newboard._pieces[tx,ty] = player
        return newboard
    def _getNewBoard(self, x, y):
        # Builds a new board from current one and updates pieces and open spaces
        # copy current board state
        newboard = BoardState(self)
        # add new piece
        newboard._pieces[x,y] = self._player
        # remove new piece from open space list
        del newboard._open[x,y]
        # add new open spaces surrounding piece
        for dx,dy in Compass:
            tx = x + dx; ty = y + dy
            if not newboard._pieces.get((tx, ty)):
                # space is open, add it to open list (unless it's off the edge!)
                if tx >= 0 and tx <= 7 and ty >= 0 and ty <= 7:
                    newboard._open[tx, ty] = 1
        # make it the other player's turn
        newboard._changePlayers()
        return newboard
    def _changePlayers(self):
        # Changes to the other player's turn
        if self._player == 1: self._player = 2
        else:                 self._player = 1

    
class Board:
    "Holds the Tk GUI and the current board state"
    class Square:
        "Holds data related to a square of the board"
        def __init__(self, x, y):
            self.x, self.y = x, y # location of square (in range 0-7)
            self.player = 0 # number of player occupying square
            self.squareId = 0 # canvas id of rectangle
            self.pieceId = 0 # canvas id of circle

    def __init__(self, strategies=()):
        '''Initialize the interactive game board.  An optional list of
           computer opponent strategies can be supplied which will be
           displayed in a menu to the user.
        '''
        # create a Tk frame to hold the gui
        self._frame = Frame()
        # set the window title
        self._frame.master.wm_title('Reversi')
        # build the board on a Tk drawing canvas
        size = 8*GridSize # make room for 8x8 squares
        self._canvas = Canvas(self._frame, width=size, height=size)
        self._canvas.pack()
        # add button for starting game
        self._menuFrame = Frame(self._frame)
        self._menuFrame.pack(expand=Y, fill=X)
        self._newGameButton = Button(self._menuFrame, text='New Game', command=self._newGame)
        self._newGameButton.pack(side=LEFT, padx=5)
        Label(self._menuFrame).pack(side=LEFT, expand=Y, fill=X)
        # add menus for choosing player strategies
        self._strategies = {} # strategies, indexed by name
        optionMenuArgs = [self._menuFrame, 0, 'Human']
        for s in strategies:
            name = s.getName()
            optionMenuArgs.append(name)
            self._strategies[name] = s
        self._strategyVars = [0] # dummy entry so strategy indexes match player numbers
        # make an menu for each player
        for n in (1,2):
            label = Label(self._menuFrame, anchor=E, text='%s:' % PlayerNames[n])
            label.pack(side=LEFT, padx=10)
            var = StringVar(); var.set('Human')
            var.trace('w', self._strategyMenuCallback)
            self._strategyVars.append(var)
            optionMenuArgs[1] = var
            menu = apply(OptionMenu, optionMenuArgs)
            menu.pack(side=LEFT)
        # add a label for showing the status
        self._status = Label(self._frame, relief=SUNKEN, anchor=W)
        self._status.pack(expand=Y, fill=X)
        # map the frame in the main Tk window
        self._frame.pack()

        # track the board state
        self._squares = {} # Squares indexed by (x,y)
        self._enabledSpaces = () # list of valid moves as returned by BoardState.getmoves()
        for x in range(8):
            for y in range(8):
                square = self._squares[x,y] = Board.Square(x,y)
                x0 = x * GridSize + Offset
                y0 = y * GridSize + Offset
                square.squareId = self._canvas.create_rectangle(x0, y0,
                                                                x0+GridSize, y0+GridSize,
                                                                fill=BoardColor)

        # _afterId tracks the current 'after' proc so it can be cancelled if needed
        self._afterId = 0

        # ready to go - start a new game!
        self._newGame()

    def play(self):
        'Play the game! (this is the only public method)'
        self._frame.mainloop()

    def _postStatus(self, text):
        # updates the status line text
        self._status['text'] = text

    def _strategyMenuCallback(self, *args):
        # this is called when one of the player strategies is changed.
        # _updateBoard will keep everything in sync
        self._updateBoard()

    def _newGame(self):
        # delete existing pieces
        for s in self._squares.values():
            if s.pieceId:
                self._canvas.delete(s.pieceId)
                s.pieceId = 0
        # create a new board state and display it
        self._state = BoardState()
        self._updateBoard()

    def _updateBoard(self):
        # cancel 'after' proc, if any
        if self._afterId:
            self._frame.after_cancel(self._afterId)
            self._afterId = 0
        # reset any enabled spaces
        self._disableSpaces()
        # update canvas display to match current state
        for pos, player in self._state.getPieces().items():
            square = self._squares[pos]
            if square.pieceId:
                if square.player != player:
                    self._canvas.itemconfigure(square.pieceId, fill=PlayerColors[player])
            else:
                x,y = pos
                x0 = x * GridSize + Offset + 4
                y0 = y * GridSize + Offset + 4
                square.pieceId = self._canvas.create_oval(x0, y0,
                                                          x0 + PieceSize, y0 + PieceSize,
                                                          fill=PlayerColors[player])
        # prepare for next move, either human or ai
        player = self._state.getPlayer()
        moves = self._state.getMoves()
        # check for game over
        if not moves:
            self._gameOver()
            return
        # check for a pass
        if len(moves) == 1 and moves[0][0] == None:
            # must pass - do it now
            self._state = moves[0][2]
            moves = self._state.getMoves()
            if not moves:
                self._gameOver()
                return
            # prepend status message with passed message
            passedText = PlayerNames[player] + ' must pass - '
            # update player
            player = self._state.getPlayer()
        else:
            # player can't pass
            passedText = ''
    
        # get strategy (if not human)
        ai = self._strategies.get(self._strategyVars[player].get())
        if ai:
            # ai: we have to schedule the ai to run
            self._postStatus(passedText + "%s (%s) is thinking" % \
                             (ai.getName(), PlayerNames[player]))
            self._afterId = self._frame.after_idle(self._processAi, ai, moves)
        else:
            # human: just enable legal moves and wait for a click
            self._postStatus(passedText + PlayerNames[player] + "'s turn")
            self._enabledSpaces = self._state.getMoves()
            self._enableSpaces()

    def _processAi(self, ai, moves):
        # calls the strategy to determine next move
        if len(moves) == 1:
            # only one choice, don't both calling strategy
            self._state = moves[0][2]
        else:
            # call strategy
            x,y,boardstate = ai.getNextMove(self._state.getPlayer(), moves)
            self._state = boardstate
        self._afterId = self._frame.after(MoveDelay, self._updateBoard)

    def _enableSpaces(self):
        # make spaces active where a legal move is possible (only used for human players)
        for x,y,bs in self._enabledSpaces:
            if x == -1: break
            id = self._squares[x,y].squareId
            self._canvas.tag_bind(id, '<ButtonPress>',
                                  lambda e, s=self, x=x, y=y, bs=bs: s._selectSpace(bs))
            self._canvas.tag_bind(id, '<Enter>',
                                  lambda e, c=self._canvas, id=id: \
                                  c.itemconfigure(id, fill=HiliteColor))
            self._canvas.tag_bind(id, '<Leave>',
                                  lambda e, c=self._canvas, id=id: \
                                  c.itemconfigure(id, fill=BoardColor))
    
    def _disableSpaces(self):
        # remove event handlers for all enabled spaces
        for x,y,bs in self._enabledSpaces:
            if x == -1: break
            id = self._squares[x,y].squareId
            self._canvas.tag_unbind(id, '<ButtonPress>')
            self._canvas.tag_unbind(id, '<Enter>')
            self._canvas.tag_unbind(id, '<Leave>')
            self._canvas.itemconfigure(id, fill=BoardColor)
        self._enabledSpaces = ()

    def _selectSpace(self, bs):
        # this is called when a human clicks on a space to place a piece
        self._state = bs # the new board state was pre-computed, just use it
        self._updateBoard()

    def _gameOver(self):
        # the game is over.  Count up the pieces and declare the winner.
        count = [0,0,0] # first entry is a dummy
        for player in self._state.getPieces().values():
            count[player] = count[player] + 1
        self._postStatus('Game Over,  %s: %d  -  %s: %d' % \
                         (PlayerNames[1], count[1], PlayerNames[2], count[2]))

class Strategy:
    # This is a base class for implementing strategies
    def getName(self):
        "Returns the name of the strategy for displaying to the user."
        try:
            # return name if we have one
            return self._name
        except AttributeError:
            # determine name from class name
            classname = str(self.__class__) # get class name as 'module.class'
            m = re.search(r'\.(.+)$', classname) # strip module name from classname
            if m: self._name = m.group(1)
            else: self._name = 'AI'
            return self._name
    def getNextMove(self, player, moves):
        '''Determines next move from list of available moves.
           Derived classes must implement this.

           player is the current player.  moves is a list of valid
           moves where each item is (x,y,boardState).
           This routine must return one of the moves from moves.  

           Note: if there is only one valid move (or no move in the case of a pass),
           this routine will not be called and the move will be made automatically.
        '''
        raise Exception, "Invalid Strategy class, getNextMove not implemented"

class Random(Strategy):
    def getNextMove(self, player, moves):
        # just pick a move randomly
        move = moves[random.randint(0, len(moves)-1)]
        return move

class Greedy(Strategy):
    def getNextMove(self, player, moves):
        # check every move and pick the one with the most pieces belonging to player
        bestMove = None
        bestCount = -1
        for move in moves:
            x,y,bs = move
            pieces = bs.getPieces()
            count = 0
            for piece in pieces.values():
                if piece == player: count = count + 1
            if count > bestCount:
                bestCount = count
                bestMove = move
        return bestMove

if __name__ == '__main__':
    # create a new game board with the desired strategies
    strategies = (Random(),Greedy())
    board = Board(strategies)
    board.play()
