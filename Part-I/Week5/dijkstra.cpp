#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <utility>
#include <list>
#include <fstream>
#include <sstream>
using namespace std;


typedef pair<int, size_t> Edge;
typedef pair<int, size_t> dis_pair;
#define MAX_LENGTH 1000000

struct CompDispair {
	bool operator()(const dis_pair& lhs, const dis_pair& rhs) const {
		return lhs.second > rhs.second;
	}
};

class Graph {
public:
	explicit Graph(int vertice):num_edges_(0), edges_(vertice) {}
	void addEdge(int start, int end, size_t length) {
		edges_[start].push_back(Edge{end, length});
		++num_edges_;
	}
	size_t getNumberVertice() const { return edges_.size(); }
	size_t getNumEdges() const { return num_edges_; }
	const list<Edge>& getAdjVertice(int v) const {
		return edges_[v];
	}
	// implementation of dijkstra algorithm
	vector<size_t> getShortDistance(int source) {
		// the given source idx is beyond the range
		if(source < 0 || source >= getNumberVertice()) {
			cerr << "the source shoule be [0, " << getNumberVertice() << " ]\n";
			exit(-1);
		}
		vector<size_t> dis(getNumberVertice(), MAX_LENGTH);
		vector<bool> found(getNumberVertice(), false);
		priority_queue<dis_pair, vector<dis_pair>, CompDispair> dis_queue;
		dis[source] = 0;
		dis_queue.push(dis_pair{source, 0});
		while(!dis_queue.empty()) {
			int v_nearest = dis_queue.top().first;
			int len_nearest = dis_queue.top().second;
			dis_queue.pop();
			if(!found[v_nearest]) {
				found[v_nearest] = true;
				dis[v_nearest] = len_nearest;
				const list<Edge>& adjs = getAdjVertice(v_nearest);
				list<Edge>::const_iterator it = adjs.cbegin(), it_end = adjs.cend();
				for(; it != it_end; ++it) {
					int u = it->first;
					if(found[u]) continue;
					size_t len = it->second;
					size_t alt = len + len_nearest;
					if(alt < dis[u]) {
						dis[u] = alt;
						dis_queue.push(dis_pair{u, alt});
					}
				}
			}
		}
		return dis;
	}
private:
	vector<list<Edge>> edges_;
	size_t num_edges_;
};


void readFromFile(Graph& g, const string& file) {
	ifstream reader(file, std::ios::in);
	if(!reader) {
		cerr << "cannot open the file " << file << "\n";
		exit(-1);
	}
	string str_line;
	while(getline(reader, str_line)) {
		stringstream stream(str_line);
		vector<int> nums;
		int start, end;
		size_t length;
		stream >> start;
		start -= 1;
		char ch;
		int prev_end = -1;
		while(stream) {
			stream >> end >> ch >> length;
			if(ch != ',') {
				//avoid error when reading
				cerr << "ch shoule be $,$ but it is $" << ch << "$\n";
				exit(-1);
			}
			if(end != prev_end)
				g.addEdge(start, end - 1, length);
			prev_end = end;
		}
	}
	reader.close();
}
const string input_file = "dijkstraData.txt";

int main(int argc, char** argv) {

	const int v = 200;
	Graph g(v);
	readFromFile(g, input_file);
	cout << "Number of vertice:\t" << g.getNumberVertice() << "\n";
	cout << "Number of edges:\t" << g.getNumEdges() << "\n";
	vector<size_t> distance = g.getShortDistance(0);
	vector<int> destination{7, 37, 59, 82, 99, 115, 133, 165, 188, 197};

	for(int i = 0; i < destination.size(); ++i) {
		cout << distance[destination[i] - 1];
		if(i != destination.size() - 1) cout << ",";
	}
	cout << endl;
	return 0;
}