/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   : dijkstra_adjList.cpp
 *   Author    	: He Hongyu (Ray)
 *   Date       : 2018-10-18
 *   Description: C++ program for Dijkstra's shortest path algorithm for adjacency
			 	 list representation of graph
 *   Email	: hongyu.he@hotmail.com
 *   GitHub	: https://github.com/HongyuHe
 ================================================================*/

#include <unordered_set>
#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
#include <list>

using namespace std;

struct AdjNode {
  AdjNode(int dest = 0, int wt = 0);
  int index;
  int weight;
};

class CmpWeight {
 public:
  bool operator() (const struct AdjNode& a ,
	   			   const struct AdjNode& b) const {
    return a.weight > b.weight;
  }
};

class Graph {
 public:
  Graph(int V = 0);
  ~Graph();

  void set_V_(int V);
  int get_V_() const;
  void set_adjList_(int src, int dest, int weight);
  list<struct AdjNode>* get_adjList_() const;

 private:
  int V_;
  list<struct AdjNode>* adjList_; //A set of all edges;
};

typedef priority_queue<struct AdjNode,
 			vector<struct AdjNode>,
 			CmpWeight> MinHeap;
class Dijkstra {
 public:
  Dijkstra(int V = 0);
  ~Dijkstra();

  void BuidSPT(Graph* graph, int src);
  void ShowSPT() const;
 private:
  unordered_set<int>* SPT_; //Target SPT tree;
  MinHeap* minheap_; // A priority queue for selecting next path;
  vector<int>* relax_table_; // Store the current shortest path
  							// from sourse to each vertex;
};
// Driver program to test above functions;
int main ()
{
	int V = 9;
	Graph* graph = new Graph(V);
	graph->set_adjList_(0, 1, 4);
	graph->set_adjList_(0, 7, 8);
	graph->set_adjList_(1, 2, 8);
	graph->set_adjList_(1, 7, 11);
	graph->set_adjList_(2, 3, 7);
	graph->set_adjList_(2, 8, 2);
	graph->set_adjList_(2, 5, 4);
	graph->set_adjList_(3, 4, 9);
	graph->set_adjList_(3, 5, 14);
	graph->set_adjList_(4, 5, 10);
	graph->set_adjList_(5, 6, 2);
	graph->set_adjList_(6, 7, 1);
	graph->set_adjList_(6, 8, 6);
	graph->set_adjList_(7, 8, 7);

	Dijkstra* dijkstra = new Dijkstra(V);
	dijkstra->BuidSPT(graph, 0);
	dijkstra->ShowSPT();

	delete graph;
	delete dijkstra;

	return 0;
}

/*--------------------- Dijkstra -----------------------*/
Dijkstra::Dijkstra(int V) {
	SPT_ = new unordered_set<int>;
	relax_table_ = new vector<int>(V);
	minheap_ = new MinHeap();

	relax_table_->assign(V, INT_MAX);
}
Dijkstra::~Dijkstra() {
	delete SPT_;
	delete relax_table_;
	delete minheap_;
}

void Dijkstra::BuidSPT(Graph* graph, int src) {
	list<struct AdjNode>* adj = graph->get_adjList_();
	minheap_->push(AdjNode(src, 0)); // Start from source whose distance is 0;
	relax_table_->at(src) = 0;

	struct AdjNode cur_src;
	int cur_dist = 0; // The current distance
					// from where we are standing to the source;
	while (!minheap_->empty()) {
		//BFS
		cur_src = minheap_->top();
		minheap_->pop();
		//new source (next vertex) should not already in our SPT;
		if (SPT_->find(cur_src.index) != SPT_->end())
			continue;
		cout << cur_src.index << "→";
		//Add new source (next vertex) into SPT(the target tree);
		SPT_->insert(cur_src.index);
		cur_dist = relax_table_->at(cur_src.index); // Update where we are standing;

		for (auto next_v:adj[cur_src.index]) {
			int new_distance = next_v.weight + cur_dist;
			int old_distance = relax_table_->at(next_v.index);
			//Add the distance from source rather than the weight of the next edge;
			minheap_->push(AdjNode(next_v.index, new_distance));
			if (old_distance > new_distance) {
				relax_table_->at(next_v.index) = new_distance; //Relaxation;
			}
		}
	}
	cout << "End" << endl <<endl;
}

void Dijkstra::ShowSPT() const {
	cout << "Minimum distance to each vertex: " << endl;
	for (int i = 0; i < relax_table_->size(); i++) {
		cout << "("  << i << ") " << " ✈  "
			 << relax_table_->at(i) << endl;
	}
}

/*--------------------- Graph -----------------------*/
Graph::Graph(int V) {
	V_ = V;
	adjList_ = new list<struct AdjNode>[V_];
}
Graph::~Graph() {
	delete[] adjList_;
}
void Graph::set_V_(int V) {
	V_ = V;
}
int Graph::get_V_() const {
	return V_;
}
void Graph::set_adjList_(int scr, int dest, int weight) {
	adjList_[scr].push_back(AdjNode(dest, weight));	//Undirected graph;
	adjList_[dest].push_back(AdjNode(scr, weight));
}
list<struct AdjNode>* Graph::get_adjList_() const {
	return adjList_;
}

/*--------------------- AdjNode -----------------------*/
AdjNode::AdjNode(int dest, int wt) {
	index = dest;
	weight = wt;
}
