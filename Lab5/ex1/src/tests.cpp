#include "priority_queue.hpp"
#include <random>
#include <fstream>

uint32_t getRand(const uint32_t& A, const uint32_t& B) {
    static std::random_device randDev;
    static std::mt19937 twister(randDev());
    static std::uniform_int_distribution<uint32_t> dist;

    dist.param(std::uniform_int_distribution<uint32_t>::param_type(A, B));
    return dist(twister);
}

void perform_tests(){

    std::cout << "Tests started" << std::endl;

    std::string out_file_name = "./Test_Data/output.csv";
    std::ofstream output_file;
    uint32_t compares[3];
    uint16_t num_of_prior;

    output_file.open(out_file_name, std::ofstream::trunc | std::ofstream::out);
    output_file << "n;insert;priority;pop" << std::endl;
    
    priority_queue *queue;
    for(int n = 10; n <= 1000; n++){
        
        num_of_prior = n/4;
        compares[0] = 0;
        compares[1] = 0;
        compares[2] = 0;
        for(int i = 0; i < 100; i++){
            
            queue = new priority_queue;
            
            for(int i = 0; i < n-1; i++){
                queue->insert(getRand(0, 200), getRand(2, n-1));
            }
            queue->zero_compares();
            queue->insert(getRand(0, 200), 0);
            compares[0] += queue->get_compares();
            queue->zero_compares();
            
            for(int i = 0; i < num_of_prior; i++){
                element elem = queue->read_elem(getRand(n/3, n-1));
                //uint32_t priority = 0;
                //do {
                   //priority = elem.p - getRand(0, n-1);
                //} while(priority < 0);
                queue->priority(elem.key, elem.p/4);
            }
            compares[1] += (queue->get_compares()/num_of_prior);
            queue->zero_compares();
            
            for(int i = 0; i < n; i++){
                queue->pop();  
            }
            compares[2] += queue->get_compares()/n;
            queue->zero_compares();
            delete queue;
        }
        output_file << n << ";" << compares[0]/100 << ";" << compares[1]/100 << ";" << compares[2]/100 << std::endl;
        
    }
    output_file.close();
}
