#include "kruskal.hpp"
#include <algorithm>
#include <math.h> 

Kruskal::Kruskal(uint32_t graph_size, uint32_t starting_vertex) {
    this->graph_size = graph_size;
    this->starting_vertex = starting_vertex;
}

Kruskal::~Kruskal () {
    vertexes.clear();
    edges.clear();
}

void Kruskal::add_edge (uint32_t u, uint32_t v, double weight) {
    if (u < starting_vertex || u > graph_size || v < starting_vertex || v > graph_size || weight < 0.0) {
        std::cout << "Wrong edge input" << std::endl;
        return;
    }

    for (uint32_t i = 0; i < edges.size(); i++) {
        Edge e = edges.at(i);
        if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
            return;
        }
    }

    edges.push_back(Edge(u, v, weight));
}


std::vector<Edge> Kruskal::find_mst() {
    std::vector<Edge> path;
    compares = 0;
    DisjointSets *ds = new DisjointSets();

    for (uint32_t i = starting_vertex; i < graph_size + starting_vertex; i++) {
        //avoid making copy of shared_ptr
        vertexes.push_back(std::make_shared<Vertex>(i));
        ds->make_set(vertexes.at(i-starting_vertex).get());
    }
    uint32_t sort_compares = (uint32_t)edges.size() * static_cast<uint32_t>(log(edges.size()) + 0.5);
    //std::cout << std::endl << std::endl << sort_compares << std::endl <<std::endl;
    compares += sort_compares;
    std::sort(edges.begin(), edges.end(), edges_comp);

    for (uint32_t i = 0; i < edges.size(); i++) {
        Edge e = edges.at(i);
        compares++;
        if (ds->find_set(vertexes.at(e.u - starting_vertex).get()) != ds->find_set(vertexes.at(e.v - starting_vertex).get())) {
            path.push_back(edges.at(i));
            ds->make_union(vertexes.at(e.u - starting_vertex).get(), vertexes.at(e.v - starting_vertex).get());
        }
    }
    compares = compares + ds->compares;
    delete ds;
    return path;
}

DisjointSets::DisjointSets() {}

DisjointSets::~DisjointSets() {}

void DisjointSets::make_set (Vertex *x) {
    x->parent = x;
    x->rank = 0;
}

Vertex *DisjointSets::find_set(Vertex *x) {
    compares++;
    if (x != x->parent) {
        x->parent = find_set(x->parent);
    }

    return x->parent;
}

void DisjointSets::link(Vertex *x, Vertex *y) {
    compares++;
    if (x->rank > y->rank) {
        y->parent = x;
    } else {
        x->parent = y;
        compares++;
        if (x->rank == y->rank) {
            y->rank++;
        }
    }
}

void DisjointSets::make_union(Vertex *x, Vertex *y) {
    link(find_set(x), find_set(y));
}