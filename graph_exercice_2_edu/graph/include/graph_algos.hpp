#pragma once

#include "graph.hh"
#include <ranges>
#include <limits>
#define INF 999
// Actual implementation
namespace
{
    // Implement Floyd-Warshall
    template <template <class, class> class GRAPH, class STATE, class EDATA>
    EDATA shortest_distance_(GRAPH<STATE, EDATA> g, const STATE &src, const STATE &dst,
                             EDATA zero, EDATA infinite)
    {
        std::unordered_map<STATE, std::unordered_map<STATE, EDATA>> distances;

        // Initialize distances with infinite values
        for (const auto &state1 : g.states())
        {
            for (const auto &state2 : g.states())
            {
                distances[state1][state2] = (state1 == state2) ? zero : infinite;
            }
        }

        // Update distances based on existing edges
        for (const auto &edge : g.getEdges())
        {
            distances[edge.src()][edge.dst()] = edge.data();
        }


        // Perform Floyd-Warshall algorithm
        for (const auto &k : g.states())
        {
            for (const auto &i : g.states())
            {
                for (const auto &j : g.states())
                {
                    if (distances[i][k] == infinite || distances[k][j] == infinite)
                        continue;
                
                    if (distances[i][k] + distances[k][j] < distances[i][j])
                    {
                        distances[i][j] = distances[i][k] + distances[k][j];
                    }
                }
            }
        }

        return distances[src][dst];
    }
}

// API function
template <class GRAPH, class STATE>
auto shortest_distance(GRAPH &g, const STATE &src, const STATE &dst)
{
    using EDATA = typename GRAPH::data_type;
    EDATA zero = 0;
    EDATA infinite = std::numeric_limits<EDATA>::max();

    return shortest_distance_(g, src, dst, zero, infinite);
}