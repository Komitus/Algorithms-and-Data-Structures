#ifndef _priority_queue
#define _priority_queue
#include <iostream>
#include <vector>
#include <limits>
#include <memory>

struct Element {
    double key;
    uint32_t *parent = nullptr; 
    double dist;

public:

    Element() {
        key = 0;
        parent = 0;
        dist = std::numeric_limits<double>::max();
    }

    Element(uint32_t key, uint32_t *parent, double dist) {
        this->key = key;
        this->parent = parent;
        this->dist = dist;
    }
};

//based on minHeap
//the highest priority is 0 and will be placed at queue.at(0)
class PriorityQueue {
private:
    uint32_t heap_size = 0;
    std::vector<std::shared_ptr<Element>> queue;
    void heapify(uint32_t i);
    uint32_t heap_parent(uint32_t i);
    uint32_t left (uint32_t i);
    uint32_t right (uint32_t i);
    uint32_t compares = 0;

public:
    PriorityQueue();
    ~PriorityQueue();
    std::vector<std::shared_ptr<Element>> get_queue();
    std::shared_ptr<Element> insert(uint32_t key, uint32_t *parent, double dist);
    void priority (uint32_t key, double dist);
    bool empty();
    void top();
    uint32_t pop();
    std::shared_ptr<Element> find(uint32_t key);
    void print();
    Element read_elem(uint32_t index);
    uint32_t get_compares();
    void zero_compares();
};

#endif