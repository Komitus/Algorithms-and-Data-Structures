#include "input_handler.hpp"
#include <algorithm>
#include <chrono>   
#include <fstream>
#include "prim.hpp"
#include "kruskal.hpp"

InputHandler::InputHandler(){}
InputHandler::~InputHandler(){}

void InputHandler::handle_input(uint32_t first_index, char algo_type){

    uint32_t num_of_vertexes;
    uint32_t num_of_edges;
    uint32_t u,v, source;
    double w;
    uint32_t compares = 0;
    std::vector<Edge> path;
    std::cout << "Enter graph definition: " << std::endl;
    std::cout << "Number of VERTEXTES: ";
    std::cin >> num_of_vertexes;
    if(algo_type == 'k') mst = new Kruskal(num_of_vertexes, first_index);
    else mst = new Prim(num_of_vertexes, first_index);
    std::cout<< "Number of EDGES: ";
    std::cin >> num_of_edges;
    std::cout << "Enter edges definition (u, v, w):" << std::endl;
    for(uint32_t i = 0; i < num_of_edges; i++){
        std::cin >> u >> v >> w;
        mst->add_edge(u, v, w);
    }

    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::high_resolution_clock::duration elapsed;

    begin = std::chrono::high_resolution_clock::now();
    path = mst->find_mst();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - begin;
    print_path(&path);
    std::cout << "Time (nanosecs): " << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << std::endl;
    std::cout << "Compares: " << mst->compares << std::endl;
    delete mst;
}


void InputHandler::do_example(){
    std::string filename = "./Test_Data/g8.txt";
    std::ifstream in_file;
    uint32_t num_of_vertexes;
    uint32_t num_of_edges;
    uint32_t source;
    uint32_t compares = 0;
    std::vector<Edge> path;
    uint32_t u, v;
    double w;

    for(uint8_t i = 0; i < 2; i++){

        std::cout << std::endl << "#########################" << std::endl;
        if(i == 0) std::cout << "####### Kruskal #########" << std::endl;
        else std::cout << "######## Prim ###########" << std::endl;
        std::cout << "#########################" << std::endl << std::endl;

        in_file.open(filename, std::ifstream::in);

        if(in_file){
            in_file >> num_of_vertexes;
            in_file >> num_of_edges;
            std::cout<<num_of_vertexes << " " << num_of_edges << std::endl;
            if(i == 0) mst = new Kruskal(num_of_vertexes, 0);
            else mst = new Prim(num_of_vertexes, 0);

            std::cout << "Edges from input (u, v, w): " << std::endl;
            for(uint32_t i = 0; i < num_of_edges ; i++){
                in_file >> u >> v >> w;
                mst->add_edge(u, v, w);
                std::cout << u << "; " << v << "; " << w << std::endl; 
            }
            std::cout << std::endl;
            in_file.close();
        }
        
        std::chrono::high_resolution_clock::time_point begin;
        std::chrono::high_resolution_clock::time_point end;
        std::chrono::high_resolution_clock::duration elapsed;

        begin = std::chrono::high_resolution_clock::now();
        path = mst->find_mst();
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - begin;
        print_path(&path);
        std::cout << "Time (nanosecs): " << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << std::endl;
        std::cout << "Compares: " << mst->compares << std::endl;
        delete mst;
    }
    in_file.close();

}

void InputHandler::print_path(std::vector<Edge> *path){
    
    std::cout << "RETURNED MST: " << std::endl;
    double sum = 0.0;
    uint32_t *u;
    uint32_t *v;
    double w;
    for (size_t i = 0; i < path->size(); i++) {
        
        u = &path->at(i).u;
        v =  &path->at(i).v;
        if(*u > *v) std::swap(u, v);
        
        w = path->at(i).weight;
        sum += w;
        std::cout << *u << " " << *v << " " << w << std::endl;
    }
    std::cout << "Weight sum: " << sum << std::endl;
}