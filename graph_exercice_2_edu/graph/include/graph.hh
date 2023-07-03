#pragma once

#include <vector>
#include <unordered_map>
#include <cassert>
#include <stdexcept>
#include <ranges>
#include <concepts>
#include <iostream>
#include <sstream>

// template<StateType STATE, class EDATA>
// class graph {
// public:
//   // Implement this or some similar version
//   static graph read_edge_stream(std::istream& is, std::size_t nstates = 0, std::size_t nedges = 0) {
//     // g is the graph

//     return g;
//   }

// };


// Includes here

// Fwd declarations

// edges of the graph
template<class STATE, class EDATA>
class edge;
// iterator over edges of the graph
template<class STATE, class EDATA>
class edge_iterator;
// wrapper class to return the begin and end iterator
// of a state
template<class STATE, class EDATA>
class edge_range;
// The actual graph
template<class STATE, class EDATA>
class graph;

/**
 * @brief Templated class representing an edge in a graph.
 * @tparam STATE The state type of the graph.
 * @tparam EDATA The data type associated with the edge.
 */
template<class STATE, class EDATA>
class edge{
public:
  using state_type = STATE;
  using data_type = EDATA;

  /**
   * @brief Constructs an edge with the given source, destination, and data. O(1).
   * @param src The source state of the edge.
   * @param dst The destination state of the edge.
   * @param data The data associated with the edge.
   */
  edge(const state_type& src, const state_type& dst, const data_type& data)
    : src_(src), dst_(dst), data_(data)
  {}

  /**
   * @brief Returns the source state of the edge. O(1).
   * @return The source state.
   */
  const state_type& src() const { return src_; }

  /**
   * @brief Returns the destination state of the edge. O(1).
   * @return The destination state.
   */
  const state_type& dst() const { return dst_; }

  /**
   * @brief Returns the data associated with the edge. O(1).
   * @return The data.
   */
  const data_type& data() const { return data_; }

private:
  state_type src_;  ///< The source state of the edge.
  state_type dst_;  ///< The destination state of the edge.
  data_type data_;  ///< The data associated with the edge.
};

/**
 * @brief Templated class representing an iterator over edges with the same source state.
 * @tparam STATE The state type of the graph.
 * @tparam EDATA The data type associated with the edge.
 */
template<class STATE, class EDATA>
class edge_iterator{
public:
  using edge_type = graph<STATE, EDATA>::edge_type;

  /**
   * @brief Constructs an edge iterator with the given edges and current index. O(1).
   * @param iter The vector of edges.
   * @param current The current index of the iterator.
   */
  edge_iterator(const std::vector<edge_type>& iter, std::size_t current)
    : iter_(iter), current_(current)
  {}

  /**
   * @brief Checks if the iterator is not equal to another iterator. O(1).
   * @param rhs The other iterator to compare with.
   * @return True if the iterators are not equal, false otherwise.
   */
  bool operator!=(const edge_iterator& rhs) const { return current_ != rhs.current_; }

  /**
   * @brief Checks if the iterator is equal to another iterator. O(1).
   * @param rhs The other iterator to compare with.
   * @return True if the iterators are equal, false otherwise.
   */
  bool operator==(const edge_iterator& rhs) const { return !(*this != rhs); }

  /**
   * @brief Advances the iterator to the next edge. O(1).
   * @return The reference to the updated iterator.
   */
  edge_iterator& operator++() {
    ++current_;
    return *this;
  }

  /**
   * @brief Returns the edge at the current iterator position. O(1).
   * @return The reference to the current edge.
   */
  const edge_type& operator*() const {
    return iter_[current_];
  }

private:
  std::vector<edge_type> iter_;  ///< The vector of edges.
  std::size_t current_;          ///< The current index of the iterator.
};

/**
 * @brief Templated class representing a range of edges leaving a specific source state.
 * @tparam STATE The state type of the graph.
 * @tparam EDATA The data type associated with the edge.
 */
template<class STATE, class EDATA>
class edge_range {
public:
  friend class graph<STATE, EDATA>;

  using edge_type = graph<STATE, EDATA>::edge_type;
  using edge_iterator_type = graph<STATE, EDATA>::edge_iterator_type;

  /**
   * @brief Constructs an edge range with the given vector of edges and source state. O(1).
   * @param edges The vector of edges.
   * @param src The source state of the edges in the range.
   */
  edge_range(const std::vector<edge_type>& edges, const STATE& src)
    : edges_(edges), src_(src)
  {}

  /**
   * @brief Returns the iterator pointing to the beginning of the edge range. O(1).
   * @return The iterator pointing to the beginning.
   */
  edge_iterator_type begin() const {
    return edge_iterator_type(edges_, 0);
  }

  /**
   * @brief Returns the iterator pointing to the end of the edge range. O(1).
   * @return The iterator pointing to the end.
   */
  edge_iterator_type end() const {
    return edge_iterator_type(edges_, edges_.size());
  }

private:
  const std::vector<edge_type>& edges_;  ///< The vector of edges.
  const STATE& src_;                     ///< The source state of the edges.
};

/**
 * @brief Templated class representing a graph.
 * @tparam STATE The state type of the graph.
 * @tparam EDATA The data type associated with the edge.
 */
template<class STATE, class EDATA>
class graph {
public:
  using edge_type = edge<STATE, EDATA>;
  using edge_iterator_type = edge_iterator<STATE, EDATA>;
  using edge_range_type = edge_range<STATE, EDATA>;
  using edge_vector_type = std::vector<edge_type>;
  using data_type = EDATA;


  graph() = default;
  graph(const graph&) = default;
  graph(graph&&) = default;
  graph& operator=(const graph&) = default;
  graph& operator=(graph&&) = default;

  /**
   * @brief Adds an edge to the graph. O(1).
   * @param src The source state of the edge.
   * @param dst The destination state of the edge.
   * @param data The data associated with the edge.
   */
  void add_edge(const STATE& src, const STATE& dst, const EDATA& data) {
      edges_.emplace_back(src, dst, data);
  }

  /**
   * @brief Returns a vector of all states existing in the graph.
   * @return The vector of states.
   * @note The time complexity is O(|E| + |V|), where |E| is the number of edges and |V| is the number of vertices (states).
   */
  std::vector<STATE> states() {
    std::vector<STATE> states;
    for (const auto& val : edges_){
      if (std::find(states.begin(), states.end(), val.src()) == states.end()) {
        states.push_back(val.src());
      }

      if (std::find(states.begin(), states.end(), val.dst()) == states.end()) {
        states.push_back(val.dst());
      }
    }

    return states;
  }

  /**
   * @brief Returns an edge range corresponding to the edges leaving a specific source state.
   * @param s The source state.
   * @return The edge range.
   * @note The time complexity is O(|E|), where |E| is the number of edges in the graph.
   */
  edge_range_type out(const STATE& s) {
    filteredEdges.clear();
    for (const auto& edge : edges_) {
      if (edge.src() == s) {
        filteredEdges.push_back(edge);
      }
    }
    return edge_range_type(filteredEdges, s);
  }

  /**
   * @brief Reads edge data from the input stream and adds the edges to the graph.
   * @param is The input stream.
   * @param nstates The expected number of states (optional, default is 0).
   * @param nedges The expected number of edges (optional, default is 0).
   */
  void read_edge_stream(std::istream& is, std::size_t nstates = 0, std::size_t nedges = 0) {
    std::string line;
    while (std::getline(is, line)) {
      std::istringstream iss(line);

      STATE srcState;
      STATE dstState;
      EDATA edgeData;
      iss >> srcState >> dstState >> edgeData;

      this->add_edge(srcState, dstState, edgeData);
    }
    return;
  }

  /**
   * @brief Returns the vector of all edges in the graph.
   * @return The vector of edges.
   */
  edge_vector_type getEdges() {
    return edges_;
  }

private:
  edge_vector_type edges_;          ///< The vector of edges in the graph.
  edge_vector_type filteredEdges;   ///< The vector of filtered edges.
};