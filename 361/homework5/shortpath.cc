#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#include "GraphAlgorithms.h"

#include "routines.h"


using namespace std;

main() {

	cout << "Program syntax:	shortpath < test_case.inp " << endl;

	GraphAlgorithms my_ga;
	
	int source = 0;
	
	vector<list<pair<int,int> > > adj_list;
	read_graph(cin,adj_list);

	vector<int> predecessor;
	predecessor = my_ga.shortest_path(adj_list, source);	

	for (int i=0; i<adj_list.size(); i++) {
		bool first = true;
		int current = i;
		int sum = 0;
		
		while(current != source) {
			if(in_list(adj_list[predecessor[current]], current)) 
				sum += val_in_list(adj_list[predecessor[current]], current);
			else 
				cout << "Error! " << " edge " << predecessor[current] <<"->" << current << "not in graph" << endl;
			current = predecessor[current];
		}
		
		cout << "Shortest path to vertex " << i << " has length =" << sum <<endl;
	}
}
