#ifndef _structure_classess
#define _structure_classess
#include <vector>
#include <cstdint>
#include "priority_queue.hpp"
#include "randGen.hpp"

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

struct VisitVertex{
public:
    uint32_t key;
    bool visited;

    VisitVertex(uint32_t key, bool visited) {
        this->key = key;
        this->visited = visited;
    }
};

struct {
    bool operator() (Edge e1, Edge e2) {
        return e1.weight < e2.weight;
    }
} edges_comp;


class MST {

public:
    ~MST(){};
    uint32_t compares = 0; 
    virtual void add_edge(uint32_t u, uint32_t v, double weight) = 0;
    virtual std::vector<Edge> find_mst() = 0;
};

struct Stats {
    unsigned long steps = 0;
    double weight = 0.0;
    uint32_t mem = 0;
};
void perform_test();
#endif