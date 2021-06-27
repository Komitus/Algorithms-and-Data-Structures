#ifndef _cycle_walk
#define _cycle_Walk
#include "structure_classes.hpp"
#include "walker.hpp"

enum state {
    NOT_VISITED = 0,
    VISITED_ONCE = 1,
    VISITED_TWICE = 2
};

struct EulerVertex {
    uint32_t key;
    enum state visit;

    EulerVertex (uint32_t key, enum state visit) {
        this->key = key;
        this->visit = visit;
    }
};
class CycleWalk : public Walker{
private:
    std::vector<std::shared_ptr<EulerVertex>> vertices;
public:
    CycleWalk(uint32_t graph_size, uint32_t start_index);
    ~CycleWalk();
    void add_edges(std::vector<Edge>edges);
    void walk(bool print);
};
#endif