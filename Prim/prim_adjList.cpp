/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   : dijkstra_adjList.cpp
 *   Author    	: He Hongyu (Ray)
 *   Date       : 2018-10-18
 *   Description: C++ program for Prim's MST for adjacency list
 				 representation of graph
 *   Email	: hongyu.he@hotmail.com
 *   GitHub	: https://github.com/HongyuHe
 ================================================================*/

 #include <unordered_set>
 #include <iostream>
 #include <limits.h>
 #include <utility>
 #include <vector>
 #include <queue>
 #include <list>

 using namespace std;

 struct AdjNode {
   AdjNode(int dest = 0, int wt = 0);
   int index;
   int weight;
 };

 class CmpWeight { //Utility function for priority_queue;
  public:
   bool operator() (const pair<int, struct AdjNode>& a ,
 	   			   const pair<int, struct AdjNode>& b) const {
     return get<1>(a).weight > get<1>(b).weight;
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

 typedef priority_queue< pair<int, struct AdjNode>,
  						 vector<pair<int, struct AdjNode> >,
  						 CmpWeight
						> MinHeap; //pair< source, {dest, weight} >
 class Prim {
  public:
   Prim(int V = 0);
   ~Prim();

   void BuidMST(Graph* graph, int src);

  private:
   unordered_set<int>* MST_; //Target tree;
   MinHeap* minheap_;
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

 	Prim* prim = new Prim(V);
 	prim->BuidMST(graph, 0);

	delete graph;
	delete prim;

 	return 0;
 }

 /*--------------------- Prim -----------------------*/
 Prim::Prim(int V) {
 	MST_ = new unordered_set<int>;
 	minheap_ = new MinHeap();
 }
 Prim::~Prim() {
 	delete MST_;
 	delete minheap_;
 }

 void Prim::BuidMST(Graph* graph, int src) {
 	list<struct AdjNode>* adj = graph->get_adjList_();
 	minheap_->push( make_pair(0, AdjNode(src, 0)) );

	pair<int, struct AdjNode> cur_edge;
 	struct AdjNode cur_src;
 	while (!minheap_->empty()) { //BFS
 		cur_edge = minheap_->top();
 		minheap_->pop();
		cur_src = get<1>(cur_edge);

 		//new source should not already in our MST;
 		if (MST_->find(cur_src.index) != MST_->end())
 			continue;
		MST_->insert(cur_src.index); //Add into MST(the target tree)
 		cout << "MST Edge: " << get<0>(cur_edge)
			 << "-" 		 << cur_src.index
			 << " Weight:" 	 << cur_src.weight
			 << endl;

 		for (auto vertex:adj[cur_src.index]) {
 			minheap_->push( make_pair(cur_src.index,
							  	AdjNode(vertex.index, vertex.weight)) );
 			//Add all adjent edges to priority_queue;
 			}
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
