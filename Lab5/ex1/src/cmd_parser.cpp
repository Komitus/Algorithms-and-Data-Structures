#include "cmd_parser.hpp"

#include <sstream>
#include <cstring>

parser::parser() {
    pq = new priority_queue();
}

parser::~parser() {
    delete pq;
}

void parser::parse_cmd(std::string cmd) {

    std::istringstream iss;
    std::string str;
    std::vector<std::string> subs_cmd;

    int key;
    uint32_t p;

    iss.str(cmd);
    while(iss) {
        iss >> str;
        subs_cmd.push_back(str);
    }
    iss.clear();
    
    std::string sub_str = subs_cmd.at(0);

    if (sub_str == "insert") {

        if(subs_cmd.size() >= 3){
            pq->zero_compares();
            iss.str(subs_cmd.at(1));
            iss >> key;
            iss.clear();

            iss.str(subs_cmd.at(2));
            iss >> p;
    
            pq->insert(key, p);
            std::cout<<"Compares: "<<pq->get_compares()<<std::endl;
        } else {
            std::cerr<<"Please, type arguments"<<std::endl;
        }
        
    } else if (sub_str == "empty") {
        pq->empty();
    } else if (sub_str == "top") {
        pq->top();
    } else if (sub_str == "pop") {
        pq->pop();
    } else if (sub_str == "priority") {

        if(subs_cmd.size() >= 3){
            iss.str(subs_cmd.at(1));
            iss >> key;
            iss.clear();

            iss.str(subs_cmd.at(2));
            iss >> p;

            pq->priority(key, p);
        } else {
            std::cerr<<"Please, type arguments"<<std::endl;
        }
        
    } else if (sub_str == "print") {
        pq->print();
    } else {
        std::cerr << "***Error: Invalid command: " << sub_str << std::endl;
    }
    subs_cmd.clear();
    subs_cmd.shrink_to_fit();
}

void parser::handle_input() {
    uint32_t m = 0;
    std::string cmd;
    std::istringstream iss;
    while(m == 0){
        std::cout<<"Type number of operations"<<std::endl;
        std::getline (std::cin, cmd);
        iss.str(cmd);
        iss >> m;
        std::cout<<"Typed M: "<<m<<std::endl;
        iss.clear();
    }
    
    for(uint32_t i = 0; i < m; i++) {
        std::getline(std::cin, cmd);
        parse_cmd(cmd);
    }
}

