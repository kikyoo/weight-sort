/*
 * weight-sort.hpp
 *
 *  Created on: 2017年12月25日
 *      Author: kikyoo
 */

#ifndef WEIGHT_SORT_HPP_
#define WEIGHT_SORT_HPP_

#include <random>
#include <thread>
#include <unistd.h>
#include <sys/syscall.h>
#include <vector>
#include <algorithm>

template<typename T>
static inline typename std::enable_if<std::is_floating_point<T>::value, T>::type Random(T low=0, T high=1) {
  static thread_local std::mt19937_64 gen(syscall(SYS_gettid));
  std::uniform_real_distribution<T> distribution(low, high);
  return distribution(gen);
}
template<typename T>
static inline typename std::enable_if<!std::is_floating_point<T>::value, T>::type Random(T low=0, T high=1) {
  static thread_local std::mt19937_64 gen(syscall(SYS_gettid));
  std::uniform_int_distribution<T> distribution(low, high);
  return distribution(gen);
}

template <typename Key, typename Weight>
static std::vector<std::pair<Key, Weight>> WeightSort(std::vector<std::pair<Key, Weight>>&& in) {
  Weight sum = 0;
  for (const auto& one: in) {
    sum += std::get<1>(one);
  }
  std::vector<std::pair<size_t, Weight>> weight(in.size());
  for (size_t i = 0; i < in.size(); i ++) {
    Weight w = std::get<1>(in[i]) + Random((Weight)0, sum);
    weight[i] = std::make_pair(i, w);
  }
  std::sort(weight.begin(), weight.end(), [](std::pair<size_t, Weight>& i, std::pair<size_t, Weight>& j){return std::get<1>(i) > std::get<1>(j);});

  std::vector<std::pair<Key, Weight>> out(in.size());
  for (size_t i =0; i < in.size(); i ++) {
    out[i] = std::move(in[std::get<0>(weight[i])]);
  }
  return out;
}

template <typename Key, typename Weight>
static std::vector<std::pair<Key, Weight>> WeightSort(const std::vector<std::pair<Key, Weight>>& in) {
  Weight sum = 0;
  for (const auto& one: in) {
    sum += std::get<1>(one);
  }
  std::vector<std::pair<size_t, Weight>> weight(in.size());
  for (int i = 0; i < in.size(); i ++) {
    Weight w = std::get<1>(in[i]) + Random(0, sum);
    weight[i] = std::make_pair(i, w);
  }
  std::sort(weight.begin(), weight.end(), [](std::pair<size_t, Weight>& i, std::pair<size_t, Weight>& j){return std::get<1>(i) > std::get<1>(j);});

  std::vector<std::pair<Key, Weight>> out(in.size());
  for (size_t i =0; i < in.size(); i ++) {
    out[i] = in[std::get<0>(weight[i])];
  }
  return out;
}


#endif /* WEIGHT_SORT_HPP_ */
