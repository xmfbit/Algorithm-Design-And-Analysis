#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>   // hash
#include <fstream>
#include <algorithm>
#include <cassert>
using namespace std;
const string input_file = "algo1-programming_prob-2sum.txt";

int main(int argc, char** argv) {
	// read data from file
	ifstream reader(input_file, std::ios::in);
	// use unordered_set to dedup
	unordered_set<long long> nums;
	long long data;
	while(reader >> data) {
		nums.insert(data);
	}
	reader.close();
	const long long min_t = -10000, max_t = 10000;
	vector<long long> nums_vec;
	nums_vec.reserve(nums.size());
	copy(nums.cbegin(), nums.cend(), back_inserter(nums_vec));
	sort(nums_vec.begin(), nums_vec.end());
	auto it = nums_vec.begin(), it_end = nums_vec.end();
	unordered_set<long long> targets;
	for(; it != it_end; ++it) {
		auto low_bound = lower_bound(it + 1, it_end, min_t - *it);
		if(low_bound != nums_vec.end()) {
			auto high_bound = upper_bound(it + 1, it_end, max_t - *it);
			while(low_bound != high_bound) {
				targets.insert(*it + *low_bound++);
			}
		}
	}
	cout << "The answer is " << targets.size() << endl;
	return 0;
}