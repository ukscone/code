#ifndef CS361_GRAPH_ALGORITHMS
#define CS361_GRAPH_ALGORITHMS
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class GraphAlgorithms {
 public:
   

  vector<int> shortest_path(const vector<list<pair<int,int> > > &adj_list,int v);
  vector<int> mst(const vector<list<pair<int,int> > > &adj_list,int v);
  bool new_cycle(const vector<list<pair<int,int> > > &adj_list);

 private:
  // Feel Free to implement private member functions

};
#endif
