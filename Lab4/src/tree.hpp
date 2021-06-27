#ifndef _tree
#define _tree
#include <iostream>
#include <fstream>

struct stats
{
public:
    uint32_t comps;
    uint32_t inserts;
    uint32_t loads;
    uint32_t deletes;
    uint32_t finds;
    uint32_t mins;
    uint32_t maxs;
    uint32_t successors;
    uint32_t inorders;
    uint32_t max_size;
    uint32_t curr_size;
    stats()
    {
        comps = 0;
        inserts = 0;
        loads = 0;
        deletes = 0;
        finds = 0;
        mins = 0;
        maxs = 0;
        successors = 0;
        inorders = 0;
        max_size = 0;
        curr_size = 0;
    }
    stats(stats *s){
        comps = s->comps;
        inserts = s->inserts;
        loads = s->loads;
        deletes = s->deletes;
        finds = s->finds;
        mins = s->mins;
        maxs = s->maxs;
        successors = s->successors;
        inorders = s->inorders;
        max_size = s->max_size;
        curr_size = s->curr_size;
    }
};

class Node {
public :
    std::string key;
    Node *parent, *left, *right;
    Node (std::string  key, Node * null_leaf) {
        this->key = key;
        this->parent = null_leaf;
        this->left = null_leaf;
        this->right = null_leaf;
    }  
    virtual ~Node() {};
};

class Tree {

protected:
    stats *s;
    Node *root;
    Node *null_leaf;
    virtual uint32_t getHeight_helper(Node* root) = 0;
    
public:
    virtual void insert(std::string key) = 0;
    virtual void load(std::string file_name) = 0;
    virtual void del_node (std::string key) = 0;
    virtual bool find(std::string key) = 0;
    virtual std::string min() = 0;
    virtual std::string max() = 0;
    virtual std::string successor(std::string k) = 0;
    virtual void inorder() = 0;
    virtual void print() = 0;
    virtual uint32_t getHeight() = 0;
    
    virtual void resetCompares() = 0;
    virtual stats * getStats() = 0;
    virtual void check_max_size() = 0;

    virtual ~Tree() {}; 
    
};

#endif
