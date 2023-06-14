#include "include/graph.hh"

template<class STATE, class EDATA>
void graph<STATE, EDATA>::add_edge(const STATE& src, const STATE& dst, const EDATA& data){
    auto edge = edge_type(src, dst, data);
    edges_.push_back(edge);
}

template<class STATE, class EDATA>
std::vector<STATE> graph<STATE, EDATA>::states() {
    std::vector<STATE> states;
    for (const auto& val : edges_){
      if (std::find(states.begin(), states.end(), val.src()) == states.end()) {
        states.push_back(val.src());
      }
    }

    return states;
}

template<class STATE, class EDATA>
graph<STATE, EDATA>::edge_range_type graph<STATE, EDATA>::out(const STATE& s) {
    return edge_range_type(edges_, s);
}