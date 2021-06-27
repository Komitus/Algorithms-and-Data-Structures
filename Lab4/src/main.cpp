#include <iostream>
#include "tools.hpp"


int main(int argc, char *argv[])
{
    std::string *params;
    params = cmdParser(argc, argv);
    //!!! inorder printing disabled for tests
    if (params[0].compare("test_ex1") == 0) 
    {   
        test_ex1();
    }
    else if(params[0].compare("test_ex2") == 0)
    {
        test_ex2();
    }
    else if(params[0].compare("tests") == 0)
    {
        test_ex1();
        test_ex2();
    }
    else
    {   // ./bin/main --type rbt '<' ./bin/input.txt '>' ./bin/output.txt
        read_from_file(params[0], params[1], params[2]);
    }
}