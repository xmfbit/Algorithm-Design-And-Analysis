// greedy algorithm demo for job scheduling
// it's a trival problem after watching the lecture video 
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

struct Job {
	int weight;
	int length;
	Job() {}
	Job(int weight, int length): weight(weight), length(length) {}
};

// job comperator by diff (weight - length)
struct Comperator_LongerDifference {
public:
	bool operator()(const Job& j1, const Job& j2) const {
		int d1 = j1.weight - j1.length;
		int d2 = j2.weight - j2.length;
		if(d1 > d2)	return true;
		else if(d1 < d2)	return false;
		else return j1.weight > j2.weight;
	}
};

// job comperator by ratio (weight / length
struct Comperator_LargerRatio {
public:
	bool operator()(const Job& j1, const Job& j2) const {
		double r1 = static_cast<double>(j1.weight) / j1.length;
		double r2 = static_cast<double>(j2.weight) / j2.length;
		return r1 > r2;
	}
};

class JobSchedule {
public:
	explicit JobSchedule(const string& input_file) {
		ifstream reader(input_file.c_str());
		int weight, length;
		reader >> number;
		while(reader >> weight >> length) {
			addJob(weight, length);
		}
		assert(jobs.size() == number);
	}

	long long schedule(int code) {
		if(code == 0) {
			sort(jobs.begin(), jobs.end(), Comperator_LongerDifference());
		} else if(code == 1) {
			sort(jobs.begin(), jobs.end(), Comperator_LargerRatio());
		} else {
			cout << "Unsupport code.\n";
			return 0;
		}
		long long total_length = 0;
		long long weighted_time = 0;
		//int cnt = 0;
		for(const auto& j : jobs) {
			total_length += j.length;
			weighted_time += total_length * j.weight;
			//cout << "After " << cnt << " jobs, cost = " << weighted_time << endl;
			//cnt++;
		}
		return weighted_time;
	}
private:
	int number;
	vector<Job> jobs;
	void addJob(int weight, int length) {
		jobs.push_back(Job(weight, length));
	}
};

int main(int argc, char** argv) {
	const string input_file = "./jobs.txt";
	JobSchedule js(input_file);
	cout << js.schedule(1) << endl;
	
	return 0;
}
// 69119377652 67311454237