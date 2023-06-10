#include <iostream>
#include <algorithm>
#include "prime_lib.hh"

int main() {
  std::cout << std::ranges::none_of(prime_number_range(50), [](auto x){return x == 48;}) << '\n';

  return 0;
}
