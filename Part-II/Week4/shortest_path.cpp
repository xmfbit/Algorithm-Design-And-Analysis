#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

struct Edge {
	int from;
	int to;
	int weight;
	Edge(int from, int to, int  weight):from(from), to(to), weight(weight) {}
	Edge():Edge(0, 0, 0) {}
};

class Graph {
public:
	explicit Graph(const string& input_file);
	int getNumberVertices() const {
		return edges.size();
	}
	const vector<Edge>& getAdjNodes(int u) const {
		return edges[u];
	}
	//bool bellman_ford(int source, vector<int>& d) const;
	bool detect_negtive_cycle() const;  // detect negtive cycle with bellman-ford algorithm
	vector<vector<int>> solve_shortest_distance() const;
	int shortest_path_distance() const;
	void show_weights() const;
private:
	vector<vector<Edge>> edges;
	vector<vector<int>> weights;
	void addEdge(int from, int to, int weight);
	void relax(vector<long long>& d, int u, int v) const;
	void relax(vector<long long>& d) const;
};

Graph::Graph(const string& input_file) {
	int v, e;
	ifstream reader(input_file.c_str());
	reader >> v >> e;
	edges = vector<vector<Edge>>(v);
	weights = vector<vector<int>>(v, vector<int>(v, INT_MAX));
	cout << "Number of vertices: " << v << ", number of edges: " << e << endl;
	int from, to, weight;
	for(int i = 0; i < e; ++i) {
		reader >> from >> to >> weight;
		addEdge(from - 1, to - 1, weight);
	}
	for(int i = 0; i < v; ++i) {
		weights[i][i] = 0;
	}
	cout << "Load the graph done." << endl;
}

void Graph::addEdge(int from, int to, int weight) {
	edges[from].push_back(Edge(from, to, weight));
	weights[from][to] = weight;
}

void Graph::relax(vector<long long>& d, int u, int v) const {
	if(d[v] > d[u] + weights[u][v]) {
		d[v] = d[u] + weights[u][v];
	}
}
void Graph::relax(vector<long long>& d) const {
	for(const auto& adj_list : edges) {
		for(const auto& e : adj_list) {
			relax(d, e.from, e.to);
		}
	}
}

bool Graph::detect_negtive_cycle() const{
	int v = getNumberVertices();
	vector<long long> d(v, INT_MAX);
	d[0] = 0;
	for(int cnt = 0; cnt < v - 1; ++cnt) {
		relax(d);
	}
	for(const auto& adj_list : edges) {
		for(const auto& e : adj_list) {
			if(d[e.to] > d[e.from] + weights[e.from][e.to]) {
				return true;
			}
		}
	}
	return false;
}

vector<vector<int>> Graph::solve_shortest_distance() const {
	int v = getNumberVertices();
	vector<vector<long long>> D(v, vector<long long>(v));
	for(int i = 0; i < v; ++i) {
		for(int j = 0; j < v; ++j) {
			D[i][j] = weights[i][j];
		}
	}
	for(int k = 0; k < v; ++k) {
		auto D_prev = D;
		for(int i = 0; i < v; ++i) {
			for(int j = 0; j < v; ++j) {
				D[i][j] = min(D_prev[i][j], D_prev[i][k] + D_prev[k][j]);
			}
		}
	}
	vector<vector<int>> ret(v, vector<int>(v));
	for(int i = 0; i < v; ++i) {
		for(int j = 0; j < v; ++j) {
			ret[i][j] = static_cast<int>(D[i][j]);
		}
	}
	return ret;
}

int Graph::shortest_path_distance() const {
	auto D = solve_shortest_distance();
	int v = getNumberVertices();
	int ret = INT_MAX;
	for(int i = 0; i < v; ++i) {
		for(int j = 0; j < v; ++j) {
			if(ret > D[i][j]) {
				ret = D[i][j];
			}
		}
	}
	return ret;
}

void Graph::show_weights() const {
	int v = getNumberVertices();
	for(int i = 0; i < v; ++i) {
		for(int j = 0; j < v; ++j) {
			cout << weights[i][j] << "\t";
		}
		cout << endl;
	}
}


int main(int argc, char** argv) {
	vector<string> files{"g1.txt", "g2.txt", "g3.txt"};
	vector<Graph> graphs;
	for(const auto& s : files) {
		cout << "Load the graph from file " << s << endl;
		graphs.push_back(Graph(s));
	}
	vector<int> w;
	for(int i = 0; i < graphs.size(); ++i) {
		const auto&g = graphs[i];
		if(!g.detect_negtive_cycle()) {
			w.push_back(g.shortest_path_distance());
		} else {
			cout << "there exists negtive cycle in the graph " << i << endl;
		}
	}
	for(auto v : w) {
		cout << v << endl;
	}
	return 0; //NULL, NULL, -19 
}