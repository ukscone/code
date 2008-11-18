//******************************************************************************
// Author: 			Jonathan Plona
// Course: 			CS240C, Professor Dolan
// Description: 	Implementation for the Board class.
// Date:  			Tuesday, May 27, 2008
//******************************************************************************

#include "board.h"

Board::Board(int y_pos, int x_pos) {
	x_scale = 4;
 	y_scale = 2;
 	width = 8*x_scale + 1;
 	height = 8*y_scale + 1;
 	
 	frontier_white = frontier_black = stable_white = stable_black = 0;
 	
 	white = '+';
 	black = ACS_DIAMOND;
 	
 	for(int x = 0; x < 8; ++x)
		for(int y = 0; y < 8; ++y) {
			stable[x][y] = false;
			teh_board[x][y] = EMPTY;
		}
 	
 	//Create table.
 	table = newwin(height + 3, width + 4, y_pos, x_pos); 
 	init_table();
 	
 	//Create board as a subwindow of table.
	board = derwin(table, height, width, 2, 2); 
	init_board();
	
	syncok(board, TRUE);
}

Board::Board(const Board& other) { //Copy constructor
	x_scale = other.x_scale;
	y_scale = other.y_scale;
	width = other.width;
	height = other.height;
	black = other.black;
	white = other.white;
	
	table = dupwin(other.table);
	board = dupwin(other.board);
	
	for(int x = 0; x < 8; ++x)
		for(int y = 0; y < 8; ++y) {
			stable[x][y] = other.stable[x][y];
			teh_board[x][y] = other.teh_board[x][y];
	}
}

Board::~Board() {delwin(board); delwin(table);}

void Board::init_table() {
	box(table, 0, 0);
	char lets[] = "abcdefgh";
	char nums[] = "12345678";
	
	for(int i = 0; i < 8; ++i) {
		mvwaddch(table, 3 + i*y_scale, 1, nums[i]);
		mvwaddch(table, 1, 4 + i*x_scale, lets[i]);
	}
}

void Board::init_board() {
	//Draw the border.
	box(board, 0, 0);
	//Draw the checkerboard.
	for(int i = 1; i < 8; ++i) {
		mvwaddch(board, height - 1, i*x_scale, ACS_BTEE);
		mvwaddch(board, i*y_scale, 0, ACS_LTEE);
		mvwaddch(board, 0, i*x_scale, ACS_TTEE);
		mvwaddch(board, i*y_scale, width - 1, ACS_RTEE);
		wmove(board, 1, i*x_scale);
		wvline(board, 0, height - 2);
		wmove(board, i*y_scale, 1);	
		whline(board, 0, width - 2);	
	}
	for(int x = 1; x < 8; ++x) {
		for(int y = 1; y < 8; ++y) {
			mvwaddch(board, y*y_scale, x*x_scale, ACS_PLUS);
		}
	}
	//Place the four initial pieces.
	set_at(3, 3, WHITE);
	set_at(4, 4, WHITE);
	set_at(3, 4, BLACK);
	set_at(4, 3, BLACK);
}

void Board::set_at(int x, int y, PIECE p) {
	assert(x < 8 && y < 8 && x >= 0 && y >=0); //Assert not outside the board.
	assert(p != Board::EMPTY);
	//Place piece
	if(p == Board::BLACK) {
		mvwaddch(board, y*y_scale + 1, x*x_scale + 2, black);
	}
	else {
		mvwaddch(board, y*y_scale + 1, x*x_scale + 2, white);
	}
	
	teh_board[x][y] = p;
	
	update_frontier_counts();
	
	update_stable_discs();
	update_stable_counts();
}
 	
Board::PIECE Board::get_at(int x, int y) {
	assert(x < 8 && y < 8 && x >= 0 && y >=0); //Assert not outside the board.
	
	return teh_board[x][y];
}
 	
void Board::board_refresh() {
	wrefresh(table); 
	wrefresh(board);
}

void Board::move_board(int y_pos, int x_pos) {
	wmove(board, y_pos, x_pos);
}

void Board::update_frontier_counts() {
	frontier_black = frontier_white = 0;
	for(int x = 0; x < 8; ++x)
	for(int y = 0; y < 8; ++y) {
		if(is_frontier(x, y)) {
			if(get_at(x, y) == BLACK) ++frontier_black;
			else ++frontier_white;
		}
	}
}

bool Board::is_frontier(int x, int y) {
	if(get_at(x, y) == EMPTY) return false;
	for(int dx = -1; dx <= 1; ++dx) 
	for(int dy = -1; dy <= 1; ++dy) {
		if(inside_board(x + dx, y + dy) && get_at(x + dx, y + dy) == EMPTY) {
			return true;
		}
	}
	return false;
}

void Board::update_stable_discs() {
	bool changed = true;
	while(changed) {
		changed = false;
		for(int x = 0; x < 8; ++x)
		for(int y = 0; y < 8; ++y) {
			if(!stable[x][y] && get_at(x, y) != EMPTY && !is_unstable(x, y)) {
				stable[x][y] = true;
				changed = true;
			}
		}
	}
}

bool Board::is_unstable(int x, int y) {
	int dy = 1;
	PIECE color = teh_board[x][y];
	PIECE other = (color == BLACK ? WHITE : BLACK);
	for(int dx = -1; dx <=1; ++dx) {
		bool emptytop = false;
		bool emptybottom = false;
		bool unstabletop = false;
		bool unstablebottom = false;
		for(int i = x + dx, j = y + dy; !emptytop && inside_board(i, j); i += dx, j += dy) {
			if(teh_board[i][j] == EMPTY) emptytop = true;
			else if(!stable[i][j] || teh_board[i][j] == other) unstabletop = true;
		}
		for(int i = x - dx, j = y - dy; !emptybottom && !(emptytop && unstablebottom) && inside_board(i, j); i -= dx, j -= dy) {
			if(teh_board[i][j] == EMPTY) emptybottom = true;
			else if(!stable[i][j] || teh_board[i][j] == other) unstablebottom = true;
		}
		if(emptytop && (emptybottom || unstablebottom)) return true;
		if(emptybottom && (emptytop || unstabletop)) return true;
	}
	
	int dx = 1;
	bool emptytop = false;
	bool emptybottom = false;
	bool unstabletop = false;
	bool unstablebottom = false;
	for(int i = x + dx; !emptytop && i < 8; i += dx) {
		if(teh_board[i][y] == EMPTY) emptytop = true;
		else if(!stable[i][y] || teh_board[i][y] == other) unstabletop = true;
	}
	for(int i = x - dx; !emptybottom && !(emptytop && unstablebottom) && i >= 0; i -= dx) {
		if(teh_board[i][y] == EMPTY) emptybottom = true;
		else if(!stable[i][y] || teh_board[i][y] == other) unstablebottom = true;
	}
	if(emptytop && (emptybottom || unstablebottom)) return true;
	if(emptybottom && (emptytop || unstabletop)) return true;
	
	return false;
}

void Board::update_stable_counts() {
	stable_black = stable_white = 0;	
	for(int x = 0; x < 8; ++x)
	for(int y = 0; y < 8; ++y) {
		if(stable[x][y]) {
			if(get_at(x, y) == BLACK) ++stable_black;
			else if(get_at(x, y) == WHITE) ++stable_white;
		}	
	}
}

bool Board::inside_board(int x, int y) const {
	if(x < 0 || x > 7 || y < 0 || y > 7) return false;
	return true;
}
