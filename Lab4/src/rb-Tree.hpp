#ifndef _RB_Tree

#define _RB_Tree

#include "bs-Tree.hpp"
enum Colors{BLACK, RED};

class RB_Node : public Node {

public:
    Colors color;
    RB_Node (std::string  key, Node * null_leaf, Colors color) : Node(key, null_leaf){
        this->color = color;
    }
};

class RB_Tree : public BS_Tree {    
private:
    void insert_fixUp(Node *node);
    void delete_fixUp(Node *node);
    void rbt_delete(Node *node);
    void rb_print(const std::string& prefix, const Node* node, bool isLeft);
protected:
    void left_rotate(Node *x);
    void right_rotate(Node *y);
public:     
    RB_Tree();
    void insert(std::string key);
    void del_node (std::string key);
    void print();
};



#endif