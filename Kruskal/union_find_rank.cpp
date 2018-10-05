/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   ：union_find_rank.cpp
 *   Author     ：He Hongyu (Ray)
 *   Date       ：2018-10-03
 *   Description：C++ program for union-find(by rank) algorithm
 				  to detect cycle in a graph
 *   Email		: hongyu.he@hotmail.com
 *	 GitHub		: https://github.com/HongyuHe
 ================================================================*/
#include <iostream>
#include <cstring>

using namespace std;
// a structure to represent an edge in the graph
struct Edge {
  int src;
  int dest;
};
// a structure to represent an subtree for union-find
struct Subtree {
  int parent;
  int rank;
};
// a class to represent the graph
class Graph {
 public:
  Graph(int V, int E);
  ~Graph();
  void set_edges_(int index, int src, int dest);

  void Union(int subtreeA, int subtreeB, struct Subtree *ranked_tree_);
  int  FindTreeRoot(struct Subtree *ranked_tree_, int vertex);
  bool IsCycle(void);

 private:
  int V_; // V-> Number of vertices
  int E_; // E-> Number of edges
  struct Edge* edges_; // edges_ is represented as an array of edges
  struct Subtree* ranked_tree_;
};
// Driver program to test functions:
int main ()
{
    int V = 5;
    int E = 5;
    Graph graph(V, E);

    graph.set_edges_(0, 0, 1); //Add edge[0]: 0--1
    graph.set_edges_(1, 1, 2);
    graph.set_edges_(2, 1, 3);
	graph.set_edges_(3, 3, 2);
	graph.set_edges_(4, 3, 4);

    if (graph.IsCycle()) {
        cout << "graph contains cycle" << endl;
    } else {
        cout << "graph doesn't contain cycle" << endl;
    }
    return 0;
}
////////////////////////// Graph //////////////////////////////
Graph::Graph(int V = 0, int E = 0) {
    V_ = V;
    E_ = E; // Creates a graph with V vertices and E edges
    edges_ = new struct Edge[E];
	ranked_tree_ = new struct Subtree[V];

	memset(edges_, 0, sizeof(edges_));
	//Initialise every subset in the ranked tree;
    for (int i = 0; i < V; i++) {
		ranked_tree_[i].parent = i;
		ranked_tree_[i].rank = 0;
	}
}

Graph::~Graph() {
    delete []ranked_tree_;
    delete []edges_;
}

void Graph::set_edges_(int index, int src, int dest) {
    edges_[index].src = src;
    edges_[index].dest = dest;
}

// A utility function to find set of a vertex
// (uses path compression technique)
// find root and make root as parent of vertex
// then return the root;
int Graph::FindTreeRoot(struct Subtree *ranked_tree_, int vertex) {
    if (ranked_tree_[vertex].parent != vertex) { //(path compression)
        ranked_tree_[vertex].parent =
		FindTreeRoot(ranked_tree_, ranked_tree_[vertex].parent);
    }
    return ranked_tree_[vertex].parent;
}
// A function that does union of two
// Subtree of subtreeA and subtreeB (uses union by rank)
void Graph::Union(int subtreeA, int subtreeB,
	 			  struct Subtree *ranked_tree_) {
    int root_1 = FindTreeRoot(ranked_tree_, subtreeA);
    int root_2 = FindTreeRoot(ranked_tree_, subtreeB);

	if (ranked_tree_[root_1].rank > ranked_tree_[root_2].rank) {
		ranked_tree_[root_2].parent = root_1;
	} else if (ranked_tree_[root_1].rank < ranked_tree_[root_2].rank) {
		ranked_tree_[root_1].parent = root_2;
	} else { //rank_1 == rank_2
		ranked_tree_[root_2].parent = root_1;
		ranked_tree_[root_1].rank++;
	}// If ranks are same, then make one as root and increment
    // its rank by one
}
// The main function to check whether a given graph contains cycle or not
// Iterate through all edges of graph, find sets of both vertices
// of every edge, if sets are same, then there is cycle in graph.
bool Graph::IsCycle(void) {
    for (int i = 0; i < E_; i++) {
        int end_1 = FindTreeRoot(ranked_tree_, edges_[i].src);
        int end_2 = FindTreeRoot(ranked_tree_, edges_[i].dest);

        if (end_1 == end_2) {
            return true;
        }
        Union(end_1, end_2, ranked_tree_);
    }
    return false;
}
