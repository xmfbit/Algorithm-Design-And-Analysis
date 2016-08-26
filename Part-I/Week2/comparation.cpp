#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iterator>
#include "quick_sort.hpp"
using namespace std;
using namespace alg;

bool test(const vector<int>& vec) {
  return is_sorted(vec.begin(), vec.end());
}

int main(int argc, char** argv) {
  ifstream file(argv[1], std::ios::in);
  string tmp;
  vector<int> vec;
  while(std::getline(file, tmp)) {
    vec.push_back(atoi(tmp.c_str()));
  }
  quick_sort(vec.begin(), vec.end());
  if(!test(vec)) {
    cout << "ERROR!" << endl;
  } else {
    cout << cnt << endl;
  }
  return 0;
}
