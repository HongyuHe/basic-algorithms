/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   : bfs.cpp
 *   Author    	: He Hongyu (Ray)
 *   Date       : 2018-10-10
 *   Description: C++ Program to print BFS traversal from a given
				  source vertex. BFS(int s) traverses vertices
 			      reachable from s.
 *   Email		: hongyu.he@hotmail.com
 *   GitHub		: https://github.com/HongyuHe
 ================================================================*/
#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;
// This class represents a directed graph using
// adjacency list representation;
class Graph {
 public:
  Graph(int V);
  ~Graph();

  void set_adj_(int src, int dest);
  void BFS(int source); // Prints BFS traversal from a given source vertex;
 private:
  int V_;  // No. of vertices;
  list<int>* adj_; // Pointer to an array containing adjacency lists;
  queue<int> queue_; //A queue for BFS;
  vector<bool> visited_; //A vector to mark all visited vertices;
};

int main () // Driver program to test methods of graph class
{
	Graph graph(4);
	graph.set_adj_(0, 2);
	graph.set_adj_(0, 1);
	graph.set_adj_(2, 0);
	graph.set_adj_(2, 3);
	graph.set_adj_(1, 2);

	graph.BFS(0);

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

void Graph::BFS(int source) {
	queue_.push(source);
	visited_.at(source) = true;

	while (!queue_.empty()) {
		int new_src = queue_.front();
		queue_.pop(); // Dequeue a vertex from queue and print it
		cout << new_src << "→";
		// Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it;
		for (auto vertex:adj_[new_src]) {
			if (!visited_.at(vertex)) {
				visited_.at(vertex) = true;
				queue_.push(vertex);
			}
		}
	}
	cout << "End" << endl;
}
