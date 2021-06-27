#include "prim.hpp"

Prim::Prim (uint32_t graph_size, uint32_t starting_vertex){
    this->graph_size = graph_size;
    this->starting_vertex = starting_vertex;
}

Prim::~Prim() {
    //vertices.clear();
    edges.clear();
}

void Prim::initialize_single_source (PriorityQueue *pq) {
    for (uint32_t i = starting_vertex; i < graph_size + starting_vertex; i++) {
        std::shared_ptr<Element> e = pq->insert(i, 0, std::numeric_limits<double>::max());
        //vertices.push_back(e);
    }
}

void Prim::add_edge(uint32_t u, uint32_t v, double weight) {
    if (u < starting_vertex || u > graph_size || v < starting_vertex || v > graph_size || weight < 0.0) {
        std::cerr << "Wrong edge input" << std::endl;
        return;
    }

    for (uint32_t i = 0; i < edges.size(); i++) {
        Edge e = edges.at(i);
        if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
            std::cerr << "Edge containing given vertexes already exists" << std::endl;
            return;
        }
    }

    edges.push_back(Edge(u, v, weight));
}

std::vector<Edge> Prim::find_mst() {
    std::vector<Edge> path;
    PriorityQueue *pq = new PriorityQueue();

    initialize_single_source(pq);
    pq->priority(starting_vertex, 0.0);

    std::vector<std::vector<Neighbour>> adj(graph_size);
    for (uint32_t i = 0; i < edges.size(); i++) {
        Edge e = edges.at(i);
        adj.at(e.u - starting_vertex).push_back(Neighbour(pq->find(e.v), e.weight));
        adj.at(e.v - starting_vertex).push_back(Neighbour(pq->find(e.u), e.weight));
    }

    uint32_t *parent;
    uint32_t u;
    double weight;

    while (!pq->empty()) {
        weight = pq->get_queue().at(0)->dist;
        parent = pq->get_queue().at(0)->parent;
        u = pq->pop();

        if (parent != nullptr) {
            path.push_back(Edge(u, *parent, weight));
        }

        std::vector<Neighbour> *l = &adj.at(u - starting_vertex);
        for (uint32_t i = 0; i < l->size(); i++) {
            Neighbour *v = &l->at(i);
            compares++;
            if (pq->find(v->vertex->key) == v->vertex && v->weight < v->vertex->dist) {
                v->vertex->parent = new uint32_t(u);
                //v->vertex->dist = v->weight;
                pq->priority(v->vertex->key, v->weight);
            }
        }

    }
    compares = compares + pq->get_compares();
    delete pq;
    adj.clear();
    adj.shrink_to_fit();
    return path;
}


