// maintaince the median of a stream with two min-heap
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <functional>
#include <cassert>
using namespace std;

const string input_file = "Median.txt";

// min-heap
typedef priority_queue<int, vector<int>, greater<int>> MinHeap;
// max-heap
typedef priority_queue<int, vector<int>, less<int>> MaxHeap;


void re_blance_1(MaxHeap& low, MinHeap& high) {
	int max_num_in_low = low.top();
	high.push(max_num_in_low);
	low.pop();
}

void re_blance_2(MaxHeap& low, MinHeap& high) {
	low.push(high.top());
	high.pop();
}

int main(int argc, char** argv) {
	ifstream reader(input_file.c_str(), std::ios::in);
	int num;
	int cnt = 0;
	MaxHeap low_heap;
	MinHeap high_heap;
	long long sum = 0;
	// insert the first element
	reader >> num;
	low_heap.push(num);
	sum += num;
	// insert the second element
	reader >> num;
	if(num > low_heap.top()) high_heap.push(num);
	else {
		low_heap.push(num);
		re_blance_1(low_heap, high_heap);
	}
	sum += low_heap.top();
	assert(low_heap.size() == high_heap.size() || low_heap.size() == high_heap.size() + 1);
	while(reader >> num) {
		if(num >= low_heap.top()) {
			high_heap.push(num);
		} else {
			low_heap.push(num);
		}
		if(low_heap.size() == high_heap.size() + 2) {
			re_blance_1(low_heap, high_heap);
		} else if(high_heap.size() > low_heap.size()) {
			re_blance_2(low_heap, high_heap);
		}
		assert(high_heap.size() == low_heap.size() || high_heap.size() == low_heap.size() - 1);
		sum += low_heap.top();
	}
	reader.close();
	cout << "The answer is " << sum % 10000 << endl;
	return 0;
}