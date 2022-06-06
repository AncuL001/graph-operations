#include "weightedGraph.hpp"
#include "kruskal.hpp"
#include "prim.hpp"
#include <vector>
#include <iostream>

void fillGraph(WeightedGraph<char>& g) {
    g.addVertex('0');
    g.addVertex('1');
    g.addVertex('2');
    g.addVertex('3');
    g.addVertex('4');

    g.addEdge('0', '1', 3);
    g.addEdge('0', '3', 7);
    g.addEdge('0', '4', 8);
    g.addEdge('1', '2', 1);
    g.addEdge('1', '3', 4);
    g.addEdge('2', '3', 2);
    g.addEdge('3', '4', 3);
}


template <typename VType>
void showEdgeListMenu(WeightedGraph<VType>& g) {
    for (auto edge: g.getAllEdges()) {
        std::cout << std::get<0>(edge) << " -- "
                  << std::get<1>(edge) << " : "
                  << std::get<2>(edge) << "\n";
    }
}

template <typename VType>
void addVertexMenu(WeightedGraph<VType>& g) {
    while (true) {
        VType val;

        std::cout << "Masukkan nama vertex (0: Kembali): ";
        std::cin >> val;

        if (val == '0') return;

        try {
            g.addVertex(val);
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            continue;
        }
        return;
    }
}

template <typename VType>
void addEdgeMenu(WeightedGraph<VType>& g) {
    while (true) {
        VType val1, val2;
        int weight;

        std::cout << "Masukkan nama vertex 1 (0: Kembali): ";
        std::cin >> val1;
        if (val1 == '0') return;

        std::cout << "Masukkan nama vertex 2 (0: Kembali): ";
        std::cin >> val2;
        if (val2 == '0') return;

        std::cout << "Masukkan weight (0: Kembali): ";
        std::cin >> weight;
        if (weight == 0) return;

        try {
            g.addEdge(val1, val2, weight);
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            continue;
        }
        return;
    }
}

template <typename VType>
void traversalMenu(WeightedGraph<VType>& g) {
    std::cout << "1. Kruskal\n"
              << "2. Prim\n"
              << "0. Kembali\n"
              << "Menu: ";

    int op;
    std::cin >> op;

    switch (op) {
    case 1:
        kruskal(g);
        break;
    
    case 2:
        prim(g);
        break;

    default:
        break;
    }
}

template <typename VType>
void kruskal(WeightedGraph<VType>& g) {
    Kruskal kruskal(g);
    for (auto edge: kruskal.getMst()) {
        std::cout << std::get<0>(edge) << " - "
                    << std::get<1>(edge) << " : "
                    << std::get<2>(edge) << '\n';
    }
}

template <typename VType>
void prim(WeightedGraph<VType>& g) {
    VType startVertex;

    while (true) {
        std::cout << "Vertex pertama (0: Kembali): ";
        std::cin >> startVertex;
        if (startVertex == '0') return;

        if (g.edges.find(startVertex) == g.edges.end()) {
            std::cout << "vertex tidak ditemukan";
            continue;
        }

        break;
    }

    Prim prim(g, startVertex);
    for (auto edge: prim.getMst()) {
        std::cout << std::get<0>(edge) << " - "
                    << std::get<1>(edge) << " : "
                    << std::get<2>(edge) << '\n';
    }
}

int main() {
    WeightedGraph<char> g;

    while (true) {
        std::cout << "1. Lihat daftar edge\n"
                  << "2. Tambahkan vertex\n"
                  << "3. Tambahkan edge\n"
                  << "4. Traversal\n";

        if (g.edges.size() == 0) 
            std::cout << "5. Isi graph dengan graph template\n";

        std::cout << "0. Keluar\n"
                  << "Menu: ";

        int op;
        std::cin >> op;

        switch (op) {
        case 1:
            showEdgeListMenu(g);
            break;

        case 2:
            addVertexMenu(g);
            break;

        case 3:
            addEdgeMenu(g);
            break;

        case 4:
            traversalMenu(g);
            break;

        case 5:
            fillGraph(g);
            break;

        case 0:
            return 0;

        default:
            break;
        }
    }
}
