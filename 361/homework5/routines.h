#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#include "GraphAlgorithms.h"

using namespace std;

bool in_list(const list<pair<int,int> > &my_list, pair<int,int> my_pair);

bool in_list(const list<pair<int,int> > &my_list, int v);

int val_in_list(const list<pair<int,int> > &my_list, int v);

bool s_tree(const vector<list<pair<int,int> > > &adj_list,
	    const vector<int> &tree, int source);

int s_tree_val(const vector<list<pair<int,int> > > &adj_list,
	    const vector<int> &tree, int source);

bool symmetric(const vector<list<pair<int,int> > > &adj_list);

void read_graph(istream &in, vector<list<pair<int,int> > > & adj_list);
