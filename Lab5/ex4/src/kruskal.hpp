#ifndef _kruskal
#define _kruskal
#include "structure_classes.hpp"

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

class Kruskal : public MST {
private:
    uint32_t graph_size;
    uint32_t starting_vertex;
    std::vector<Edge> edges;
    std::vector<std::shared_ptr<Vertex>> vertexes;
    

public: 
    Kruskal(uint32_t graph_size, uint32_t starting_vertex);
    ~Kruskal();
    void add_edge (uint32_t u, uint32_t v, double weight);
    std::vector<Edge> find_mst();
};

//no need to use const std::shared_ptr<Vertex>& bcs always exist reference in graph.vertexes even after disjoint sets
class DisjointSets {
private:
    void link(Vertex *x, Vertex *y);
public:
    uint32_t compares = 0;  
    DisjointSets();
    ~DisjointSets();

    void make_set(Vertex *x);
    Vertex * find_set(Vertex *x);
    void make_union(Vertex *x, Vertex *y);
};

#endif