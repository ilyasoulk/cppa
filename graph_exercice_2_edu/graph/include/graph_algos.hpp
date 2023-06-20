#pragma once

#include "graph.hh"
#include <ranges>
#include <limits>

// Actual implementation
namespace {
// Implement Floyd-Warshall
template<template<class, class> class GRAPH, class STATE, class EDATA>
EDATA shortest_distance_(GRAPH<STATE, EDATA> g, const STATE& src, const STATE& dst ,
                         EDATA zero, EDATA one){

}
}

// API function
template<class GRAPH, class STATE>
auto shortest_distance(GRAPH& g, const STATE& src, const STATE& dst){

}