import Reversi
class NoBrainer(Reversi.Strategy):
    def getNextMove(self, player, moves):
        return moves[0]

strategies = (Reversi.Random(),Reversi.Greedy(),NoBrainer())
board = Reversi.Board(strategies)
board.play()
