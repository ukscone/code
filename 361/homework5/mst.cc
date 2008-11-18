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
 
  cout << "Program syntax:  mst < test_case.inp " << endl;

  GraphAlgorithms my_ga;
  vector<list<pair<int,int> > > adj_list;

  vector<list<int> > paths;
  read_graph(cin,adj_list);

  if (symmetric(adj_list)) {
    cout << "Graph is symmetric" << endl;
    vector<int> t1;

    t1 = my_ga.mst(adj_list,0);   // You need to complete this

    if (s_tree(adj_list,t1,0)) {
      cout << "This is a spanning tree" << endl;
      cout << "Cost = " << s_tree_val(adj_list,t1,0) << endl;
    } else {
      cout << "Oops --- what you computed was not a spanning tree " <<endl;
    }
    
    for (int i=0;i<t1.size();i++) {
      cout << i <<"=>" << t1[i] << endl;
    }

  } else {
    cout << "Graph is anti-symmetric" << endl;
  }


}
