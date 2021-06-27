#include "input_handler.hpp"
#include <algorithm>
#include <chrono>   
#include <fstream>

InputHandler::InputHandler(){}
InputHandler::~InputHandler(){}

void InputHandler::handle_input(uint32_t first_index){

    uint32_t num_of_vertexes;
    uint32_t num_of_edges;
    uint32_t u,v, source;
    double w;
    uint32_t compares = 0;
    std::vector<std::shared_ptr<Element>> S;
    std::cout << "Enter graph definition: " << std::endl;
    std::cout << "Number of VERTEXTES: ";
    std::cin >> num_of_vertexes;
    graph = new Graph(num_of_vertexes, first_index);
    std::cout<< "Number of EDGES: ";
    std::cin >> num_of_edges;
    std::cout << "Enter edges definition (u, v, w):" << std::endl;
    for(uint32_t i = 0; i < num_of_edges; i++){
        std::cin >> u >> v >> w;
        graph->add_edge(u, v, w);
    }
    std::cout << "Enter source: ";
    std::cin >> source;
    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::high_resolution_clock::duration elapsed;

    begin = std::chrono::high_resolution_clock::now();
    S = graph->dijkstra_shortest_path(source, &compares);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - begin;
    print_paths(&S, source);
    std::cout << "Time (nanosecs): " << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << std::endl;
    std::cout << "Compares: " << compares << std::endl;
    delete graph;
}


void InputHandler::do_example(){
    std::string filename = "./Test_Data/g8.txt";
    std::ifstream in_file;
    uint32_t num_of_vertexes;
    uint32_t num_of_edges;
    uint32_t source;
    uint32_t compares = 0;
    uint32_t u, v;
    double w;

    in_file.open(filename, std::ifstream::in);

    if(in_file){
        in_file >> num_of_vertexes;
        in_file >> num_of_edges;
        std::cout<<num_of_vertexes << " " << num_of_edges << std::endl;
        graph = new Graph(num_of_vertexes, 0);

        for(uint32_t i = 0; i < num_of_edges ; i++){
            in_file >> u >> v >> w;
            graph->add_edge(u, v, w);
            std::cout << u << "; " << v << "; " << w << std::endl; 
        }
        in_file.close();
    }
    
    std::cout << "Enter source: ";
    std::cin >> source;

    std::vector<std::shared_ptr<Element>> S;
    
    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::high_resolution_clock::duration elapsed;

    begin = std::chrono::high_resolution_clock::now();
    S = graph->dijkstra_shortest_path(source, &compares);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - begin;

    print_paths(&S, source);
    std::cout << "Time (nanosecs): " << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count() << std::endl;
    std::cout << "Compares: " << compares << std::endl;
    delete graph;

}
void InputHandler::print_paths(std::vector<std::shared_ptr<Element>> *S, uint32_t source){
    
    std::sort(S->begin(), S->end(), comp);
    uint8_t ic = graph->index_correction;
    std::cout<< "Paths From " << source << std::endl;

    for (uint32_t i = 0; i < S->size(); i++) {

        if(S->at(i)->dist != std::numeric_limits<double>::max()){
            std::cout << "To: " << S->at(i)->key << "; all dist: " << S->at(i)->dist << ":" << std::endl;
        } else {
            continue;
        }
        
        double prev = 0.0;
        std::vector<std::shared_ptr<Element>> path;
        std::shared_ptr<Element> next = S->at(i);

        //we go from end throught parents to achieve source
        while (next->key != source) {
            path.push_back(next);
            //if(S->at(next->key - ic)->parent != nullptr)
                next = S->at(*(S->at(next->key - ic)->parent) - ic);
            //else 
                //break;     
        }
        path.push_back(next);
        
        for (uint32_t j = path.size(); j > 0; j--) {
            if(path.at(j-1)->key == source ) std::cerr << "  " << source;
            else std::cerr << " -- " << path.at(j-1)->dist - prev << " -->  " << path.at(j-1)->key << " " ;
            prev = path.at(j-1)->dist;
        }
        std::cerr << "\n";
    }
}