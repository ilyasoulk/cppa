#include "include/graph.hh"

template<class STATE, class EDATA>
edge<STATE, EDATA>::edge(const STATE& src, const STATE& dst, const EDATA& data)
    : src_(src), dst_(dst), data_(data)
    {}

template<class STATE, class EDATA>
const STATE& edge<STATE, EDATA>::src() const {
    return src_;
}

template<class STATE, class EDATA>
const STATE& edge<STATE, EDATA>::dst() const {
    return dst_;
}

template<class STATE, class EDATA>
const EDATA& edge<STATE, EDATA>::data() const {
    return data_;
}