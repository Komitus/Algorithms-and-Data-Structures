#include "structure_classes.hpp"
#include "walker.hpp"

struct NextVertex {
    std::shared_ptr<VisitVertex> next;
    double weight;

    NextVertex (std::shared_ptr<VisitVertex> next, double weight)  {
        this->next = next;
        this->weight = weight;
    }
};

class WeightWalk : public Walker{
private:
    std::vector<std::shared_ptr<VisitVertex>> vertices;
public:
    WeightWalk(uint32_t graph_size, uint32_t start_index);
    ~WeightWalk();

    void add_edge (uint32_t u, uint32_t v, double weight);
    void walk(bool print);
};