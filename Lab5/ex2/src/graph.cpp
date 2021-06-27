#include "graph.hpp"

Graph::Graph(uint32_t graph_size, uint32_t first_index){
    this->graph_size = graph_size;
    index_correction = first_index;
}

Graph::~Graph(){
    //vertexes.clear();
    edges.clear();
}

void Graph::add_edge(uint32_t start, uint32_t end, double weight) {
    //TODO: Comparing to double!!!!
    if (start > graph_size || end > graph_size || weight < 0.0) {
        return;
    }

    edges.push_back(Edge(start, end, weight));
}

void Graph::initialize_single_source (PriorityQueue *pq, uint32_t source) {

    std::shared_ptr<Element> first_e = pq->insert(source, nullptr, 0);
    
    for (uint32_t i = index_correction; i < graph_size + index_correction; i++) {
        if(i != source){
            std::shared_ptr<Element> e = pq->insert(i, nullptr, std::numeric_limits<double>::max());
            //vertexes.push_back(e);
        }
    } 
    /*
    if(source == graph_size - 1 + index_correction) vertexes.push_back(first_e);
    else {
        std::vector<std::shared_ptr<Element>>::iterator it = vertexes.begin();
        std::advance( it, source+1 );
        vertexes.insert(it, first_e); 
    } 
    */
}

std::vector<std::shared_ptr<Element>> Graph::dijkstra_shortest_path(uint32_t source, uint32_t *compares) {
    
    std::vector<std::shared_ptr<Element>> S;
    PriorityQueue *pq = new PriorityQueue();

    //Initialice vertexes
    initialize_single_source(pq, source);

    //Creating adjacency lists.
    std::vector<std::vector<Neighbour>> adj(graph_size);
    for (size_t i = 0; i < edges.size(); i++) {
        Edge e = edges.at(i);
        adj.at(e.start - index_correction).push_back(Neighbour(pq->find(e.end), e.weight));
    }
    
    while (!pq->empty()) {
        double dist = pq->get_queue().at(0)->dist;
        S.push_back(pq->get_queue().at(0));
        uint32_t u = pq->pop();

        //std::cout<<"Popped: " << u <<std::endl;
        std::vector<Neighbour> *l = &adj.at(u - index_correction);
        //std::cout << "Neighbours: ";
        for (uint32_t i = 0; i < l->size(); i++) {
            Neighbour *v = &l->at(i);
            (*compares)++;
            //std::cout << v->vertex->key << "; ";
            if (v->vertex->dist > dist + v->weight) {
                //v->vertex->dist = dist + v->weight;
                v->vertex->parent = new uint32_t(u);
                pq->priority(v->vertex->key, dist + v->weight);
            }
        }
        //std::cout<<std::endl;
    }

    (*compares) += pq->get_compares();
    delete pq;
    for(size_t i = 0; i < adj.size(); i++){
        adj.at(i).clear();
        adj.shrink_to_fit();
    }
    adj.clear();
    adj.shrink_to_fit();
    return S;
}

