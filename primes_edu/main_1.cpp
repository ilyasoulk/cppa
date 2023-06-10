#include <iostream>
#include "prime_lib.hh"

int main() {
  for (auto prime : prime_number_range(10)) {
    std::cout << prime << " ";
  }
  std::cout << std::endl;

  return 0;
}
