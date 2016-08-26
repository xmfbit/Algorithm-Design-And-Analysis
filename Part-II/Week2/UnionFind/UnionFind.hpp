#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP
#include <vector>

namespace alg {
	using std::vector;
	class UnionFind {
	protected:
		vector<int> id_;   // id_[i] = root(i)
		vector<int> sz_;   // sz_[i] = number of sons and grand-sons whose root is i
		int cnt_;          // count of the components
	public:
		explicit UnionFind(int size);
		
		inline int getSize()const {
			return id_.size();
		}

		inline int getComponentsNumber() const {
			return cnt_;
		}

		inline bool connected(int p, int q) {
			if(p == q)	return true;
			return find(p) == find(q);
		}

		int find(int p);

		void unionTwo(int p, int q);
	};

	class UnionFindCP:public UnionFind {
	public:
		explicit UnionFindCP(int size):UnionFind(size) {}
		int find(int p);
	};
}
#endif // end of UnionFind.hpp