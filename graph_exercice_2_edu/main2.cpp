#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include "graph/include/graph.hh"


// Something here?
/**
 * Parses the input file and applies state and edge operations based on the specified data types.
 * O(n) with n being the number of edges(lines) in the file.
 * @tparam STATE The state type.
 * @tparam EDATA The edge data type.
 * @param file The input file stream.
 * @param n_states The number of states.
 * @param n_edges The number of edges.
 */
template<typename STATE, typename EDATA>
void parse_and_apply_state_edge_(std::ifstream& file, int n_states, int n_edges){

  // Here as well?
  auto g = graph<STATE, EDATA>();
  g.read_edge_stream(file, n_states, n_edges); // the idea

  // Something here?

  // Do not change this
  for (auto s : g.states())
    for (auto& e : g.out(s))
      std::cout << e.src() << " -- " << e.data() << " -> " << e.dst() << '\n';
}

/**
 * Parses the input file and applies state operations based on the specified data type. O(1)
 * @tparam STATE The state type.
 * @param file The input file stream.
 * @param dataType The data type of the edge.
 * @param n_states The number of states.
 * @param n_edges The number of edges.
 */
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

/**
 * Parses the input file and applies state and edge operations based on the specified file format. O(1)
 * @param filename The name of the input file.
 */
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

  const std::string base = "graph_files/graph";
  for (int i : std::views::iota(1, 4)){
    auto filepath = base + std::to_string((i)) + ".txt";
    std::cout << "Graph stored in " << filepath << " is :\n";
    parse_and_apply(filepath);
  }

  parse_and_apply("graph_files/graph1.txt");

  return 0;
}
