//============================================================================
// Name        : weight-sort.cpp
// Author      : kikyoo
// Description : in C++, Ansi-style
//============================================================================

#include <map>
#include <iostream>
#include "weight-sort.hpp"

template <typename Key, typename Weight>
static void print(std::vector<std::pair<Key, Weight>>& in) {
  for (const auto& one:in) {
    std::cout << "key:" << std::get<0>(one)
      << ", weight:" << std::get<1>(one) << std::endl;
  }
}

int main() {

  const size_t SIZE = 4;

  std::vector<std::pair<std::string, int>> vec;
  for (int i =0;  i < SIZE; i ++) {
    vec.push_back(std::make_pair("key_" + std::to_string(i), i*i));
  }

  std::cout << "before weight sort:" << std::endl;
  print(vec);

  auto out = WeightSort(vec);

  std::cout << "after weight sort:" << std::endl;
  print(out);

  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "do some statistics:" << std::endl;
  std::map<std::pair<std::string, int>, int> statistics;
  for (int i =0;i < 100000; i ++) {
    auto out = WeightSort(vec);
    statistics[out[0]] +=1;
  }
  for (const auto& pair: statistics) {
    std::cout << "key:" << std::get<0>(pair.first) <<", weight:" << std::get<1>(pair.first) << ", times:" << pair.second << std::endl;
  }

  return 0;
}
