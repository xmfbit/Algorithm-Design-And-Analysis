// solution of knapsack problem
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

struct Item {
	size_t weight;
	size_t value;
	Item(size_t weight, size_t value): weight(weight), value(value) {}
	Item():Item(0, 0) {}
};

struct ItemComperator {
	bool operator()(const Item& lhs, const Item& rhs) const {
		return lhs.weight > rhs.weight;
	}
};
class KnapSackSolver {
public:
	explicit KnapSackSolver(const string& input_file):W(0), N(0) {
		ifstream reader(input_file.c_str());
		reader >> W >> N;
		item.resize(N);
		
		for(size_t i = 0; i < N; ++i) {
			reader >> item[i].value >> item[i].weight;
		}
		sort(item.begin(), item.end(), ItemComperator());
	}
	size_t solve();
private:
	vector<Item> item;
	size_t W;
	size_t N;
};

size_t KnapSackSolver::solve() {
	vector<size_t> dp(W+1, 0);
	clock_t t = clock();
	for(size_t item_id = 0; item_id < N; ++item_id) {
		int w_id = W;
		size_t cur_weight = item[item_id].weight;
		size_t cur_value = item[item_id].value;
		while(w_id >= cur_weight) {
			dp[w_id] = max(dp[w_id], dp[w_id - cur_weight] + cur_value);
			--w_id;
		}
	}
	t = clock() - t;
	cout << "Total time: " << static_cast<float>(t) / CLOCKS_PER_SEC << endl;
	return dp[W];
}


int main(int argc, char** argv) {
	const string input_file = "./knapsack_big.txt";
	KnapSackSolver solver(input_file);
	cout << "Load data done." << endl;
	cout << "Result: " << solver.solve() << endl;
	return 0;   //2493893  4243395
}