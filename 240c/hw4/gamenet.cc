//******************************************************************************
// Author: 			Jonathan Plona
// Course: 			CS240C, Professor Dolan
// Description: 	Implementation file for the GameNet class.
// Date:  			Tuesday, May 27, 2008
//******************************************************************************

#include "gamenet.h"

bool GameNet::open(int port) {
	client_length = sizeof(cli_addr);
	
	//Get socket.
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) return 0;
    
    //Set server information
    bzero((char *) &serv_addr, sizeof(serv_addr)); 
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	
	//Bind.
	int n = bind(sock_fd, (sockaddr*) &serv_addr, sizeof(serv_addr)); 
	if(n < 0) return false;
	        
	//Listen.
	listen(sock_fd, 0); 
	//Accept.
	new_sock_fd = accept(sock_fd, (sockaddr*) &cli_addr, &client_length); 
	if (new_sock_fd < 0) return false;
	return true;
}

bool GameNet::open(std::string host, int port) {
	//Get socket.
    new_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (new_sock_fd < 0) return false;
    
    server = gethostbyname(host.c_str());
    if (server == NULL) return false;
    
    //Set server information.
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);
    
    //Connect.
    int n = connect(new_sock_fd, (sockaddr*)&serv_addr, sizeof(serv_addr));
    if(n < 0) return false;
    
    return true;
}

bool GameNet::read_move(std::string& move) {
	bzero(buffer, 256);
	int n = read(new_sock_fd,buffer, 255);
	move = buffer;
	if(n < 0) return false;
	return true;
}

bool GameNet::send_move(std::string move) {
	int n = write(new_sock_fd, move.c_str(), move.size());
	if (n < 0) return false;
	return true;
}
