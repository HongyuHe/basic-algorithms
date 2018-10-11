/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   : dfs_backtrack.cpp
 *   Author    	: He Hongyu (Ray)
 *   Date       : 2018-10-10
 *   Description: Backtracking DFS algorithm
 *   Email		: hongyu.he@hotmail.com
 *   GitHub		: https://github.com/HongyuHe
 ================================================================*/
#include <iostream>
#include <vector>
#include <list>

using namespace std;
// This class represents a directed graph using
// adjacency list representation;
class Graph {
 public:
  Graph(int V);
  ~Graph();

  void set_adj_(int src, int dest);
  void DFS_back_track(int source); // Prints DFS_back_track traversal from a given source vertex;
 private:
  int V_;  // No. of vertices;
  list<int>* adj_; // Pointer to an array containing adjacency lists;
  vector<bool> visited_; //A vector to mark all visited vertices;
};

int main () // Driver program to test methods of graph class
{
	Graph graph(5);
	graph.set_adj_(0, 2);
	graph.set_adj_(0, 1);
	graph.set_adj_(2, 0);
	graph.set_adj_(2, 3);
	graph.set_adj_(1, 2);
	graph.set_adj_(3, 3);
	graph.set_adj_(1, 4);

	graph.DFS_back_track(0);
	cout << "End" << endl;

	return 0;
}

/*Graph*/
Graph::Graph(int V = 0) {
	V_ = V;
	adj_ = new list<int>[V];
	visited_.assign(V_, false); // Mark all the vertices as not visited
}
Graph::~Graph() {
	delete []adj_;
}

void Graph::set_adj_(int src, int dest) {
	adj_[src].push_back(dest);
}

void Graph::DFS_back_track(int source) {
	visited_.at(source) = true;
	cout << source << "→";

	for (auto vertex:adj_[source]) {
		if (!visited_.at(vertex)) {
			DFS_back_track(vertex);
		}
	}
	visited_.at(source) = false; //back track
}
