#ifndef _walker
#define _walker
#include "structure_classes.hpp"

class Walker {
protected:
    uint32_t graph_size;
    uint32_t start_index;
    std::vector<Edge> edges;
    double find_edge(uint32_t u, uint32_t v);
public:
    ~Walker();
    Stats stats;
    void add_edge (uint32_t u, uint32_t v, double weight);
    virtual void walk(bool print) = 0;
    void resetEdges();
};
#endif