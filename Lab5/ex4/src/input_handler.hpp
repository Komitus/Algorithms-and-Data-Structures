#ifndef _input_handler
#define _input_handler
#include "structure_classes.hpp"

class InputHandler {
private:
    MST *mst;
    void print_path(std::vector<Edge> *path);
    uint32_t source_vertex;
public:
    InputHandler();
    ~InputHandler();
    void handle_input(uint32_t first_index, char algo_type);
    void do_example();
};

#endif