// computing strongly connected components of directed graph
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Graph {
public:
	Graph(int v) {
		edges.resize(v);
	}

	void addEdge(int start, int end) {
		edges[start].push_back(end);
	}
	size_t getVertice() const {
		return edges.size();
	}

	const list<int>& getAdj(size_t v) const {
		return edges[v];
	}

	Graph reserve() const {
		Graph res(getVertice());
		for(size_t i = 0; i < getVertice(); ++i) {
			for(int other : getAdj(i)) {
				res.addEdge(other, i);
			}
		}
		return res;
	}
	
	void printEdges() const {
		for(size_t i = 0; i < getVertice(); ++i) {
			for(int other : getAdj(i)) {
				cout << i << "\t" << other << endl;
			}
		}
	}
private:
	vector<list<int>> edges;
};


class SCC {
public:
	SCC(const Graph& g):graph(g) {
		num_v = g.getVertice();
		vertice.resize(num_v);
		mask.resize(num_v);
		for(int i = 0; i < num_v; ++i) {
			vertice[i] = i;
			mask[i] = false;
		}
		cnt = 0;
	}

	size_t getSCC() {
		cout << "Start post order of g_rev" << endl;
		getPostOrderDfs(graph);
		cout << "Start SCC DFS of g" << endl;
		SCCDfs(graph);
		cout << "Done!" << endl;
		sort(component_size.rbegin(), component_size.rend());
		for(int i = 0; i < component_size.size() && i < 5; ++i) {
			cout << component_size[i] << "\t";
		}
		for(int i = 0; i < max<int>(5 - component_size.size(), 0); ++i) {
			cout << 0 << "\t";
		}
		cout << endl;
		return cnt;
	}

	void getPostOrderDfs(const Graph& g) {
		Graph g_rev = g.reserve();
		for(int i = 0; i < num_v; ++i) {
			if(!mask[i]) dfs_stack(g_rev, i);
		}
	}

	void dfs_scc_stack(const Graph& g, int v) {
		stack<int> vertice;
		vertice.push(v);
		mask[v] = true;
		size_t cur_component_size = 0;
		while(!vertice.empty()) {
			int u = vertice.top();
			const list<int>& adjs = g.getAdj(u);
			bool has_explored_done = true;
			for(int w : adjs) {
				if(!mask[w]) {
					vertice.push(w);
					mask[w] = true;
					has_explored_done = false;
				}
			}
			if(has_explored_done) {
				vertice.pop();
				cur_component_size++;
			}
		}
		component_size.push_back(cur_component_size);
	}

	void dfs_stack(const Graph& g, int v) {
		stack<int> vertice;
		vertice.push(v);
		mask[v] = true;
		while(!vertice.empty()) {
			int u = vertice.top();
			const list<int>& adjs = g.getAdj(u);
			bool has_explored_done = true;
			for(int w : adjs) {
				if(!mask[w]) {
					vertice.push(w);
					mask[w] = true;
					has_explored_done = false;
				}
			}
			if(has_explored_done) {
				vertice.pop();
				post_order.push(u);
			}
		}
	}

	void SCCDfs(const Graph& g) {
		for(int i = 0; i < num_v; ++i) {
			mask[i] = false;
		}
		while(!post_order.empty()) {
			int s = post_order.top();
			post_order.pop();
			if(!mask[s]) {
				dfs_scc_stack(g, s);
				cnt++;
			}
		}
	}
private:
	Graph graph;
	size_t num_v;
	vector<int> vertice;
	vector<bool> mask;
	stack<int> post_order;
	size_t cnt;
	vector<size_t> component_size;
};


int main() {
	int start, end;
	const size_t num_v = 875714;
	Graph* graph = new Graph(num_v);
	ifstream fin("SCC.txt", std::ios::in);
	string str;
	size_t cnt = 0;
	cout << "Read the graph into memory ..." << endl;
	while(getline(fin, str)) {
		stringstream buffer(str);
		buffer >> start >> end;
		graph->addEdge(start - 1, end - 1);
		cnt++;
	}
	cout << "Edges number:\t" << cnt << endl;
	SCC scc(*graph);
	delete graph;
	size_t scc_number = scc.getSCC();
	cout << "scc number:\t " << scc_number << endl;
	return 0;
}