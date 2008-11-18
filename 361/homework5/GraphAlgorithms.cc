//****************************************************************************
// This is a start on HW #5.
//***************************************************
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include "GraphAlgorithms.h"

#include "routines.h"

class w_edge {
 public:
 	w_edge(int x, int y, int z) : u(x), v(y), weight(z) {}
	int u;
	int v;
	int weight;
};

bool operator > (const w_edge &e1, const w_edge &e2) {
	return e1.weight > e2.weight;
}
bool operator == (const w_edge& e1, const w_edge& e2) {
	return (e1.u == e2.u) && (e1.v == e2.v) && (e1.weight == e2.weight);
}
bool operator != (const w_edge& e1, const w_edge& e2) {
	return !(e1 == e2);
}

ostream& operator << (ostream& o, const w_edge &e) {
	o << "(" << e.u << ", " << e.v << ", " << e.weight << ")";
	return o;
}

int choose(const vector<int> & dist, const vector<bool> & Q);


#include <queue>

vector<int> GraphAlgorithms::mst(const vector<list<pair<int, int> > > &adj_list, int v) {
	vector<int> parents(adj_list.size());
	
	vector<bool> in_tree(adj_list.size(), false);\
	
	priority_queue<w_edge, vector<w_edge>, greater<w_edge> > fringe;
	fringe.push(w_edge(-1, 0, -1));
	
	while(!fringe.empty()) 
		if(!in_tree[fringe.top().v]) {
			w_edge to_add = fringe.top(); fringe.pop();
			parents[to_add.v] = to_add.u;
			in_tree[to_add.v] = true;
			
			for(list<pair<int, int> >::const_iterator p = adj_list[to_add.v].begin(); p != adj_list[to_add.v].end(); ++p) 
				if(!in_tree[p->first]) fringe.push(w_edge(to_add.v, p->first, p->second));
		}
		else fringe.pop();
	
	return parents;
}



vector<int> GraphAlgorithms::shortest_path(const vector<list<pair<int,int> > > &adj_list, int v) {
	vector<int> parent(adj_list.size(), -1);
	vector<int> distance(adj_list.size(), INT_MAX);
	vector<bool> Q(adj_list.size(), true);
	distance[v] = 0;
	int current;
	
	while(find(Q.begin(), Q.end(), true) != Q.end()) {
		current = choose(distance, Q);
		Q[current] = false;
		int new_dist;
		for(list<pair<int, int> >::const_iterator p = adj_list[current].begin(); p != adj_list[current].end(); ++p) {
			new_dist = distance[current] + p->second;
			if(new_dist < distance[p->first]) {
				distance[p->first] = new_dist;
				parent[p->first] = current;
			}
		}
	}
	
	return parent;
}

bool GraphAlgorithms::new_cycle(const vector<list<pair<int,int> > > &adj_list) {
	vector<int> distance(adj_list.size(), INT_MAX);
	distance[0] = 0;
	
	for(int i = 0; i < adj_list.size(); ++i) {
		for(int j = 0; j < adj_list.size(); ++j)
		for(list<pair<int, int> >::const_iterator p = adj_list[j].begin(); p != adj_list[j].end(); ++p) {
			if(distance[j] != INT_MAX && distance[p->first] > distance[j] + p->second) {
				distance[p->first] = distance[j] + p->second;
			}
		}
	}
	
	for(int j = 0; j < adj_list.size(); ++j)
	for(list<pair<int, int> >::const_iterator p = adj_list[j].begin(); p != adj_list[j].end(); ++p) {
		if(distance[p->first] > distance[j] + p->second) return true;
	}
	
	return false;
}

/*******************************************************************/
/* Some useful routines */

int choose(const vector<int> & dist, const vector<bool> & Q) {
	int min = INT_MAX;
	int min_index = 0;
	for (int i=0;i<dist.size();i++) {
		if (Q[i]) {
			if (min > dist[i]) {
				min = dist[i];
				min_index = i;
			}
		}
	}
	return min_index;
}

