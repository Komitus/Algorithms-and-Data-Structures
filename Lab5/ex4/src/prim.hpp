#include "structure_classes.hpp"

struct Neighbour {
    std::shared_ptr<Element> vertex;
    double weight;

    Neighbour (std::shared_ptr<Element> vertex, double weight) {
        this->vertex = vertex;
        this->weight = weight;
    }
};

class Prim : public MST {
private: 
    uint32_t graph_size;
    uint32_t starting_vertex;
    std::vector<Edge> edges;
    std::vector<std::shared_ptr<Element>> vertices;

    void initialize_single_source (PriorityQueue *pq);
    Edge find_edge(uint32_t u, uint32_t v);

public:
    Prim (uint32_t grap_size, uint32_t starting_vertex);
    ~Prim ();

    void add_edge(uint32_t u, uint32_t v, double weight);
    std::vector<Edge> find_mst(); 
};