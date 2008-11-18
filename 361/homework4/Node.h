#ifndef NODE_H
#define NODE_H

#include <string>
#include "Time.h"

using namespace std;

class Node {
	public:
		Node(string f = "") : filename(f), command(""), visited(false), 
									recompile(false), creation_time(Time()) {}
		
		string filename, command;
		
		set<Node*> children;
		bool visited, recompile;
		
		Time creation_time;
};

#endif
