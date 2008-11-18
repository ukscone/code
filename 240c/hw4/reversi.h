//******************************************************************************
// Author: 			Jonathan Plona
// Course: 			CS240C, Professor Dolan
// Description: 	This is the header file for the Reversi class.  The Reversi 
//					class uses the curses library.  Its only public methods are 
//					play(), provided by the game class, and init() which sets
//					up curses mode.  The destructor ends curses mode.
// Date:  			Tuesday, May 27, 2008
//******************************************************************************

#ifndef REVERSI_H
#define REVERSI_H

#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <curses.h>

#include "game.h"
#include "board.h"

class Reversi : public game {
 
 public:
 	//CONSTRUCTORS
 	Reversi();
 	Reversi(const Reversi& other);
 	virtual ~Reversi();
 	
 	//Initialize a reversi game.
	void init();
 	
 protected:
	// Return the color of the next player.
 	Board::PIECE next_color() const
		{return (moves_completed() % 2 == 0 ? Board::BLACK : Board::WHITE);}
	// Return the color of the last player.
	Board::PIECE last_color() const
		{return (moves_completed() % 2 == 1 ? Board::BLACK : Board::WHITE);}
		
	/*******************************************************************
 	 *						 OVERRIDDEN METHODS							*
 	 *******************************************************************/
 	// Display a message to the user.
 	virtual void display_message(const std::string& message) const;
 	// Get a move from the user.
	virtual std::string get_user_move() const;
 	// Have the next player make a specified move:
	virtual void make_move(const std::string& _move);
	// Return a pointer to a copy of myself.
	virtual game* clone() const;
    // Compute all the moves that the next player can make:
	virtual void compute_moves(std::queue<std::string>& moves) const;
	// Display the status of the current game:
	virtual void display_status() const;
	// Evaluate a board position:
	// NOTE: positive values are good for the computer.
	virtual int evaluate() const;
	// Return true if the current game is finished:
	virtual bool is_game_over() const;
	// Return true if the given move is legal for the next player:
	virtual bool is_legal(const std::string& move) const;
	
 private:
 	Board* board;
 	
 	bool is_copy;				//If this is an AI copy, don't display messages.
 	
 	int pass_count;				//Number of consecutive passes.
 	int black_score, white_score;
 	
 	// Display a message, specifying x and y coordinates.
 	void display_msg(const std::string& message, int y, int x) const;
 	// Adjust the score.
 	void increment_score(bool flip);
 	// Return true if the next player has a legal move.
 	bool has_legal_move() const;
 	// Initialize a network game.
 	void init_network_game();
 	// Return true if (x, y) is inside the board.
 	bool inside_board(int x, int y) const;
 	// Return all of the directions (in the form of unit vectors)
 	// where pieced could be flipped by a move (x, y).
	std::vector< std::pair<int, int> > flip_vectors(int x, int y) const;
};
#endif
