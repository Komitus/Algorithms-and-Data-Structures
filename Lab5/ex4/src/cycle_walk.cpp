#include "cycle_walk.hpp"

CycleWalk::CycleWalk(uint32_t graph_size, uint32_t start_index) {
    this->graph_size = graph_size;
    this->start_index = start_index;
}
CycleWalk::~CycleWalk() {
    vertices.clear();
}

void CycleWalk::add_edges (std::vector<Edge> edges) {
    this->edges = edges;
}

void CycleWalk::walk(bool print) {
    //bcs i must have created it with MST algorithm
    stats.mem += sizeof(edges);
    for (uint32_t i = start_index; i < graph_size - start_index; i++) {
        std::shared_ptr<EulerVertex> v = std::make_shared<EulerVertex>(i, NOT_VISITED);
        vertices.push_back(v);
        stats.mem += sizeof(v);
    }

    std::vector<std::vector<std::shared_ptr<EulerVertex>>> adj(graph_size);
    for (uint32_t i = 0; i < edges.size(); i++) {
        
        Edge e = edges.at(i);
        adj.at(e.u - start_index).push_back(vertices.at(e.v - start_index));
        adj.at(e.v - start_index).push_back(vertices.at(e.u - start_index));
    }

    stats.mem += sizeof(adj);

    uint32_t visited_vertices = 0;

    uint32_t start = 0;
    std::vector<std::shared_ptr<EulerVertex>> curr_adj = adj.at(start);
    std::shared_ptr<EulerVertex> curr = vertices.at(start);

    stats.mem += sizeof (curr);
    stats.mem += sizeof (curr_adj);

    uint32_t next;

    while (visited_vertices < graph_size) {
        next = UINT32_MAX;    
        enum state state;
        
        stats.steps++;

        for (uint32_t i = 0; i < curr_adj.size(); i++) {
            if (curr_adj.at(i)->visit == NOT_VISITED) {
                next = i;
                break;
            }
        }
        
        if (next == UINT32_MAX) {
            for (uint32_t i = 0; i < curr_adj.size(); i++) {
                if (curr_adj.at(i)->visit == VISITED_ONCE) {
                    next = i;
                    break;
                }
            }
            state = VISITED_TWICE;

        } else {
            state = VISITED_ONCE;
        }

        if (next == UINT32_MAX) {
            next = start;
        }

        curr->visit = state;
        curr_adj.at(next)->visit = state;

        stats.weight += find_edge (curr->key, curr_adj.at(next)->key);

        if (curr->visit == VISITED_TWICE) {
            visited_vertices++;
        }

        if(print){
            std::cerr << curr->key << " -> ";
        }
        
        curr = vertices.at(curr_adj.at(next)->key - start_index);
        curr_adj = adj.at(curr_adj.at(next)->key - start_index);
        if(print){
            std::cerr << curr->key << std::endl;
        }
        
    }
    if(print){
        std::cout << stats.steps << " " << stats.weight << " " << stats.mem << " " << std::endl; 
    } 
}
