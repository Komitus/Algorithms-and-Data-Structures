#ifndef _structure_classess
#define _structure_classess
#include <vector>
#include <cstdint>
#include "priority_queue.hpp"

struct Edge {
    uint32_t u;
    uint32_t v;
    double weight;

    Edge(uint32_t u, uint32_t v, double weight) {
        this->u = u;
        this->v = v;
        this->weight = weight;
    }
};

struct {
    bool operator() (Edge e1, Edge e2) {
        return e1.weight < e2.weight;
    }
} edges_comp;

struct Vertex{
public:
    Vertex *parent;
    uint32_t key;
    uint32_t rank;

    Vertex(uint32_t key)
    {
        this->key = key;
    }
};

class MST {

public:
    uint32_t compares = 0; 
    virtual void add_edge(uint32_t u, uint32_t v, double weight) = 0;
    virtual std::vector<Edge> find_mst() = 0;
    ~MST(){};
};

void perform_test();
#endif