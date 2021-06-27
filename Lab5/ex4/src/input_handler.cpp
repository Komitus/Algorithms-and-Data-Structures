#include "input_handler.hpp"
#include <algorithm>
#include <chrono>   
#include <fstream>
#include "prim.hpp"
#include "kruskal.hpp"
#include "random_walk.hpp"
#include "weight_walk.hpp"
#include "cycle_walk.hpp"

InputHandler::InputHandler(){}
InputHandler::~InputHandler(){}

void InputHandler::handle_input(uint32_t first_index, char algo_type){

    uint32_t num_of_vertexes;
    uint32_t num_of_edges;
    uint32_t u,v, source;
    double w;
    uint32_t compares = 0;
    Walker *walker;
    MST *mst;

    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::high_resolution_clock::duration elapsed;

    std::cout << "Enter graph definition: " << std::endl;
    std::cout << "Number of VERTEXTES: ";
    std::cin >> num_of_vertexes;

    if(algo_type == 'r'){
        walker = new RandomWalk(num_of_vertexes, first_index);
    } else if (algo_type == 'w'){
        walker = new WeightWalk(num_of_vertexes, first_index);
    } else if (algo_type == 'k') {
        mst = new Kruskal(num_of_vertexes, first_index);
    } else if (algo_type == 'p') {
        mst = new Prim(num_of_vertexes, first_index);
    }

    std::cout<< "Number of EDGES: ";
    std::cin >> num_of_edges;
    std::cout << "Enter edges definition (u, v, w):" << std::endl;
    if(algo_type == 'w' || algo_type == 'r'){
        for(uint32_t i = 0; i < num_of_edges; i++){
            std::cin >> u >> v >> w;
            walker->add_edge(u, v, w);
        }
        begin = std::chrono::high_resolution_clock::now();
    } else {
        for(uint32_t i = 0; i < num_of_edges; i++){
            std::cin >> u >> v >> w;
            mst->add_edge(u, v, w);
        }
        begin = std::chrono::high_resolution_clock::now();
        dynamic_cast<CycleWalk *>(walker)->add_edges(mst->find_mst());
        delete mst;
    }
    walker->walk(true);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - begin; 
    std::cout << "Time (nanosecs): " << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << std::endl;
}

void InputHandler::do_example(){
    std::string dir_name = "./Test_Data/";
    std::string filename;
    std::ifstream in_file;
    uint32_t start_index = 0;
    uint32_t num_of_vertexes, num_of_edges;
    uint32_t u, v;
    double w;
    Walker *walker;
    MST *mst;

    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::high_resolution_clock::duration elapsed;

    filename = dir_name + "g" + std::to_string(8) + ".txt";
    std::cout << filename << " " << std::endl;

    for (uint16_t j = 0; j < 4; j++)
    {
        in_file.open(filename, std::ifstream::in);

        if (in_file)
        {
            in_file >> num_of_vertexes;
            in_file >> num_of_edges;
            if (j == 0)
            {
                std::cout << "Num of VERTEXES: " << num_of_vertexes << ", "
                          << "EDGES: " << num_of_edges << std::endl;
                std::cout << "Random Walk" << std::endl;
                begin = std::chrono::high_resolution_clock::now();
                walker = new RandomWalk(num_of_vertexes, start_index);
            }
            else if (j == 1)
            {   
                std::cout << "Weight Walk" << std::endl;
                begin = std::chrono::high_resolution_clock::now();
                walker = new WeightWalk(num_of_vertexes, start_index);
            }
            else if (j > 1)
            {
                if (j == 2)
                {
                    std::cout << "Cycle Walk - Kruskal" << std::endl;
                    begin = std::chrono::high_resolution_clock::now();
                    mst = new Kruskal(num_of_vertexes, start_index);
                }
                else
                {   
                    std::cout << "Cycle Walk - Prim" << std::endl;
                    begin = std::chrono::high_resolution_clock::now();
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

            walker->walk(true);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - begin;
            delete walker;
            std::cout << "Time (nanosecs): " << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << std::endl;
            in_file.close();
        }
    }
}
