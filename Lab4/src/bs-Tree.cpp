#include "bs-Tree.hpp"
#include <iostream>
//!!!!!
// I count compares to null_leaf

void BS_Tree::resetCompares(){
    s->comps = 0;
}
stats * BS_Tree::getStats(){
    return s;
}
void BS_Tree::check_max_size(){
    if(s->curr_size > s->max_size)
        s->max_size = s->curr_size;
}

BS_Tree::BS_Tree()
{
    null_leaf = new Node("", nullptr);
    null_leaf->parent = null_leaf;
    null_leaf->right = null_leaf;
    null_leaf->left = null_leaf;
    root = null_leaf;
    s = new stats();
    s->max_size = 0;
    s->curr_size = 0;
    //std::cout<<"BST Constructor"<<std::endl;
}
BS_Tree::~BS_Tree()
{
    bst_destroy(root);
    root = nullptr;
    delete null_leaf;
    null_leaf = nullptr;
    delete s;
    s = nullptr;
}

void BS_Tree::inorder()
{
    bst_inorder(root);
    s->inorders++;
}
void BS_Tree::insert(std::string key)
{
    Node *new_node = new Node(key, null_leaf);
    bst_insert(new_node);

    s->inserts++;
    s->curr_size++;
    check_max_size();
}

std::string BS_Tree::successor(std::string k)
{   
    s->successors++;
    Node *successor = bst_successor(bst_find(k));
    return successor == null_leaf ? "\n" : successor->key;
}
void BS_Tree::del_node(std::string key)
{
    //this is only for this purpose that i want avoid decrementing current size
    Node *node = bst_find(key);
    if (node != null_leaf)
    {
        bst_delete(node);
        s->deletes++;
        s->curr_size--;
    }
}

bool BS_Tree::find(std::string key)
{
    s->finds++;
    //i dont count this compare, its implementation calse
    //while in bst find handle null but i want node not value from bst find
    return bst_find(key) == null_leaf ? false : true;   
}

std::string BS_Tree::min()
{
    Node *min_node = bst_min(root);
    s->mins++;
    return (min_node != null_leaf) ? min_node->key : "\n";
}

std::string BS_Tree::max()
{
    s->maxs++;
    Node *node = root;
    s->comps++;
    if (node == null_leaf)
    {
        return "\n";
    }
    s->comps++;
    //Search right element in right subtree of node.
    while (node->right != null_leaf)
    {
        node = node->right;
        s->comps++;
    }
    return node->key;
}

void BS_Tree::load(std::string file_name)
{
    s->loads++;
    std::ifstream in_file;
    in_file.open(file_name, std::ifstream::in);
    std::string word;
    if (in_file)
    {
        while (in_file >> word)
            insert(word);     
    }
    else
    {
        std::cout << "File doesn't exist";
    }
}

//PRIVATE FUNCTIONS
// bcs its hard to increment operations once in recursive functions

void BS_Tree::bst_inorder(Node *node)
{   
    s->comps++;
    if (node == null_leaf)
        return;
    bst_inorder(node->left);
    //std::cout << node->key << " ";   //disable for test
    bst_inorder(node->right);
}

//First greater value than node.
Node *BS_Tree::bst_successor(Node *node)
{
    //If node has right subtree, search succesor in right subtree.
    s->comps++;
    if (node->right != null_leaf)   //problem with nullleaf null_leaf->right isn null_leaf
    {   
        return bst_min(node->right);
    }
    
    //Otherwise successor is lowest ancestor of node, which have left son that is parent node for our input node.
    Node *tmp = node->parent;
    s->comps++;
    while (tmp != null_leaf && node == tmp->right)
    {   
        
        node = tmp;
        tmp = tmp->parent;
        s->comps++;
    }
    s->successors++;
    
    return tmp;
}

void BS_Tree::bst_insert(Node *node)
{
    Node *x = null_leaf; //save ptr
    Node *y = root;

    //cant use bst_find bcs I wouldn't be able to get parent
    s->comps++;
    while (y != null_leaf)
    {
        x = y;
        s->comps++;
        if (node->key < y->key)
        {
            y = y->left;
        }
        else
        {
            y = y->right;
        }
    }

    node->parent = x;

    s->comps++;
    if (x == null_leaf)
    {
        root = node;
    }
    else if (node->key < x->key)
    {
        x->left = node;
        s->comps++;
    }
    else
    {
        x->right = node;
        s->comps++;
    }
}

void BS_Tree::bst_delete(Node *node)
{
    Node *x, *y;
    s->comps++;
    if (node->left == null_leaf || node->right == null_leaf)
        y = node;
    else
        y = bst_successor(node);

    s->comps++;
    if (y->left != null_leaf)
        x = y->left;
    else
        x = y->right;

    s->comps++;
    if (x != null_leaf)
        x->parent = y->parent;

    s->comps++;
    if (y->parent == null_leaf)
        root = x;
    else
    {   
        s->comps++;
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    s->comps++;
    if (y != node)
        node->key = y->key;

    delete y;
}
Node *BS_Tree::bst_find(std::string key)
{   
    Node *node = root;
    s->comps++;
    while (node != null_leaf)
    {
        s->comps++;
        if (key > node->key )
            node = node->right;  
        else if (key < node->key)
        {
            node = node->left;
            s->comps++;
        } 
        else
        {   
            s->comps++;
            return node;
        }
             
    }
    return null_leaf;
}

Node *BS_Tree::bst_min(Node *node)
{
    s->comps++;
    if (node == null_leaf)
    {
        return node;
    }
    //Search last element in left subtree of node.
    s->comps++;
    while (node->left != null_leaf)
    {
        node = node->left;
        s->comps++;
    }
    return node;
}

void BS_Tree::bst_destroy(Node *node)
{
    Node *save;

    for (Node *it = root; it != null_leaf; it = save) {
        if (it->left == null_leaf) {
            save = it->right;
            delete it;
        }
        else {
            // Rotate the left link into a right link
            save = it->left;
            it->left = save->right;
            save->right = it;
        }
    }
}

void BS_Tree::bst_print(const std::string &prefix, const Node *node, bool isLeft)
{
    if (node != null_leaf)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        std::cout << node->key << std::endl;

        // enter the next tree level - left and right branch
        bst_print(prefix + (isLeft ? "│   " : "    "), node->left, true);
        bst_print(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void BS_Tree::print()
{
    const Node *node = root;
    bst_print("", node, false);
}

uint32_t BS_Tree::getHeight()
{
    return getHeight_helper(root);
}

uint32_t BS_Tree::getHeight_helper(Node* root){
  // Base case:
    if(root == null_leaf)
        return 0;
    uint32_t leftTHeight = getHeight_helper(root->left);
    uint32_t rightTHeight = getHeight_helper(root->right);

    return std::max(leftTHeight, rightTHeight)+1;
}
