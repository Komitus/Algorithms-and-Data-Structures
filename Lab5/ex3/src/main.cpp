#include "input_handler.hpp"
#include <cstring>

int main(int argc, char *argv[]){

    //!!! inorder printing disabled for tests
    if (strcmp(argv[1], "-p") == 0) {   
        InputHandler inputHandler;
        inputHandler.handle_input(1, 'p');
    }
    else if(strcmp(argv[1], "-k") == 0){
        InputHandler inputHandler;
        inputHandler.handle_input(1, 'k');
    }
    else if(strcmp(argv[1], "example") == 0){
        InputHandler inputHandler;
        inputHandler.do_example();
    }
    else if(strcmp(argv[1], "test") == 0){
        perform_test();

    }
   
}