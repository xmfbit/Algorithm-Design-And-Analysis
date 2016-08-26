// prim algorithm for MST(miuimum spanning tree)
// a greedy algorithm 
// add the mimimum cost edge into MST 
#include <iostream>  // for std::cout 
#include <fstream>   // for std::ifstream
#include <vector>    
#include <string>  
#include <algorithm>  // for std::sort
#include <cassert>    // for assert
#include <queue>      // for priority_queue
#include <set>        // for std::set
#include <functional>   
using namespace std;

const string input_file = "./edges.txt";

struct Edge {
	int from;     // start point
	int to;       // end point
	int weight;   // weight
	Edge() {}
	Edge(int from, int to, int weight):from(from), to(to), weight(weight) {}
};

// edge comperator
// E1 < E2 <=> E1.weight < E2.weight
// to sort the edges by weight
struct EdgeComperator {
public:
	bool operator()(const Edge& e1, const Edge& e2) const {
		return e1.weight > e2.weight;   // to construct a min-heap
	}
};

class Graph {
public:
	explicit Graph(int v): edges(v) {}
	int getVerticeNumber() const { return edges.size(); }
	int getEdgeNumber() const {
		int cnt = 0;
		for(const auto& e : edges) {
			cnt += e.size();
		}
		return cnt;
	}
	// return the edges whose vertex index is 'idx'
	const vector<Edge>& getEdges(int idx) const { return edges[idx]; }
	// add an edge (from->to) to the graph
	void addEdge(int from, int to, int weight) {
		edges[from].push_back(Edge(from, to, weight));
	}
private:
	vector<vector<Edge>> edges;
};


Graph readGraphFromFile(const string& input_file_name) {
	ifstream reader(input_file_name.c_str());
	int vertice_number, edge_number;
	reader >> vertice_number >> edge_number;
	Graph g(vertice_number);
	int from, to, weight;
	while(reader >> from >> to >> weight) {
		assert(from < to);
		// for an undirected graph, add (u->v) and (v->u) at the same time
		g.addEdge(from - 1, to - 1, weight);
		g.addEdge(to - 1, from - 1, weight);
	}
	assert(g.getVerticeNumber() == vertice_number);
	assert(g.getEdgeNumber() == edge_number * 2);
	return g;
}

// return a vector containing the edges of MST
vector<Edge> prim(const Graph& g) {
	int vertice = g.getVerticeNumber();
	vector<Edge> ret;
	set<int> visited;
	visited.insert(0);
	priority_queue<int, vector<Edge>, EdgeComperator> heap;  // a min-heap
	for(const auto e : g.getEdges(0)) {
		heap.push(e);
	}
	// iteration until all of the vertices are added to 'visited'
	while(visited.size() != vertice) {
		Edge least_weight_edge = heap.top();
		heap.pop();
		int new_node;
		// if the edge is a cross-edge, then add the new node to visited
		// else discard the edge
		if(visited.find(least_weight_edge.from) == visited.end()) {
			new_node = least_weight_edge.from;
		} else if(visited.find(least_weight_edge.to) == visited.end()) {
			new_node = least_weight_edge.to;
		} else { continue; }  // the edge is not a cross-edge (both vertices are already in the MST)
		for(const auto& e : g.getEdges(new_node)) {
			if(e.to != new_node) {
				heap.push(e);
			}
		}
		ret.push_back(least_weight_edge);
		visited.insert(new_node);
	}
	return ret;
}

int main(int argc, char** argv) {
	Graph g = readGraphFromFile(input_file);   // graph construction from file
	cout << "Load the graph data done.\n";
	vector<Edge> mst = prim(g);     // prim algorithm to get the MST
	long long total = 0;
	// get the total weight of MST
	for(const auto& e : mst) {
		total += e.weight;
	}
	cout << "mst weight:\t" << total << endl;
	return 0;
}