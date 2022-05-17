#include "weightedGraph.hpp"
#include "kruskal.hpp"
#include "prim.hpp"
#include <vector>
#include <iostream>

void fillGraph(WeightedGraph<char>& g) {
    g.addVertex('a');
    g.addVertex('b');
    g.addVertex('c');
    g.addVertex('d');
    g.addVertex('e');
    g.addVertex('f');
    g.addVertex('g');
    g.addVertex('h');
    g.addVertex('i');

    g.addEdge('a', 'b', 4);
    g.addEdge('a', 'h', 8);
    g.addEdge('b', 'c', 8);
    g.addEdge('b', 'h', 11);
    g.addEdge('c', 'd', 7);
    g.addEdge('c', 'f', 4);
    g.addEdge('c', 'i', 2);
    g.addEdge('d', 'e', 9);
    g.addEdge('d', 'f', 10);
    g.addEdge('e', 'f', 10);
    g.addEdge('f', 'g', 2);
    g.addEdge('g', 'h', 1);
    g.addEdge('g', 'i', 6);
    g.addEdge('h', 'i', 7);
}

int main() {
    WeightedGraph<char> g;
    fillGraph(g);

    Kruskal kruskal(g);
    for (auto edge: kruskal.getMst()) {
        std::cout << std::get<0>(edge) << " - "
                    << std::get<1>(edge) << " : "
                    << std::get<2>(edge) << '\n';
    }

    std::cout << '\n';

    Prim prim(g, 'a');
    for (auto edge: prim.getMst()) {
        std::cout << std::get<0>(edge) << " - "
                    << std::get<1>(edge) << " : "
                    << std::get<2>(edge) << '\n';
    }
}
