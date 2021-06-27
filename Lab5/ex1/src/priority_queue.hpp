#ifndef _priority_queue
#define _priority_queue
#include <iostream>
#include <vector>

struct element {
    int key;
    uint32_t p;

public:

    element(int key, uint32_t p) {
        this->key = key;
        this->p = p;
    }
};

//based on minHeap
//the highest priority is 0 and will be placed at queue.at(0)
class priority_queue {
private:
    uint32_t heap_size = 0;
    std::vector<element> queue;
    void heapify(uint32_t i);
    uint32_t parent(uint32_t i);
    uint32_t left (uint32_t i);
    uint32_t right (uint32_t i);
    uint32_t compares = 0;

public:
    priority_queue();
    ~priority_queue();
    void insert (int key, uint32_t p);
    void empty();
    void top();
    void pop();
    void priority(int key, uint32_t p);
    void print();
    element read_elem(uint32_t index);
    uint32_t get_compares();
    void zero_compares();
};

void perform_tests();
#endif