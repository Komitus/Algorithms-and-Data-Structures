#ifndef _cmd_parser
#define _cmd_parser

#include "priority_queue.hpp"

class parser {
private:
    priority_queue *pq;
    void parse_cmd(std::string cmd);

public:
    parser();
    ~parser();

    void handle_input();
};

#endif