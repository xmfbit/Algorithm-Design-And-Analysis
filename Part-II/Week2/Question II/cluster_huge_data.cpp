#include "UnionFind.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iterator>
#include <bitset>
#include <cstdint>
#include <cassert>
#include <ctime>
#include <algorithm>
using namespace std;
using namespace alg;

class Cluster {
public:
	// read data from input file 
	Cluster(const string& input_file) {
		clock_t t = clock();
		ifstream reader(input_file.c_str());
		string line;
		getline(reader, line);
		istringstream ss(line);
		int code_length;
		ss >> num_vertice >> code_length;
		assert(num_vertice == 200000);
		assert(code_length == 24); // param check
		bitset<24> bits;
		int data, vertice_idx = 0;
		while(getline(reader, line)) {
			istringstream ss_line(line);
			for(int i = code_length - 1; i >= 0; --i) {
				ss_line >> data;
				bits[i] = data;
			}
			vertices[bits.to_ulong()].push_back(vertice_idx);
			++vertice_idx;
		}
		t = clock() - t;
		cout << "Construction time:\t" << static_cast<float>(t) / CLOCKS_PER_SEC << "s.\n";
	}
	// get the result
	int getK(int minSpacing);
private:
	map<uint32_t, vector<int>> vertices;  // key: hamming code, value: the vector of vertex index
	int num_vertice;
};


int Cluster::getK(int minSpacing) {
	clock_t t = clock();
	UnionFindCP uf(num_vertice);
	// build mask
	vector<uint32_t> mask(24 * 24);
	for(int i = 0; i < 24; ++i) {
		uint32_t tmp = 1U << i;
		for(int j = 0; j < 24; ++j) {
			mask[i * 24 + j] = tmp | (1U << j);
		}
	}
	// union the nodes whose distance == 0
	auto end_it = vertices.end();
	for(auto it = vertices.begin(); it != end_it; ++it) {
		const auto& vs = it->second;
		for(int i = 0; i < vs.size(); ++i) {
			for(int j = i + 1; j < vs.size(); ++j) {
				if(!uf.connected(vs[i], vs[j])) {
					uf.unionTwo(vs[i], vs[j]);
				}
			}
		}
	}
	// union the nodes whose distance == 1 or distance == 2
	for(auto it = vertices.begin(); it != end_it; ++it) {
		vector<uint32_t> diff_code(mask.size());
		const auto& vs = it->second;
		for(int i = 0; i < mask.size(); ++i) {
			diff_code[i] = it->first ^ mask[i];
		}
		for(int i = 0; i < diff_code.size(); ++i) {
			auto it_find = vertices.find(diff_code[i]);
			if(it_find == vertices.end())	continue;
			const auto& other = it_find->second;
			for(int v : vs) {
				for(int u : other) {
					if(!uf.connected(v, u)) {
						uf.unionTwo(v, u);
					}
				}
			}
		}
	}
	t = clock() - t;
	cout << "Processing time:\t" << static_cast<float>(t) / CLOCKS_PER_SEC << "s.\n";
	return uf.getComponentsNumber();
}

int main() {
	const string input_file = "./clustering_big.txt";
	Cluster cluster(input_file);
	cout << "Read data done.\n";
	cout << cluster.getK(3) << endl;
	return 0;
}