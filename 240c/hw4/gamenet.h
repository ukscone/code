//******************************************************************************
// Author: 			Jonathan Plona
// Course: 			CS240C, Professor Dolan
// Description: 	This is the header file for the GameNet class.  This class
//					provides basic networking functionality for the game class.
//					A connection can be opened in client mode or server mode, 
//					and then strings can be send and recieved.  All methods
//					return true on success and false on failure.
// Date:  			Tuesday, May 27, 2008
//******************************************************************************

#ifndef GAMENET_H
#define GAMENET_H

#include <string>
#include <strings.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class GameNet {
	
 public:
 	//Open as a server.
	bool open(int port);
	//Open as a client.
	bool open(std::string host, int port);

	bool read_move(std::string& move);

	bool send_move(std::string move);
	
 private:
	int sock_fd, new_sock_fd;  			//Socket file descriptors.
	socklen_t client_length;
	sockaddr_in serv_addr, cli_addr;	//Server/client addresses.
	hostent* server;
	
	char buffer[256];					//Read buffer.
};
#endif
