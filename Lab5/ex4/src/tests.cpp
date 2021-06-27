#include <fstream>
#include <sstream>
#include <random>
#include "kruskal.hpp"
#include "prim.hpp"
#include "random_walk.hpp"
#include "weight_walk.hpp"
#include "cycle_walk.hpp"

void perform_test()
{

    std::string dir_name = "./Test_Data/";
    std::string lenghts[4] = {"8", "250", "1000", "10000"};
    std::string filename;
    std::string stat_type[3] = {"steps", "weight", "memory"};
    std::ifstream in_file;
    std::ofstream out_file[3];
    uint32_t start_index = 0;
    uint32_t num_of_vertexes, num_of_edges;
    uint32_t u, v;
    double w;
    Walker *walker;
    MST *mst;
    uint16_t attempts = 50;
    uint32_t avg_steps;
    uint32_t avg_mem;
    double avg_weight;

    for (uint8_t i = 0; i < 3; i++)
    {
        out_file[i].open(dir_name + stat_type[i] + ".csv", std::ofstream::trunc | std::ofstream::out);
        out_file[i] << "|V|;|E|;Rand;Weight;Prim;Kruskal" << std::endl;
    }

    for (uint16_t i = 0; i < 4; i++)
    {
        filename = dir_name + "g" + lenghts[i] + ".txt";
        std::cout << filename << std::endl;
        avg_steps = 0;
        avg_weight = 0.0;
        avg_mem = 0;

        for (uint16_t j = 0; j < 4; j++)
        {
            in_file.open(filename, std::ifstream::in);

            if (j == 0)
                attempts = 50;
            else
                attempts = 1;

            if (in_file)
            {
                in_file >> num_of_vertexes;
                in_file >> num_of_edges;

                if (j == 0)
                {
                    std::cout << "Num of VERTEXES: " << num_of_vertexes << ", "
                              << "EDGES: " << num_of_edges << std::endl;
                    for (uint8_t i = 0; i < 3; i++)
                    {
                        out_file[i] << num_of_vertexes << ";" << num_of_edges << ";";
                    }

                    std::cout << "Random Walk" << std::endl;
                    walker = new RandomWalk(num_of_vertexes, start_index);
                }
                else if (j == 1)
                {
                    std::cout << "Weight Walk" << std::endl;
                    walker = new WeightWalk(num_of_vertexes, start_index);
                }
                else if (j > 1)
                {
                    if (j == 2)
                    {
                        std::cout << "Cycle Walk - Kruskal" << std::endl;
                        mst = new Kruskal(num_of_vertexes, start_index);
                    }
                    else
                    {
                        std::cout << "Cycle Walk - Prim" << std::endl;
                        mst = new Prim(num_of_vertexes, start_index);
                    }
                    for (uint32_t i = 0; i < num_of_edges; i++)
                    {
                        in_file >> u >> v >> w;
                        mst->add_edge(u, v, w);
                    }
                    std::vector<Edge> edges = mst->find_mst();
                    delete mst;
                    walker = new CycleWalk(num_of_vertexes, 0);
                    dynamic_cast<CycleWalk *>(walker)->add_edges(edges);
                    edges.clear();
                    edges.shrink_to_fit();
                }

                if (j < 2)
                {
                    for (uint32_t i = 0; i < num_of_edges; i++)
                    {
                        in_file >> u >> v >> w;
                        walker->add_edge(u, v, w);
                    }
                }

                for (uint16_t k = 0; k < attempts; k++)
                {
                    walker->walk(false); 
                }

                out_file[0] << walker->stats.steps / attempts << ";";
                out_file[1] << walker->stats.weight / (double)attempts << ";";
                out_file[2] << walker->stats.mem / attempts << ";";
                if (j == 3)
                {
                    out_file[0] << walker->stats.steps << std::endl;
                    out_file[1] << walker->stats.weight << std::endl;
                    out_file[2] << walker->stats.mem << std::endl;
                }

                in_file.close();
                delete walker;
            }
        }
    }
}
