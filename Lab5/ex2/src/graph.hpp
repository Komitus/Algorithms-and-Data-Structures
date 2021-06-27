#ifndef _graph
#define _graph

#include "priority_queue.hpp"
#include <memory>

struct Data {
    uint32_t compares = 0;
    bool print = false;
};

struct Edge {
    uint32_t start;
    uint32_t end;

    double weight;

    Edge(uint32_t start, uint32_t end, double weight) {
        this->start = start;
        this->end = end;
        this->weight = weight;
    }
    Edge(){}
};

struct Neighbour {
    std::shared_ptr<Element> vertex;
    double weight;

    Neighbour (std::shared_ptr<Element> vertex, double weight) {
        this->vertex = vertex;
        this->weight = weight;
    }
};

class Graph {
private:
    uint32_t graph_size;
    std::vector<Edge> edges;
    //std::vector<std::shared_ptr<Element>> vertexes;
    void initialize_single_source (PriorityQueue *pq, uint32_t source);
    void print_paths(std::vector<std::shared_ptr<Element>> S);
    
   
public:
    Graph(uint32_t graph_size, uint32_t first_index);
    ~Graph();
    uint32_t index_correction;
    std::vector<std::shared_ptr<Element>> dijkstra_shortest_path(uint32_t source, uint32_t *compares);
    void add_edge(uint32_t start, uint32_t end, double weight);
};

void perform_test();
#endif