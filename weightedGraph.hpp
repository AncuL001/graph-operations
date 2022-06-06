#pragma once

#include <unordered_map>
#include <stdexcept>
#include <vector>
#include <set>
#include <tuple>

template <typename VType> 
class WeightedGraph {
public:
    std::unordered_map<VType, std::unordered_map<VType, int>> edges;

    void addVertex(VType val) {
        if (edges.find(val) != edges.end())
            throw std::invalid_argument( "vertex sudah ada" );

        edges.insert(std::make_pair(val, std::unordered_map<VType, int>()));
    }

    void addEdge(VType val1, VType val2, int weight) {
        if (weight <= 0) throw std::invalid_argument( "weight tidak bisa negatif" );
        if (edges.find(val1) == edges.end() || edges.find(val2) == edges.end()) 
            throw std::invalid_argument( "vertex tidak ditemukan" );

        if (edges.find(val1) != edges.end() && edges[val1].find(val2) != edges[val1].end() )
            throw std::invalid_argument( "edge sudah ada" );

        edges[val1].insert(std::make_pair(val2, weight));
        edges[val2].insert(std::make_pair(val1, weight));
    }

    std::vector<std::tuple<VType, VType, int>> getAllEdges() {
        std::set<std::tuple<VType, VType, int>> edgesSet;

        for (auto v: edges)
            for (auto e: v.second)
                if (edgesSet.find(std::make_tuple(e.first, v.first, e.second)) == edgesSet.end())
                    edgesSet.insert(std::make_tuple(v.first, e.first, e.second));

        std::vector<std::tuple<VType, VType, int>> edgesVector;

        for (auto edge: edgesSet) {
            edgesVector.push_back(edge);
        }

        return edgesVector;
    }
};