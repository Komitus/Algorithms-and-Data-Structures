#include "weight_walk.hpp"

WeightWalk::WeightWalk(uint32_t graph_size, uint32_t start_index) {
    this->graph_size = graph_size;
    this->start_index = start_index;
}

WeightWalk::~WeightWalk() {
    vertices.clear();
}

void WeightWalk::walk(bool print) {

    for (uint32_t i = start_index; i < graph_size + start_index; i++) {
        std::shared_ptr<VisitVertex> v = std::make_shared<VisitVertex>(i, false);
        vertices.push_back(v);
        stats.mem += sizeof(v);
    }

    std::vector<std::vector<std::shared_ptr<NextVertex>>> adj(graph_size);

    for (uint32_t i = 0; i < edges.size(); i++) {
        Edge e = edges.at(i);
        adj.at(e.u - start_index).push_back(std::make_shared<NextVertex>(vertices.at(e.v - start_index), e.weight));
        adj.at(e.v - start_index).push_back(std::make_shared<NextVertex>(vertices.at(e.u - start_index), e.weight));
    }

    stats.mem += sizeof(adj);

    uint32_t visited_vertices = 0;

    uint32_t start = getRand(start_index, graph_size-1) - start_index;

    std::vector<std::shared_ptr<NextVertex>> curr_adj = adj.at(start);
    std::shared_ptr<VisitVertex> curr = vertices.at(start);

    stats.mem += sizeof (curr);
    stats.mem += sizeof (curr_adj);
    uint32_t prev_visited = 0;
    while (visited_vertices < graph_size) {
        if (!curr->visited) {
            visited_vertices++;
            curr->visited = true;
        }
        stats.steps++;

        double min_weight = curr_adj.at(0)->weight;
        uint32_t next = curr_adj.at(0)->next->key - start_index;
        uint32_t i;
        uint32_t tmp_weight;
        uint8_t changed = 0;
        for (i = 0; i < curr_adj.size(); i++) {
            tmp_weight = curr_adj.at(i)->weight;
            if (tmp_weight < min_weight && !curr_adj.at(i)->next->visited) {
                min_weight = tmp_weight;
            } 
        }
        if(prev_visited == visited_vertices){
            i = getRand(0, curr_adj.size()-1);
        } else {
            i--;
        }
        next = curr_adj.at(i)->next->key - start_index;

        stats.weight += Walker::find_edge(curr->key, next);

        if(print){
            std::cerr << curr->key << " -> ";
        }
            
        curr = vertices.at(next);
        curr_adj = adj.at(next);
              
        if(print){
            std::cerr << curr->key << std::endl;
        } 
        prev_visited = visited_vertices; 
    }
    if(print){
        std::cout << stats.steps << " " << stats.weight << " " << stats.mem << " " << std::endl; 
    }
    vertices.clear();
    adj.clear();
}

