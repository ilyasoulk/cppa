#include "include/graph.hh"

template<class STATE, class EDATA>
edge_iterator<STATE, EDATA>::edge_iterator(const typename std::vector<edge_iterator<STATE, EDATA>::edge_type>::const_iterator& iter)
    : iter_(iter)
    {}

template<class STATE, class EDATA>
bool edge_iterator<STATE, EDATA>::operator!=(const edge_iterator<STATE, EDATA>& rhs) const {
    return iter_ != rhs.iter_;
}

template<class STATE, class EDATA>
bool edge_iterator<STATE, EDATA>::operator==(const edge_iterator<STATE, EDATA>& rhs) const {
    return !(*this != rhs);
}

template<class STATE, class EDATA>
const edge_iterator<STATE, EDATA>::edge_type& edge_iterator<STATE, EDATA>::operator*() const {
    return *iter_;
}

template<class STATE, class EDATA>
edge_iterator<STATE, EDATA>& edge_iterator<STATE, EDATA>::operator++() {
    ++iter_;
    return *this;
}


