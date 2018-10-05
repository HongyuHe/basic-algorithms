/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   ：union_find_naive.cpp
 *   Author     ：He Hongyu (Ray)
 *   Date       ：2018-10-02
 *   Description：C program for a simple version of
 				  union-find algorithm(Disjoint_set)
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
// a class to represent an edge in the graph
class Graph {
 public:
  Graph(int V, int E);
  ~Graph();
  void set_edges_(int index, int src, int dest);

  void Union(int vertex_1, int vertex_2, int *joint_chain_);
  int  FindChainEnd(int *joint_chain_, int vertex);
  bool IsCycle(void);

 private:
  int V_; // V-> Number of vertices
  int E_; // E-> Number of edges
  int* joint_chain_;
  struct Edge* edges_;
};
// Driver program to test functions:
int main ()
{
    int V = 5;
    int E = 4;
    Graph graph(V, E);

    graph.set_edges_(0, 0, 1);
    graph.set_edges_(1, 1, 2);
    graph.set_edges_(2, 1, 3);
	graph.set_edges_(3, 3, 4);

    if (graph.IsCycle()) {
        cout << "graph contains cycle" << endl;
    } else {
        cout << "graph doesn't contain cycle" << endl;
    }
    return 0;
}
///////////////////////////// Graph ///////////////////////////////
Graph::Graph(int V = 0, int E = 0) {
    V_ = V;
    E_ = E;
    joint_chain_ = new int[V];
    edges_ = new struct Edge[E];

    memset (joint_chain_, -1, V * sizeof(int));	//Initialise the joint chain to -1;
}

Graph::~Graph() {
    delete []joint_chain_;
    delete []edges_;
}

void Graph::set_edges_(int index, int src, int dest) {
    edges_[index].src = src;
    edges_[index].dest = dest;
}
// A utility function to do union of two subsets
void Graph::Union(int vertex_1, int vertex_2,
	 			  int *joint_chain_) {
    int parent = FindChainEnd(joint_chain_, vertex_1);
    int child  = FindChainEnd(joint_chain_, vertex_2);

    joint_chain_[parent] = child;
}
// A utility function to find the subset of an element vertex
// joint_chain_ is a pointer of an array;
int Graph::FindChainEnd(int *joint_chain_, int vertex) {
    if (-1 == joint_chain_[vertex]) {
        return vertex;
    }
    return FindChainEnd(joint_chain_, joint_chain_[vertex]);
}
// The main function to check whether a given graph contains
// cycle or not.
// Iterate through all edges of graph, find subset of both
// vertices of every edge, if both subsets are same, then
// there is cycle in graph
bool Graph::IsCycle(void) {
    for (int i = 0; i < E_; i++) {
        int end_1 = FindChainEnd(joint_chain_, edges_[i].src);
        int end_2 = FindChainEnd(joint_chain_, edges_[i].dest);

        if (end_1 == end_2) {
            return true;
        }
        Union(end_1, end_2, joint_chain_);
    }
    return false;
}
