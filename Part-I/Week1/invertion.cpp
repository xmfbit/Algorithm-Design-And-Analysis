/*************************************************************************
	> File Name: invertion.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年06月19日 星期日 22时18分59秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iterator>
#include "merge_sort.hpp"
using namespace std;
using namespace alg;
int main(int argc, char** argv) {
  ifstream file(argv[1], std::ios::in);
  string tmp;
  vector<int> vec;
  while(std::getline(file, tmp)) {
    vec.push_back(atoi(tmp.c_str()));
  }
  //std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << get_inversion_count(vec.begin(), vec.end());
  return 0;
}

