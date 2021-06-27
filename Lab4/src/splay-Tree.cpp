#include "splay-Tree.hpp"

Splay_Tree::Splay_Tree()
{   
    null_leaf = new Node("", nullptr);
    null_leaf->parent = null_leaf;
    null_leaf->right = null_leaf;
    null_leaf->left = null_leaf;
    root = null_leaf;
    s = new stats();
    s->max_size = 0;
    s->curr_size = 0;
    //std::cout<<"Splay Constructor"<<std::endl;
}

void Splay_Tree::insert(std::string key)
{
    Node *new_node = new Node(key, null_leaf);
    bst_insert(new_node);
    
    splay(new_node);
    
    s->inserts++;
    s->curr_size++;
    check_max_size();
}

bool Splay_Tree::find(std::string key)
{   
    s->finds++;
    Node *node = bst_find(key);
    s->comps++;
    if (node != null_leaf)
    {
        splay(node);
        return true;
    }
    return false;
}

void Splay_Tree::del_node(std::string key)
{   
    s->deletes++;
    Node *t, *z; //subtrees
    Node *to_remove = bst_find(key);

    s->comps++;
    if (to_remove != null_leaf)
    {
        split(to_remove, z, t); // split the tree
        s->comps++;
        if (z->left != null_leaf)
        {   // remove to_remove
            z->left->parent = null_leaf;
        }
        root = join(z->left, t);
        delete z;
        z = null_leaf;

        s->curr_size--;
    } 
}


void Splay_Tree::splay(Node *x)
{   
    s->comps++;
    while (x->parent != null_leaf)
    {   
        s->comps++;
        if (x->parent->parent == null_leaf)
        {   
            s->comps++;
            if (x == x->parent->left)
            {
                // zig rotation
                right_rotate(x->parent);
            }
            else
            {
                // zag rotation
                left_rotate(x->parent);
            }
        }
        else if (x == x->parent->left && x->parent == x->parent->parent->left)
        {
            s->comps++;
            // zig-zig rotation
            right_rotate(x->parent->parent);
            right_rotate(x->parent);
        }
        else if (x == x->parent->right && x->parent == x->parent->parent->right)
        {   
            s->comps++;
            // zag-zag rotation
            left_rotate(x->parent->parent);
            left_rotate(x->parent);
        }
        else if (x == x->parent->right && x->parent == x->parent->parent->left)
        {   
            s->comps++;
            // zig-zag rotation
            left_rotate(x->parent);
            right_rotate(x->parent);
        }
        else
        {   
            // zag-zig rotation
            right_rotate(x->parent);
            left_rotate(x->parent);
        }
    }
}

// joins two trees z and t
Node * Splay_Tree::join(Node *z, Node *t)
{   
    s->comps++;
    if (z == null_leaf)
    {
        return t;
    }
    s->comps++;
    if (t == null_leaf)
    {
        return z;
    }
    Node *x = max_helper(z);
    splay(x);
    x->right = t;
    t->parent = x;
    return x;
}

// splits the tree into s and t
// we split tree taking into account node "x"
void Splay_Tree::split(Node *&x, Node  *&z, Node *&t)
{
    splay(x);
    s->comps++;
    if (x->right != null_leaf)
    {
        t = x->right;
        t->parent = null_leaf;
    }
    else
    {
        t = null_leaf;
    }
    z = x;
    z->right = null_leaf;
    x = null_leaf;
}

Node * Splay_Tree::max_helper(Node *node)
{   
    s->comps++;
    while (node->right != null_leaf) {
        s->comps++;
		node = node->right;
	}
	return node;
}

void Splay_Tree::print()
{
    BS_Tree::print();
}
