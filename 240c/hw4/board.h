//******************************************************************************
// Author: 			Jonathan Plona
// Course: 			CS240C, Professor Dolan
// Description: 	This is the header file for the Board class.  The pieces are
//					stored on the screen itself, or rather in the memory that
//					curses provides to simulate the screen.  This memory is
//					separate from the screen, so it isn't affected by any 
//					outside changes	that might affect the screen itself.
// Date:  			Tuesday, May 27, 2008
//******************************************************************************

#ifndef BOARD_H
#define BOARD_H

#include <curses.h>
#include <cassert>

class Board {

 public:
 	//CONSTRUCTORS
 	Board(int y_pos, int x_pos);
 	Board(const Board& other);
 	~Board();
 	
 	//Possible piece states.
 	enum PIECE {EMPTY, WHITE, BLACK};
 	
 	//Set and get piece state at a given (0-indexed) location 
 	void set_at(int x, int y, PIECE p);
 	PIECE get_at(int x, int y);
 	
 	//Refresh the board.
 	void board_refresh();
 	
 	//Move the board.
 	void move_board(int y_pos, int x_pos);
 	
 	int get_stable_white() {return stable_white;}
 	int get_stable_black() {return stable_black;} 	
 	int get_frontier_white() {return frontier_white;}
 	int get_frontier_black() {return frontier_black;} 
 	
 private:
 	WINDOW* table; //The whole table.
 	WINDOW* board; //Just the 8x8 board.
 	
 	PIECE teh_board[8][8];
 	
 	chtype black, white; //Which character to use for each color.
 
 	int width, height;
 	int x_scale, y_scale;
 	
 	int stable_white, stable_black;
 	int frontier_white, frontier_black;
 	
 	void update_frontier_counts();
 	
 	void update_stable_discs();
 	void update_stable_counts();
 	bool is_unstable(int x, int y);
 	bool is_frontier(int x, int y);
 	
 	bool inside_board(int x, int y) const;
 	
 	bool stable[8][8];
 	
 	void init_board();
 	void init_table();
};
#endif
