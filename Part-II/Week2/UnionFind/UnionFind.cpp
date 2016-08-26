#include "UnionFind.hpp"

namespace alg {
	UnionFind::UnionFind(int size):cnt_(size) {
		id_.reserve(size);
		sz_.reserve(size);
		for(int i = 0; i < size; ++i) {
			id_.push_back(i);
			sz_.push_back(1);
		}
	}

	int UnionFind::find(int p) {
		while(p != id_[p]) {
			p = id_[p];
		}
		return p;
	}

	void UnionFind::unionTwo(int p, int q) {
		int i = find(p);
		int j = find(q);
		if(i == j)	return;   // they have unioned
		if(sz_[i] < sz_[j]) {
			id_[i] = j;
			sz_[j] += sz_[i];
		} else {
			id_[j] = id_[i];
			sz_[i] += sz_[j];
		}
		--cnt_;
	}

	int UnionFindCP::find(int p) {
		int father = id_[p];
		while(id_[father] != father) { // father is not root
			id_[p] = id_[father];
			father = id_[p];
		}
		return father;
	}

}
