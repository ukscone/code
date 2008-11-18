#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <set>

#include "Time.h"
#include "Node.h"

using namespace std;

//Read a directory listing.
void parse_listing(ifstream& fin, list<pair<string,Time> >& dir_table) {
	string line;
	while (!fin.eof()) {
		getline(fin,line);
		if (!fin.fail()) {
			istringstream in(line);
		  
		  	//Ignore permissions, id, owner, group, size.
			string ignore;
			for(int i = 0; i < 5; ++i) in >> ignore;

			//Read modification time.
			string year_day, time_string;
			in >> year_day;
			in >> time_string;

			unsigned int index = time_string.find(".");

			string hour_time;
			string sub_sec;
			if (index == string::npos) {
				cerr << "Error reading directory listing." << endl
					 << "Exiting..." << endl;
				exit(1);
			}
			else {
				hour_time = time_string.substr(0,index);
				sub_sec = time_string.substr(index);
			}
			//Ignore offset.
			in >> ignore;
	  		
	  		//Read filename.
			string filename;
			in >> filename;
			
			//Add to directory table.
			try {
				dir_table.push_back(make_pair(filename,Time(year_day+" "+hour_time)));
			} catch (int) {
				cerr << "Error reading directory listing." << endl
					 << "Exiting..." << endl;
				exit(1);
			}
		}
	}
}

//Read a makefile.
void parse_makefile(ifstream& fin, map<string, Node*>& nodes, list<pair<string, string> >& dep_rules) {
	set<string> targets;
	string line;
	while(!fin.eof()) {
		getline(fin, line);
		if(!fin.fail()) {
			//Read in the target.
			unsigned int index = line.find(":");
			if(index == string::npos) {
				cerr << "Error reading makefile." << endl
					 << "Exiting..." << endl;
				exit(1);
			}
			string target = line.substr(0, index);
			//Check for duplicate rules.
			if(targets.find(target) == targets.end()) {
				nodes[target] = new Node(target);
				targets.insert(target);
			}
			else {
				cerr << "Error: Duplicate rule." << endl
					 << "Exiting..." << endl;
				exit(1);
			}
			
			//Read in the dependencies.
			line = line.substr(index + 1);
			istringstream deps(line);			
			string dep;			
			while(deps >> dep) {
				if(nodes.find(dep) == nodes.end()) nodes[dep] = new Node(dep);
				dep_rules.push_back(pair<string, string>(target, dep)); 	
			}
			//Read in compilation command.
			//Note: command line must start with a tab character.
			getline(fin, line);
			if(line[0] != '\t') {
				cerr << "Error reading makefile." << endl
					 << "Exiting..." << endl;
				exit(1);
			}
			nodes[target]->command = line.substr(1);
		}
	}
}

//Detect "roots" of a dependency graph.
void detect_roots(map<string, Node*> nodes, set<Node*>& roots) {
	//Insert all nodes into roots.
	for(map<string, Node*>::iterator p = nodes.begin(); p != nodes.end(); ++p) {
		roots.insert(p->second);
	}
	//For each node, remove its dependencies from roots.
	//The nodes which are left are not depended upon.
	for(map<string, Node*>::iterator p = nodes.begin(); p != nodes.end(); ++p) 
	for(set<Node*>::iterator r = p->second->children.begin(); r != p->second->children.end(); ++r) {
		roots.erase(*r);
	}
}

//Detect dircular dependencies.
bool detect_cycles(set<Node*> roots) {
	//An empty graph has no cycles.
	if(roots.size() == 0) return false;
	//Detection follows a depth-first search as follows:
	//Set the current node as visited.
	//If any child node is already visited, then we have a cycle.
	//Otherwise visit each child node.
	//Un-visit the current node.
	for(set<Node*>::iterator p = roots.begin(); p != roots.end(); ++p) {
		if((*p)->visited == true) return true;
		(*p)->visited = true;
		if(detect_cycles((*p)->children)) return true;
		(*p)->visited = false;
	}
	return false;
}

//Detect which file need to be recompiled.
bool recompile(set<Node*> roots, Node* parent) {
	//If the caller node is a leaf, check to see if it needs to be built.
	if(roots.size() == 0) {
		if(parent->creation_time.raw_time() == 0) return true;
		else return false;
	}
	//Otherwise, loop through its children
	bool ret = false;
	for(set<Node*>::iterator p = roots.begin(); p != roots.end(); ++p) {
		//If the child needs to be recompiled, so does the parent.
		if((*p)->recompile || recompile((*p)->children, *p)) {
			ret = true;
			if(!(*p)->recompile && (*p)->command != "") cout << (*p)->command << endl;
			//Make sure target has an associated rule if file doesn't already exist
			else if((*p)->command == "") {
				cerr << "Error: no rule for " << (*p)->filename << endl
					 << "Exiting..." << endl;
				exit(1);
			}
			(*p)->recompile = true;
		}
		//If the child node is newer than the parent, the parent needs to be recompiled.
		if((*p)->creation_time > parent->creation_time) ret = true;
	}
	return ret;
}

int main(int argc, char *argv[]) {  
	//Check for proper arguments.
	if (argc!=3) {
		cerr << "Usage:" << endl 
			 << argv[0] << " makefile listing "<< endl;
		exit(1);
	}

	//Open files.
	ifstream fin1;
	ifstream fin2;

	fin1.open(argv[1]);
	if (fin1.fail()) {
		cerr << "Failed to open " << argv[1] << endl
			 << "Exiting..." << endl;
		exit(-1);
	}
	fin2.open(argv[2]);
	if (fin2.fail()) {
		cerr << "Failed to open " << argv[2] << endl
			 << "Exiting..." << endl;
	}

	//Read files.
	list<pair<string, Time> > dir_table;
	map<string, Node*> nodes;
	list<pair<string, string> > dep_rules;
	
	parse_listing(fin2, dir_table); 
	parse_makefile(fin1, nodes, dep_rules);
	
	//Assign times to nodes.
	for(list<pair<string, Time> >::iterator p = dir_table.begin(); p != dir_table.end(); ++p) {
		if(nodes.find(p->first) != nodes.end()) nodes[p->first]->creation_time = p->second;
	}
	
	//Assign dependencies to nodes.
	for(list<pair<string, string> >::iterator p = dep_rules.begin(); p != dep_rules.end(); ++p) {
		nodes[p->first]->children.insert(nodes[p->second]);
	}
	
	//Populate the set of "roots".
	set<Node*> roots;
	detect_roots(nodes, roots);
	
	//If a circular dependency is detected, exit.
	if(roots.size() == 0 || detect_cycles(roots)) {
		cerr << "Circular dependency detected." << endl
			 << "Exiting..." << endl;
		exit(1);
	}
	
	//Output compilation comands, if any.
	Node* temp = new Node();
	temp->creation_time = Time();
	if(!recompile(roots, temp)) cerr << "Nothing to do." << endl <<  "Exiting..." << endl;
}
