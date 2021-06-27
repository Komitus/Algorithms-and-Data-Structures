#include "graph.hpp"
#include <fstream>
#include <sstream>
#include <random>

uint32_t getRand(const uint32_t& A, const uint32_t& B) {
    static std::random_device randDev;
    static std::mt19937 twister(randDev());
    static std::uniform_int_distribution<uint32_t> dist;

    dist.param(std::uniform_int_distribution<uint32_t>::param_type(A, B));
    return dist(twister);
}

void perform_test(){

    std::string dir_name = "./Test_Data/";
    std::string lenghts[4] = {"8", "250", "1000", "10000"};
    std::string filename;
    std::string out_filename = dir_name + "output.csv";
    std::ifstream in_file;
    std::ofstream out_file;
    uint32_t compares = 0;
    uint32_t num_of_attempts = 50;

    uint32_t num_of_vertexes, num_of_edges;
    uint32_t u, v;
    double w;
    Graph *graph;

    out_file.open(out_filename, std::ofstream::trunc | std::ofstream::out);
    out_file << "|V|;|E|;compares" << std::endl;

    for(int i = 0; i < 4; i++){
        filename = dir_name + "g" + lenghts[i] + ".txt";

        std::cout<<filename<<std::endl;
        in_file.open(filename, std::ifstream::in);
        compares = 0;

        if(in_file){
            in_file >> num_of_vertexes;
            in_file >> num_of_edges;
            std::cout << "Num of VERTEXES: " << num_of_vertexes << ", " << "EDGES: " << num_of_edges << std::endl;
            graph = new Graph(num_of_vertexes, 0);

            for(uint32_t i = 0; i < num_of_edges ; i++){
                in_file >> u >> v >> w;
                graph->add_edge(u, v, w);
            }
            in_file.close();

            for(uint32_t i = 0; i < num_of_attempts; i++){
                graph->dijkstra_shortest_path(getRand(0, num_of_vertexes-2), &compares);
            }
            out_file << num_of_vertexes << ";" << num_of_edges << ";" << compares/num_of_attempts << std::endl;
        }     
    }
}