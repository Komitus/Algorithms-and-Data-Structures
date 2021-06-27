#include "cmd_parser.hpp"
#include <cstring>

int main(int argc, char *argv[]){

    if (strcmp(argv[1], "input") == 0){
        parser *input = new parser();
        input->handle_input();
        perform_tests();
        delete input;  
        return 0;
    }
    else if (strcmp(argv[1], "test") == 0){
        perform_tests();
        return 0;
    }
    
}