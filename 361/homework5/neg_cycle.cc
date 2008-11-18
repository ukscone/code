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

  cout << "Program syntax:  neg_edge < test_case.inp " << endl;

  GraphAlgorithms my_ga;
  vector<list<pair<int,int> > > adj_list;

  vector<list<int> > paths;
  read_graph(cin,adj_list);

  if (my_ga.new_cycle(adj_list)) {   // You need to complete this

    cout << "Graph size = " << adj_list.size() << endl;
    cout << "A negative Edge weight cycle exists in the graph" << endl;

  } else {
    cout << "No negative edge weight cycle exists in the graph" << endl;
    cout << "Graph size = " << adj_list.size() << endl;
    
  }

}
