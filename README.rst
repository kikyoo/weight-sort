weight-sort
=========

权重随机，权重大的，更大机会出现在队列前部。


Simple example:

.. code-block:: c++
    
  int main() {
  
    const size_t SIZE = 4;
    std::vector<std::pair<std::string, int>> vec;
    for (int i =0;  i < SIZE; i ++) {
      vec.push_back(std::make_pair("key_" + std::to_string(i), i*i));
    }

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

可能结果
.. code-block:: c++
  do some statistics:
  key:key_0, weight:0, times:4866
  key:key_1, weight:1, times:7479
  key:key_2, weight:4, times:20708
  key:key_3, weight:9, times:66947
