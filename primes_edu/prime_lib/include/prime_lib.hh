#pragma once
#include <vector>
#include <cmath>
#include <ranges>
#include <algorithm>
// The iterator class goes either here
// class /*good name*/ {
// };

class prime_number_range {
private:
  std::size_t count_; // Number of prime numbers to generate
  std::vector<int> prime_numbers;

  //TODO

public:
  class iterator {
    public:
      iterator(prime_number_range& range, int curr);
      prime_number_range& range;
      int curr;
      int operator*() const;
      iterator operator++();
      bool operator!=(const iterator& other) const;
  };

  iterator begin();
  iterator end();
  prime_number_range(std::size_t count);
  // Or here
  // class /*good name*/ {
  // };
  // Note, there is no issue in defining "nested" classes

  // TODO

};