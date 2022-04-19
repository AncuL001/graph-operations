#pragma once

#include "weightedGraph.hpp"
#include <unordered_map>
#include <vector>
#include <algorithm>

// https://www.programiz.com/dsa/kruskal-algorithm

template <typename VType>
class Kruskal {
    WeightedGraph<VType> g;
    std::unordered_map<VType, VType> parent;
    std::vector<std::tuple<VType, VType, int>> mst;

public:
    Kruskal(WeightedGraph<VType> g): g(g) {
        for (auto vertex: g.edges) {
            parent[vertex.first] = vertex.first;
        }
    }

    VType findSet(VType val) {
        if (val == parent[val]) return val;
        return findSet(parent[val]);
    }

    void unionSet(VType val1, VType val2) {
        parent[val1] = parent[val2];
    }

    std::vector<std::tuple<VType, VType, int>> getMst() {
        if (!mst.empty()) return mst;

        auto edgesVector = g.getAllEdges();
        std::sort(edgesVector.begin(), 
                  edgesVector.end(), 
                  [](std::tuple<VType, VType, int> edge1, std::tuple<VType, VType, int> edge2){
                        return std::get<2>(edge1) < std::get<2>(edge2);
                    }
        );

        for (auto edge: edgesVector) {
            if (findSet(std::get<0>(edge)) != findSet(std::get<1>(edge))) {
                mst.push_back(edge);
                unionSet(std::get<0>(edge), std::get<1>(edge));
            }
        }

        return mst;
    }
};