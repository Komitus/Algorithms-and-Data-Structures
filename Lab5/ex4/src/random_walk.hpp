#include "structure_classes.hpp"
#include "walker.hpp"

class RandomWalk : public Walker{
private:
    std::vector<std::shared_ptr<VisitVertex>> vertices;
public:
    RandomWalk(uint32_t graph_size, uint32_t start_index);
    ~RandomWalk();
    void add_edge (uint32_t u, uint32_t v, double weight);
    void walk(bool print);
};