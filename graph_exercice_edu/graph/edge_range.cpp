#include "include/graph.hh"

template<class STATE, class EDATA>
edge_range<STATE, EDATA>::edge_range(const std::vector<edge_range<STATE, EDATA>::edge_type>& edges, const STATE& src)
    : edges_(edges), src_(src)
    {}

template<class STATE, class EDATA>
edge_range<STATE, EDATA>::edge_iterator_type edge_range<STATE, EDATA>::begin() const {
    auto i = 0;
    for (i; i < edges_.size(); i++){
        if (edges_[i].src() == src_)
            break;
    }

    return edge_iterator_type(edges_, i);
}

template<class STATE, class EDATA>
edge_range<STATE, EDATA>::edge_iterator_type edge_range<STATE, EDATA>::end() const {
    return edge_iterator_type(edges_, edges_.size());
}

