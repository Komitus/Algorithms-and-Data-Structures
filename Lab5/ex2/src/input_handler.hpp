#ifndef _input_handler
#define _input_handler
#include "graph.hpp"

struct {
    bool operator() (std::shared_ptr<Element> e1, std::shared_ptr<Element> e2) {
        return e1->key < e2->key;
    }
} comp;

class InputHandler {
private:
    Graph *graph;
    void print_paths(std::vector<std::shared_ptr<Element>> *S, uint32_t source);
    uint32_t source_vertex;
public:
    InputHandler();
    ~InputHandler();
    void handle_input(uint32_t first_index);
    void do_example();
};

#endif