//******************************************************************************
// Author: 			Jonathan Plona
// Course: 			CS240C, Professor Dolan
// Description: 	Implementation file for the Reversi class.
// Date:  			Tuesday, May 27, 2008
//******************************************************************************

#include "reversi.h"

#define BLACK Board::BLACK
#define WHITE Board::WHITE
#define EMPTY Board::EMPTY
#define PIECE Board::PIECE
using namespace std;

Reversi::Reversi() {			
	is_copy = false;
	pass_count = 0;
	black_score = 2;
	white_score = 2;
}

Reversi::Reversi(const Reversi& other) {
	board = new Board(*(other.board));
	is_copy = true;
	pass_count = other.pass_count;
	black_score = other.black_score;
	white_score = other.white_score;
}

Reversi::~Reversi() {delete board; if(!is_copy) endwin();}

game* Reversi::clone() const {
	game* copy = new Reversi(*this);	
	return copy;
}

void Reversi::init() {
	initscr();						//Enter curses mode.
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	curs_set(0);					//Hide cursor.
	refresh();	
	
	board = new Board(1, 2);		//Setup board.
	board->board_refresh();
	display_msg("REVERSI", 0, 17);
	
	//Local game or network game?
	display_msg("Would you like to play a network game? ", LINES - 1, 0);
	char ans[80];
	echo();
	getstr(ans);
	noecho();
	if(ans[0] == 'y' || ans[0] == 'Y') init_network_game();	
	else set_player_types(COMPUTER, COMPUTER);
}

void Reversi::init_network_game() {	
	//Server mode or client mode?
	display_msg("Are you the server? ", LINES - 1, 0);
	char ans[80];
	echo();
	getstr(ans);
	noecho();
	
	//SERVER
	if(ans[0] == 'y' || ans[0] == 'Y') {
		//Try to open server every ten seconds until it succeeds.
		bool status = false;
		while(!status) {
			display_msg("Waiting for client to connect...", LINES - 1, 0);
			status = open_net(8888);
			if(!status) {
				display_msg("Error setting up server. Retrying in 10 seconds.", LINES - 1, 0);
				sleep(10);
			}
		}
		set_player_types(COMPUTER, NET);
	}
	//CLIENT
	else {
		//Allow user to re-enter the IP address if the connection fails.
		bool connected = false;
		while(!connected) {
			display_msg("Please enter the IP address of the server: ", LINES - 1, 0);
			char ans[80];
			echo();
			getstr(ans);
			noecho();
			connected = open_net(string(ans), 8888);
			if(!connected) {
				display_message("Error connecting to server.");
			}
		}
		set_player_types(NET, COMPUTER);
	}
	display_msg("", LINES - 1, 0); //Clear line.
}

void Reversi::display_message(const string& message) const {
	display_msg(message, LINES - 2, 0);
}

void Reversi::display_msg(const std::string& message, int y, int x) const {
	if(!is_copy) { //If this is an AI copy, don't display any messages.
		move(y, x);
		clrtoeol();
		mvprintw(y, x, message.c_str());
		refresh();
	}
}

string Reversi::get_user_move() const {
	//Ask the user for a move.
	display_msg(next_color() == BLACK ? "Black" : "White", LINES - 1, 0);
	display_msg("'s move: ", LINES - 1, 5);
	char move[80] = {0};
	echo();
	//Loop while no move is entered.
	while(move[0] == 0) {
		move[0] = 0;
		mvgetstr(LINES - 1, 14, move);
	}
	noecho();
	display_msg("", LINES - 1, 0); //Clear line.
	return string(move);
}

void Reversi::make_move(const string& _move) {
	if(_move.substr(0, 4) != "pass") /*player made a move*/ {
		//Extract coordinates from move.
		int x = _move[0] - 97;
		int y = _move[1] - 49;
		board->set_at(x, y, next_color());
		increment_score(false);
	
		//Flip all necessary pieces.
		vector< pair<int, int> > flip_vecs = flip_vectors(x, y);
		for(unsigned int i = 0; i < flip_vecs.size(); ++i) {
			int dx = flip_vecs[i].first;
			int dy = flip_vecs[i].second;
			
			while(board->get_at(x + dx, y + dy) == last_color()) {
				board->set_at(x + dx, y + dy, next_color());
				increment_score(true);
				dx += flip_vecs[i].first;
				dy += flip_vecs[i].second;
			}
		}
		
		if(!is_copy) {
			display_message(""); //Clear line.
		}
		pass_count = 0;	//Reset pass count.
	}
	else /*player passed*/ {
		if(!is_copy) {
			display_message(string(next_color() == BLACK ? "Black" : "White") + string(" passes"));
		}
		++pass_count;
	}
	
	game::make_move(_move); //Increments move_number.
}

void Reversi::display_status() const {	
	//Show score.
	mvprintw(LINES - 3, 10, "Black: %d  White: %d ", board->get_stable_black(), board->get_stable_white());
	
	//Refresh the board.
	board->board_refresh();
	refresh();
	
	if(is_game_over()) {
		//Display endgame information.
		display_message(string("Game Over - ") + string(white_score == black_score ? "Nobody" : black_score > white_score ? "Black" : "White") + string(" wins"));
		board->board_refresh();
		getch();
	}
}

bool Reversi::is_legal(const string& move) const {
	if(move.substr(0, 4) == "pass" && !has_legal_move()) return true;
	int x = move[0] - 97;
	int y = move[1] - 49;
	if(!inside_board(x, y)) return false; 			//Out of board.
	if(board->get_at(x, y) != EMPTY) return false; 	//Already filled.
	if(!flip_vectors(x, y).empty()) return true;	//Doesn't flip any pieces.
	return false;
}

bool Reversi::is_game_over() const {
	//If neither player has a move, or the board is filled, the game is over.
	return (white_score*black_score == 0 || pass_count == 2 || black_score + white_score == 64);
}

bool Reversi::inside_board(int x, int y) const {
	if(x < 0 || x > 7 || y < 0 || y > 7) return false;
	return true;
}

vector< pair<int, int> > Reversi::flip_vectors(int x, int y) const {
	//Find the directions in which pieces would be flipped by a move (x, y)
	vector< pair<int, int> > vecs;
	for(int dx = -1; dx <= 1; ++dx) 
	for(int dy = -1; dy <= 1; ++dy) {
		if(dx == 0 && dy == 0) continue;
		if(inside_board(x + dx, y + dy) && board->get_at(x + dx, y + dy) == last_color()) {
			int dx2 = dx; 
			int dy2 = dy;
			while(inside_board(x + dx2, y + dy2) && board->get_at(x + dx2, y + dy2) == last_color()) {
				dx2 += dx;
				dy2 += dy;
			}
			if(inside_board(x + dx2, y + dy2) && board->get_at(x + dx2, y + dy2) == next_color()) 
				vecs.push_back(pair<int, int>(dx, dy));
		}
	}
	
	return vecs;
}

bool Reversi::has_legal_move() const {
	std::queue<string> moves;
	compute_moves(moves);
	return !moves.empty();
}

void Reversi::compute_moves(std::queue<string>& moves) const {
	//Compute all legal moves.
	for(int x = 0; x < 8; ++x) {
	for(int y = 0; y < 8; ++y) {
		string move = "";
		move += (char)(x + 97);
		move += (char)(y + 49);
		if(is_legal(move)) moves.push(move);
	}
	}
}

int Reversi::evaluate() const { //White is the maximizing player.
	if(is_game_over()) return white_score > black_score ? INT_MAX : INT_MIN + 1;
	else return 50*(board->get_stable_white() - board->get_stable_black()) + 10*(board->get_frontier_black() - board->get_frontier_white());
}

void Reversi::increment_score(bool flip) {
	//Update the score.
	if(next_color() == BLACK) {
		if(flip) --white_score;
		++black_score;
	}
	else {
		if(flip) --black_score;
		++white_score;
	}
}
