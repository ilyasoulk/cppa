#include <iostream>
#include <fstream>
#include <string>
#include "graph/include/graph.hh"
#include "graph/include/graph_algos.hpp"

template<typename STATE, typename EDATA>
void parse_and_apply_state_edge_(std::ifstream& file, int n_states, int n_edges){
  // Same layout as before
  auto g = graph<STATE, EDATA>();
  g.read_edge_stream(file, n_states, n_edges); // the idea

  // Do not change this
  // For each pair we compute the shortest distance individually
  for (auto src : g.states())
    for (auto dst : g.states())
      std::cout << src << " -- " << (shortest_distance(g, src, dst)) << " -> " << dst << '\n';

}


template<typename STATE>
void parse_and_apply_state_(std::ifstream& file, std::string dataType, int n_states, int n_edges){
  if (dataType == "int") {
    parse_and_apply_state_edge_<STATE, int>(file, n_states, n_edges);
  }
  else if (dataType == "char") {
    parse_and_apply_state_edge_<STATE, char>(file, n_states, n_edges);
  }

  if (dataType == "str") {
    parse_and_apply_state_edge_<STATE, std::string>(file, n_states, n_edges);
  }

  if (dataType == "float") {
    parse_and_apply_state_edge_<STATE, float>(file, n_states, n_edges);
  }

  if (dataType == "unsigned") {
    parse_and_apply_state_edge_<STATE, unsigned>(file, n_states, n_edges);
  }
  // I'm a helper function
  // Maybe I take a template
}

void parse_and_apply(const std::string& filename){
  // Implement me
  std::ifstream inputFile(filename);
  if (!inputFile) {
    std::cerr << "Error with filename: " << filename << std::endl;
    return;
  }

  std::string headerLine;
  std::getline(inputFile, headerLine);
  std::istringstream iss(headerLine);

  std::string stateType;
  std::string dataType;

  int n_edges;
  int n_states;

  iss >> stateType >> dataType;
  if (!(iss >> n_states >> n_edges)) {
    n_edges = 0;
    n_states = 0;
  }


  if (stateType == "int") {
    parse_and_apply_state_<int>(inputFile, dataType, n_states, n_edges);
  }

  else if (stateType == "str") {
    parse_and_apply_state_<std::string>(inputFile, dataType, n_states, n_edges);
  }

  else if (stateType == "char") {
    parse_and_apply_state_<char>(inputFile, dataType, n_states, n_edges);
  }

  else if (stateType == "float") {
    parse_and_apply_state_<float>(inputFile, dataType, n_states, n_edges);
  }

  else if (stateType == "unsigned") {
    parse_and_apply_state_<unsigned>(inputFile, dataType, n_states, n_edges);
  }
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
