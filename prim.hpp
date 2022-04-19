#pragma once

#include "weightedGraph.hpp"
#include <queue>
#include <iostream>

// https://algotree.org/algorithms/minimum_spanning_tree/prims_c++/

template <typename VType>
class Prim {
    WeightedGraph<VType> g;
    std::vector<std::tuple<VType, VType, int>> mst;
    VType root;

public:
    Prim(WeightedGraph<VType> g, VType root) : g(g), root(root) {}

    std::vector<std::tuple<VType, VType, int>> getMst() {
        std::priority_queue<std::pair<int, VType>,
                            std::vector<std::pair<int, VType>>,
                            std::greater<std::pair<int, VType>>> pq;

        std::unordered_map<VType, VType> parent;

        std::unordered_map<VType, int> key;
        std::unordered_map<VType, bool> visited;

        for (auto vertex: g.edges) {
            visited[vertex.first] = false;
            key[vertex.first] = 0x3f3f3f3f;
        }

        pq.push(std::make_pair(0, root));
        key[root] = 0;

        while (!pq.empty()) {
            auto u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (auto x: g.edges[u]) {
                VType v = x.first;
                int weight = x.second;

                if (!visited[v] && key[v] > weight) {
                    key[v] = weight;
                    pq.push(std::make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }

        for (auto pair: parent) {
            mst.push_back(std::make_tuple(pair.first, 
                                          pair.second, 
                                          g.edges[pair.first][pair.second]));
        }

        return mst;
    }
};