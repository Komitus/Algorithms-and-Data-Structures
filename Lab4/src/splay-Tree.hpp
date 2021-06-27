#ifndef _Splay_Tree

#define _Splay_Tree
#include "rb-Tree.hpp"

class Splay_Tree : public RB_Tree{    

private:

    void splay(Node *node);
    Node * max_helper(Node *node);
    Node *join(Node *z, Node *t);
    void split(Node *&x, Node *&z, Node *&t);
    
public:     

    Splay_Tree();   //i want to inherit from BST
    void insert(std::string key);
    void del_node (std::string key);
    bool find(std::string key);
    void print();   //i want to inherit from BST

};

#endif