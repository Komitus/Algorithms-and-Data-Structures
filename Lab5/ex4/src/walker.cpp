#include "walker.hpp"

void Walker::resetEdges(){
    edges.clear();
    edges.shrink_to_fit();
    std::cout<<edges.size() << std::endl;
}
Walker::~Walker(){
    edges.clear();
    edges.shrink_to_fit();
}
void Walker::add_edge (uint32_t u, uint32_t v, double weight) {
    if (u < start_index || u > graph_size || v < start_index || v > graph_size || weight < 0.0) {
        std::cerr << "Wrong vertex value!" << std::endl;
        return;
    }

    for (uint32_t i = 0; i < edges.size(); i++) {
        Edge e = edges.at(i);
        if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
            std::cerr << "Edge containing this vertex exists!" << std::endl;
            return;
        }
    }

    edges.push_back(Edge(u, v, weight));
}

double Walker::find_edge(uint32_t u, uint32_t v) {
    for (uint32_t i = 0; i < edges.size(); i++) {
        Edge e = edges.at(i);

        if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
            return e.weight;
        }
    }
}