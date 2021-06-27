#include "input_handler.hpp"
#include <cstring>

int main(int argc, char *argv[]){

    if (strcmp(argv[1], "input") == 0){
        uint32_t first_index;
        InputHandler *input = new InputHandler();
        std::cout << "Type first index: 0 or 1 : ";
        std::cin >> first_index;
        input->handle_input(first_index);  
        delete input;
        return 0;
    }
    else if (strcmp(argv[1], "test") == 0){
        perform_test();
        return 0;
    } 
    else if (strcmp(argv[1], "example") == 0){
        InputHandler *input = new InputHandler();
        input->do_example(); 
        delete input;
        return 0;
    }
    

}