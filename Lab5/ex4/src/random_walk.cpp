#include "random_walk.hpp"

RandomWalk::RandomWalk(uint32_t graph_size, uint32_t start_index) {
    this->graph_size = graph_size;
    this->start_index = start_index;
}

RandomWalk::~RandomWalk() {
    vertices.clear();
    vertices.shrink_to_fit();
}

void RandomWalk::walk(bool print) {

    for (uint32_t i = start_index; i < graph_size + start_index; i++) {
        std::shared_ptr<VisitVertex> v = std::make_shared<VisitVertex>(i, false);
        stats.mem += sizeof (v);
        vertices.push_back(v);
    }

    std::vector<std::vector<std::shared_ptr<VisitVertex>>> adj(graph_size);

    for (uint32_t i = 0; i < edges.size(); i++) {
        Edge e = edges.at(i);
        adj.at(e.u - start_index).push_back(vertices.at(e.v - start_index));
        adj.at(e.v - start_index).push_back(vertices.at(e.u - start_index));
    }

    stats.mem += sizeof (adj);

    uint32_t visited_vertices = 0;
    uint32_t start = getRand(start_index, graph_size-1) - start_index;

    std::vector<std::shared_ptr<VisitVertex>> curr_adj = adj.at(start);
    std::shared_ptr<VisitVertex> curr = vertices.at(start);
    stats.mem += sizeof(curr);
    stats.mem += sizeof(curr_adj);

    while (visited_vertices < graph_size) {
        if (!curr->visited) {
            visited_vertices++;
            curr->visited = true;
        }
        stats.steps++;
        

        uint32_t next = getRand(0, curr_adj.size()-1);

        stats.weight += Walker::find_edge(curr->key, curr_adj.at(next)->key);
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
    vertices.clear();
    adj.clear();
}
