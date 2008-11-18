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

/***********************************************************************
 * Check if my_pair is in my_list
 ***********************************************************************/
bool in_list(const list<pair<int,int> > &my_list, pair<int,int> my_pair) {
  list<pair<int,int> >::const_iterator p;
  for (p=my_list.begin();p!=my_list.end();++p) {
    if (*p == my_pair) {
      return true;
    }
  }
  return false;
}

/***********************************************************************
 * Check if v is in my_list
 ***********************************************************************/
bool in_list(const list<pair<int,int> > &my_list, int v) {
  list<pair<int,int> >::const_iterator p;
  for (p=my_list.begin();p!=my_list.end();++p) {
    if (p->first == v) {
      return true;
    }
  }
  return false;
}

/***********************************************************************
 * Check if v is in my_list; if so, return p->second, otherwise -1.
 ***********************************************************************/
int val_in_list(const list<pair<int,int> > &my_list, int v) {
  list<pair<int,int> >::const_iterator p;
  for (p=my_list.begin();p!=my_list.end();++p) {
    if (p->first == v) {
      return p->second;
    }
  }
  return -1;
}


/***********************************************************************
 * Check if "tree" is a spanning tree.
 ***********************************************************************/

bool s_tree(const vector<list<pair<int,int> > > &adj_list,
	    const vector<int> &tree, int source) {
  
  assert(adj_list.size()==tree.size());

  for (int i=0;i<tree.size();i++) {
    if (i!=source) {
      if ((0<=tree[i])&&(tree[i] <tree.size())) {
      if (!in_list(adj_list[i],tree[i])) {
	    return false;
      }
      } else {
	return false;
      }
    }
  }
  return true;
}

/***********************************************************************
 * Check if "tree" is a spanning tree; if it's, return the overall weight; otherwise return -1.
 ***********************************************************************/

int s_tree_val(const vector<list<pair<int,int> > > &adj_list,
	    const vector<int> &tree, int source) {
  assert(adj_list.size()==tree.size());
  int sum=0;
  for (int i=0;i<tree.size();i++) {
    if (i!=source) {
      if ((0<=tree[i])&&(tree[i] <tree.size())) {
      if (!in_list(adj_list[i],tree[i])) {
	    return -1;
      } else {
	sum+=val_in_list(adj_list[i],tree[i]);
      }
      } else {
	return -1;
      }
    }
  }
  return sum;
}

/***********************************************************************
 * Check the symmetry of the adjacent list
 ***********************************************************************/
bool symmetric(const vector<list<pair<int,int> > > &adj_list) {
  for (int i=0;i<adj_list.size();i++) {
    list<pair<int,int> >::const_iterator p;
    for (p=adj_list[i].begin();p!=adj_list[i].end();++p) {
      if (!in_list(adj_list[p->first],make_pair(i,p->second))) {
	//cout << "The triple  ("<< p->first <<"," << i <<"," << p->second << ") is not in the graph" << endl;
	return false;
      }
    }
  }
  return true;
}


/***********************************************************************
 * Read input graph adjacent list
 ***********************************************************************/

void read_graph(istream &in, vector<list<pair<int,int> > > & adj_list) {
  int n;
  int u,w,wt;
  if (!in.eof()) {
    in >> n;
    if (!in.fail()) {
      adj_list.resize(n);
    } else {
      // Error
      cout << "ERROR!" << endl;
      exit(-1);
    }
    while (!in.eof()) {
      string line;
      getline(in,line);
      if (!in.fail()) {
	
	// process the line
	int pos = line.find(':');
	if (pos!=string::npos) {
	  string first;
	  string second;
	  first = line.substr(0,pos-1);
	  second = line.substr(pos+1,line.length()-pos);
	  //cout << "First = " << first << " Second = " << second << endl;
	  istringstream in1(first);
	  istringstream in2(second);

	  in1 >> u;
	  if (in1.fail()) {
	    cout <<" Roger, we have a problem " << endl;
	    exit(-1);
	  }
	  while (!in2.eof()) {
	    in2 >> w;
	    if (!in2.fail()) {
	      in2 >> wt;
	      if (!in2.fail()) {
		adj_list[u].push_back(make_pair(w,wt));
	      }
	      else {
		cout << "Missing weight on line " << line << endl;
		exit(-1);
	      }
	    }
	  }
	  
 
	} else {
	  //cout << "Warning: ignoring line " << line << endl;
	  
	  //cout << "ERROR! no colon on line " << line << endl;
	  //exit(-1);
	}
      }
    }
  }
}
