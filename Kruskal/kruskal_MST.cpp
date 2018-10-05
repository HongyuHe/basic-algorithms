/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   ：kruskal_MST.cpp
 *   Author     ：He Hongyu (Ray)
 *   Date       ：2018-10-05
 *   Description：C++ program for Kruskal's algorithm to find Minimum Spanning Tree
				  of a given connected, undirected and weighted graph
 *   Email		: hongyu.he@hotmail.com
 *	 GitHub		: https://github.com/HongyuHe
 ================================================================*/
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;
// a structure to represent an weighted edge in the graph
struct Edge {
  int src;
  int dest;
  int weight;
};
// a structure to represent an subtree for union-find
struct Subtree {
  int parent;
  int rank;
};
// a class to represent a connected, undirected
// and weighted graph
class Graph {
 public:
  Graph(int V, int E);
  ~Graph();

  int  get_V_(void);
  int  get_E_(void);
  struct Edge* get_edges_(void);
  void set_edges_(int index, int src, int dest, int weight);

 private:
  int V_; // V-> Number of vertices
  int E_; // E-> Number of edges
  struct Edge* edges_; // edges_ is represented as an array of edges
};

class KruskalMST {
 public:
  KruskalMST(int V);
  ~KruskalMST();

  void Union(int subtreeA, int subtreeB, struct Subtree *ranked_tree_);
  int  FindTreeRoot(struct Subtree *ranked_tree_, int vertex);
  static int  SortWeight(const void* e_1, const void* e_2);
  bool IsCycle(struct Edge* edges, int i);
  void BuidMST(Graph* graph);

 private:
  struct Subtree* ranked_tree_;	//A ranked tree for union-find-by-rank;
  struct Edge* MST_edges_; //The result;
};

// Driver program to test functions:
int main ()
{
    int V = 5;
    int E = 6;
    Graph* graph = new Graph(V, E);
	KruskalMST* kruskal = new KruskalMST(V);

    graph->set_edges_(0, 0, 1, 10);	//Add edge[0]: 0--1 (weight:10)
    graph->set_edges_(1, 1, 2, 6);
    graph->set_edges_(2, 1, 3, 5);
	graph->set_edges_(3, 3, 2, 3);
	graph->set_edges_(4, 3, 4, 15);
	graph->set_edges_(5, 1, 4, 2);

    kruskal->BuidMST(graph);

    return 0;
}
////////////////////////////// Graph /////////////////////////////////
Graph::Graph(int V = 0, int E = 0) {
    V_ = V;
    E_ = E; // Creates a graph with V vertices and E edges
    edges_ = new struct Edge[E];

	memset(edges_, 0, sizeof(edges_));
}

Graph::~Graph() {
    delete []edges_;
}

void Graph::set_edges_(int index, int src, int dest, int weight) {
    edges_[index].src = src;
    edges_[index].dest = dest;
	edges_[index].weight = weight;
}

int  Graph::get_V_(void) {
	return V_;
}
int  Graph::get_E_(void) {
	return E_;
}
struct Edge* Graph::get_edges_(void) {
	return edges_;
}

////////////////////////////// KruskalMST /////////////////////////////////
KruskalMST::KruskalMST(int V) {
	MST_edges_ = new struct Edge[V - 1];
	ranked_tree_ = new struct Subtree[V];
	//Initialise every subset in the ranked tree;
    for (int i = 0; i < V; i++) {
		ranked_tree_[i].parent = i;
		ranked_tree_[i].rank = 0;
	}
}

KruskalMST::~KruskalMST() {
	delete []MST_edges_;
    delete []ranked_tree_;
}
// A utility function to find set of a vertex
// (uses path compression technique)
// find root and make root as parent of vertex
// then return the root;
int KruskalMST::FindTreeRoot(struct Subtree *ranked_tree_, int vertex) {
    if (ranked_tree_[vertex].parent != vertex) { //(path compression)
        ranked_tree_[vertex].parent =
		FindTreeRoot(ranked_tree_, ranked_tree_[vertex].parent);
    }
    return ranked_tree_[vertex].parent;
}
// A function that does union of two
// Subtree of subtreeA and subtreeB.
// Attach smaller rank tree under root of high
// rank tree. (uses union by rank)
void KruskalMST::Union(int subtreeA, int subtreeB,
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
bool KruskalMST::IsCycle(struct Edge* edges, int i) {
    int root_1 = FindTreeRoot(ranked_tree_, edges[i].src);
    int root_2 = FindTreeRoot(ranked_tree_, edges[i].dest);

    if (root_1 == root_2) {
        return true;
    }
    Union(root_1, root_2, ranked_tree_);
    return false;
}
// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int KruskalMST::SortWeight(const void* a, const void* b) {
	struct Edge* e_1 = (struct Edge*)a;
	struct Edge* e_2 = (struct Edge*)b;
	return e_1->weight > e_2->weight;
}

// The main function to construct MST using Kruskal's algorithm
void KruskalMST::BuidMST(Graph* graph) {
	int V = graph->get_V_();
	int E = graph->get_E_();
	struct Edge* edges = graph->get_edges_();

	qsort(edges, E, sizeof(edges[0]), SortWeight);
	// ★Number of edges to be taken is equal to V-1
	for (int i = 0, j = 0; j < V - 1; i++) { // If including this edge does't cause cycle,
		if (!IsCycle(edges, i)) { // include it in result and increment the index
			MST_edges_[j++] = edges[i]; // of result for next edge
		}
	} // Else discard the next_edge

	if (0 == sizeof(MST_edges_)) {
		cout << "There is no MST in this graph!" << endl;
	} else {
		cout << "Following are the edges in the constructed MST: " << endl;
		for (int i = 0 ; i < V - 1; i++) {
			cout << MST_edges_[i].src << " — " << MST_edges_[i].dest
			 	 << " Weight:" << MST_edges_[i].weight << endl;
		}
	}
}
