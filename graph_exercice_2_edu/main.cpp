#include <iostream>
#include <string>
#include "graph/include/graph.hh"

void f_i_f(){

  const int n_states = 4;

  // graph with ints as states
  // and floats as labels
  auto g = graph<int, float>();

  for (int i = 0; i < n_states; ++i)
    for (int j = 0; j < n_states; ++j)
      g.add_edge(i,j, i+j);

  for (auto s : g.states())
    for (auto& e : g.out(s))
      std::cout << e.src() << " -- " << e.data() << " -> " << e.dst() << '\n';

  // Expected output for n_states = 4
  //  3 -- 3 -> 0
  //  3 -- 4 -> 1
  //  3 -- 5 -> 2
  //  3 -- 6 -> 3
  //  2 -- 2 -> 0
  //  2 -- 3 -> 1
  //  2 -- 4 -> 2
  //  2 -- 5 -> 3
  //  1 -- 1 -> 0
  //  1 -- 2 -> 1
  //  1 -- 3 -> 2
  //  1 -- 4 -> 3
  //  0 -- 0 -> 0
  // Note there is no order imposed on the order of the states in g.states(),
  // nor on the edges obtained from g.out(s) for some state s
}

void f_f_s(){

  // const int n_states = 4;

  // // graph with ints as states
  // // and floats as labels
  // auto g = graph<float, std::string>();

  // for (int i = 0; i < n_states; ++i)
  //   for (int j = 0; j < n_states; ++j)
  //     g.add_edge(i/2.,j/2., "val: " + std::to_string(i+j));

  // for (auto s : g.states())
  //   for (auto& e : g.out(s))
  //     std::cout << e.src() << " -- " << e.data() << " -> " << e.dst() << '\n';

  // // Expected output for n_states = 4
  // //  1.5 -- val: 3 -> 0
  // //  1.5 -- val: 4 -> 0.5
  // //  1.5 -- val: 5 -> 1
  // //  1.5 -- val: 6 -> 1.5
  // //  1 -- val: 2 -> 0
  // //  1 -- val: 3 -> 0.5
  // //  1 -- val: 4 -> 1
  // //  1 -- val: 5 -> 1.5
  // //  0.5 -- val: 1 -> 0
  // //  0.5 -- val: 2 -> 0.5
  // //  0.5 -- val: 3 -> 1
  // //  0.5 -- val: 4 -> 1.5
  // //  0 -- val: 0 -> 0
  // //  0 -- val: 1 -> 0.5
  // //  0 -- val: 2 -> 1
  // //  0 -- val: 3 -> 1.5
  // // Note there is no order imposed on the order of the states in g.states(),
  // // nor on the edges obtained from g.out(s) for some state s
}

int main() {
  f_i_f();
  f_f_s();

  return 0;
}
