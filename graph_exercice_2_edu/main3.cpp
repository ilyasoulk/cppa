#include <iostream>
#include <fstream>
#include <string>
#include "graph/include/graph.hh"
#include "graph/include/graph_algos.hpp"


void parse_and_apply_state_edge_(std::ifstream& file){
  // Same layout as before

  // Do not change this
  // For each pair we compute the shortest distance individually
  for (auto src : g.states())
    for (auto dst : g.states())
      std::cout << src << " -- " << (shortest_distance(g, src, dst)) << " -> " << dst << '\n';

}

void parse_and_apply_state_(std::ifstream& file){
// Same layout as before
}


void parse_and_apply(const std::string& filename){
// Same layout as before
}


int main() {

  // How to deal with string and char
  const std::string base = "graph_files/graph";
  for (int i : std::views::iota(1, 4)){
    auto filepath = base + std::to_string((i)) + ".txt";
    std::cout << "Shortest paths for graph stored in " << filepath << " is :\n";
    parse_and_apply(filepath);
  }

  return 0;
}
