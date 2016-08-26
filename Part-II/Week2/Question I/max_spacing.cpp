#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "UnionFind.hpp"
using namespace std;
using namespace alg;

// Edge structure
struct Edge {
	int from;
	int to;
	int weight;
	Edge() {}
	// from <--> to 
	Edge(int from, int to, int weight):from(from), to(to), weight(weight) {}
};

class Cluster {
public:
	explicit Cluster(const string& input_file) {
		// read data from file
		ifstream reader(input_file.c_str());
		reader >> num_vertice;
		int from, to, weight;
		while(reader >> from >> to >> weight) {
			addEdge(from - 1, to - 1, weight);
		}
	}
	// Add an edge to the graph
	void addEdge(int from, int to, int weight) {
		edges.push_back(Edge(from, to, weight));
	}
	// get maxSpacing of K clustering
	int maxSpacing(int k_group);
private:
	vector<Edge> edges;
	int num_vertice;
};

// for sorting
struct EdgeComperator {
	bool operator()(const Edge& lhs, const Edge& rhs) const {
		return lhs.weight < rhs.weight;
	}
};

int Cluster::maxSpacing(int k_group) {
	UnionFindCP uf(num_vertice);
	// sort the edges by weight descendingly
	sort(edges.begin(), edges.end(), EdgeComperator());
	int edge_idx = 0;
	while(uf.getComponentsNumber() != k_group) {
		const Edge& edge = edges[edge_idx++];
		if(!uf.connected(edge.from, edge.to)) {
			uf.unionTwo(edge.from, edge.to);
		}
	}
	// get the weight of the next edge 
	while(edge_idx < edges.size()) {
		if(!uf.connected(edges[edge_idx].from, edges[edge_idx].to)) {
			return edges[edge_idx].weight;
		} 
		edge_idx++;
	}
	return -1;  // error! can not find the result
}


int main(int argc, char** argv) {
	const string input_file = "./clustering1.txt";
	Cluster cluster(input_file);
	cout << "Read the data done.\n";
	const int k = 4;
	cout << cluster.maxSpacing(k) << endl;
	return 0;
}
