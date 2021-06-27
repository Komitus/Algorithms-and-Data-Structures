#include <fstream>
#include <sstream>
#include <random>
#include "kruskal.hpp"
#include "prim.hpp"

void perform_test(){

    std::string dir_name = "./Test_Data/";
    std::string lenghts[4] = {"8", "250", "1000", "10000"};
    std::string filename;
    std::string out_filename = dir_name + "output.csv";
    std::ifstream in_file;
    std::ofstream out_file;

    uint32_t num_of_vertexes, num_of_edges;
    uint32_t u, v;
    double w;
    MST *mst;

    out_file.open(out_filename, std::ofstream::trunc | std::ofstream::out);
    out_file << "|V|;|E|;Prim;Kruskal" << std::endl;

    for(int i = 0; i < 4; i++){
        filename = dir_name + "g" + lenghts[i] + ".txt";
        std::cout<<filename << " ";

        for(int j = 0; j < 2; j++){
            in_file.open(filename, std::ifstream::in);
        
            if(in_file){
                in_file >> num_of_vertexes;
                in_file >> num_of_edges;
                if(j == 0){
                    std::cout << "Num of VERTEXES: " << num_of_vertexes << ", " << "EDGES: " << num_of_edges << std::endl;
                    std::cout << "Prim " + lenghts[i] << std::endl;
                    out_file << num_of_vertexes << ";" << num_of_edges << ";";
                    mst = new Prim(num_of_vertexes, 0);
                } else {
                    std::cout << "Kruskal " + lenghts[i] << std::endl;
                    mst = new Kruskal(num_of_vertexes, 0);
                } 

                for(uint32_t i = 0; i < num_of_edges ; i++){
                    in_file >> u >> v >> w;
                    mst->add_edge(u, v, w);
                }
                in_file.close();

                mst->find_mst();
                
                if(j == 0) out_file << mst->compares << ";";
                else out_file << mst->compares << std::endl;
                delete mst;  
            }     
        }   
    }
    
}