#ifndef _BS_Tree

#define _BS_Tree
#include "tree.hpp"

class BS_Tree : public Tree{    
    
private:
    uint32_t getHeight_helper(Node* root);
protected: 
    
    Node * bst_successor(Node *node);
    Node * bst_find(std::string key);
    Node * bst_min(Node *node);
    void bst_insert(Node *node);
    void bst_delete (Node *node);
    void bst_inorder(Node *node);
    void bst_destroy(Node *node);
    void bst_print(const std::string& prefix, const Node* node, bool isLeft);
    

public:     
    BS_Tree();
    ~BS_Tree();
    void inorder(); 
    void insert(std::string key);
    void del_node (std::string key);
    void load(std::string file_name);
    bool find(std::string key);
    std::string min();
    std::string max();
    std::string successor(std::string k);
    void print();
    uint32_t getHeight();

    void resetCompares();
    stats * getStats();
    void check_max_size();
};

#endif