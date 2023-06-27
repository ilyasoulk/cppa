#pragma once
#include <vector>
#include <algorithm>

// PSC General remarks
// No doc
// No concepts (for instance states need to be equality comparable)
// Many actions very suboptimal
// Graph 1
// Correct: 9/9
// Quality: 1/3
// Doc: 0/3
// Malus: Too late (-1.5), had to adept things to make it work (-1)
// Tot 10/15 -> 11/20

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

template<class STATE, class EDATA>
class edge{
public:
  using state_type = STATE;
  using data_type = EDATA;
  edge(const state_type& src, const state_type& dst, const data_type& data)
    : src_(src), dst_(dst), data_(data)
    {}
  const state_type& src() const { return src_; }
  const state_type& dst() const { return dst_; }
  const data_type& data() const { return data_; }

private:
  // An EDGE needs to know at least his dst and data, depending on your implementation
  // also the src
  state_type src_;
  state_type dst_;
  data_type data_;

};

// An edge iterator must be able to iterate over
// all the edges having a common src state
template<class STATE, class EDATA>
class edge_iterator{
public:
  using edge_type = graph<STATE, EDATA>::edge_type;

  edge_iterator(const std::vector<edge_type>& iter, std::size_t current)
    : iter_(iter), current_(current)
    {}
  bool operator!=(const edge_iterator& rhs) const { return current_ != rhs.current_; }
  bool operator==(const edge_iterator& rhs) const { return !(*this != rhs); }
  edge_iterator& operator++() {
    ++current_;
    return *this;
  }

  const edge_type& operator*() const {
    return iter_[current_];
  }


private:
  std::vector<edge_type> iter_;
  std::size_t current_;

};

// Wrapper class constructed for a certain state src; needs to give access
// to the begin and end iterator of the edges leaving src
template<class STATE, class EDATA>
class edge_range {
public:
  friend  class graph<STATE, EDATA>;

  using edge_type = graph<STATE, EDATA>::edge_type;
  using edge_iterator_type = graph<STATE, EDATA>::edge_iterator_type;

  edge_range(const std::vector<edge_type>& edges, const STATE& src)
    : edges_(edges), src_(src)
    {}

  edge_iterator_type begin() const {
    return edge_iterator_type(edges_, 0);
  }

  edge_iterator_type end() const {
    return edge_iterator_type(edges_, edges_.size());
  }

private:
  const std::vector<edge_type>& edges_;
  const STATE& src_;
};


// The actual graph
// For the moment we only need three functionalities
// add_edge: taking a src, dst and an edge label
// states(): Must return a range over all states existing in the graph
// out(s): Return the edge_range corresponding to s
template<class STATE, class EDATA>
class graph {
public:
  using edge_type = edge<STATE, EDATA>;
  using edge_iterator_type = edge_iterator<STATE, EDATA>;
  using edge_range_type = edge_range<STATE, EDATA>;
  using edge_vector_type = std::vector<edge_type>;

  graph() = default;
  graph(const graph&) = default;
  graph(graph&&) = default;
  graph& operator=(const graph&) = default;
  graph& operator=(graph&&) = default;

  void add_edge(const STATE& src, const STATE& dst, const EDATA& data) { // PSC could be improved, think about universal reference
      edges_.emplace_back(src, dst, data);
  }

  std::vector<STATE> states() { // PSC Same and stop sharing too much with francois
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

  edge_range_type out(const STATE& s) { // PSC this should not contruct something new but iterate over something that exists
    filteredEdges.clear();
    for (const auto& edge : edges_) {
      if (edge.src() == s) {
        filteredEdges.push_back(edge);
      }
    }
    return edge_range_type(filteredEdges, s);
  }

private:
  edge_vector_type edges_;
  edge_vector_type filteredEdges;
};
