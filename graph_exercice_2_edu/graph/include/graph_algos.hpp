#pragma once

#include "graph.hh"
#include <ranges>
#include <limits>
#include <string.h>
namespace
{
    /**
     * @brief Calculates the shortest distance between two states in a graph.
     * O(n^3) with n being the number of states
     * @tparam GRAPH The graph type.
     * @tparam STATE The state type.
     * @tparam EDATA The data type associated with the edge.
     * @param g The graph.
     * @param src The source state.
     * @param dst The destination state.
     * @param zero The zero value of the data type.
     * @param infinite The infinite value of the data type.
     * @return The shortest distance between src and dst.
     */
    template <template <class, class> class GRAPH, class STATE, class EDATA>
    EDATA shortest_distance_(GRAPH<STATE, EDATA> g, const STATE &src, const STATE &dst,
                             EDATA zero, EDATA infinite)
    {
        std::unordered_map<STATE, std::unordered_map<STATE, EDATA>> distances;

        for (const auto &state1 : g.states())
        {
            for (const auto &state2 : g.states())
            {
                distances[state1][state2] = (state1 == state2) ? zero : infinite;
            }
        }

        for (const auto &edge : g.getEdges())
        {
            distances[edge.src()][edge.dst()] = edge.data();
        }

        if constexpr (std::is_same<EDATA, char>::value)
        {
            for (const auto &k : g.states())
            {
                for (const auto &i : g.states())
                {
                    for (const auto &j : g.states())
                    {
                        if (distances[i][k] == infinite || distances[k][j] == infinite)
                            continue;
                        auto dist = (int(distances[i][k]) + int(distances[k][j])) % 127;
                        if (dist < int(distances[i][j]))
                        {
                            distances[i][j] = char(dist);
                        }
                    }
                }
            }
        }

        if constexpr (std::is_same<EDATA, std::string>::value)
        {
            for (const auto &k : g.states())
            {
                for (const auto &i : g.states())
                {
                    for (const auto &j : g.states())
                    {
                        if (distances[i][k].compare(infinite) == 0 || distances[k][j].compare(infinite) == 0)
                            continue;

                        if (distances[i][k].length() + distances[k][j].length() < distances[i][j].length())
                        {
                            distances[i][j] = distances[i][k] + distances[k][j];
                        }
                    }
                }
            }
        }
        else
        {
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
        }

        return distances[src][dst];
    }
}

// API function
/**
 * @brief Calculates the shortest distance between two states in a graph.
 * @tparam GRAPH The graph type.
 * @tparam STATE The state type.
 * @param g The graph.
 * @param src The source state.
 * @param dst The destination state.
 * @return The shortest distance between src and dst.
 */
template <class GRAPH, class STATE>
auto shortest_distance(GRAPH &g, const STATE &src, const STATE &dst)
{
    using EDATA = typename GRAPH::data_type;
    EDATA zero;
    EDATA infinite;
    if constexpr (std::is_same_v<EDATA, std::string>) {
        zero = "";
        infinite = "infinity";
    }   

    else if constexpr (std::is_same_v<EDATA, char>) {
        zero = char(0);
        infinite = std::numeric_limits<int>::max();
    }
    
    else {
        zero = 0;
        infinite = std::numeric_limits<EDATA>::max();
    }

    return shortest_distance_(g, src, dst, zero, infinite);
}
