#include "rb-Tree.hpp"

RB_Tree::RB_Tree()
{
    null_leaf = new RB_Node("", null_leaf, BLACK);
    root = null_leaf;
    s = new stats();
    s->max_size = 0;
    s->curr_size = 0;
    //std::cout<<"RBT Constructor"<<std::endl;
}
void RB_Tree::insert(std::string key)
{
    Node *new_node = new RB_Node(key, null_leaf, RED);
    bst_insert(new_node); //Insert new node like in normal Binary Search Tree.
    insert_fixUp(new_node);
    s->inserts++;
    s->curr_size++;
    check_max_size();
}

void RB_Tree::del_node(std::string key)
{
    //this is only for this purpose that i want avoid decrementing current size
    Node *node = bst_find(key);
    if (node != null_leaf)
    {
        rbt_delete(node);
        s->deletes++;
        s->curr_size--;
    }
}

//PRIVATE FUNCTIONS
// bcs its hard to increment operations once in recursive functions

void RB_Tree::right_rotate(Node *y)
{
    Node *x = y->left;

    y->left = x->right;
    s->comps++;
    if (x->right != null_leaf)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;

    s->comps++;
    if (y->parent == null_leaf)
    {
        root = x;
    }
    else if (y == y->parent->right)
    {
        s->comps++;
        y->parent->right = x;
    }
    else
    {
        s->comps++;
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}
//mirror of right rotate
void RB_Tree::left_rotate(Node *x)
{
    Node *y = x->right;

    x->right = y->left;
    s->comps++;
    if (y->left != null_leaf)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    s->comps++;
    if (x->parent == null_leaf)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        s->comps++;
        x->parent->left = y;
    }
    else
    {
        s->comps++;
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RB_Tree::insert_fixUp(Node *node)
{

    while (dynamic_cast<RB_Node *>(node->parent)->color == RED)
    {
        //std::cout<<"In while loop"<<std::endl;
        s->comps++;
        if (node->parent == node->parent->parent->left)
        {
            //std::cout<<"Case A"<<std::endl;
            Node *y = node->parent->parent->right;
            s->comps++;
            if (dynamic_cast<RB_Node *>(y)->color == RED)
            {
                //std::cout<<"Case A1"<<std::endl;
                dynamic_cast<RB_Node *>(node->parent)->color = BLACK;
                dynamic_cast<RB_Node *>(y)->color = BLACK;
                dynamic_cast<RB_Node *>(node->parent->parent)->color = RED;
                node = node->parent->parent;
            }
            else
            {
                s->comps++;
                if (node == node->parent->right)
                {
                    //std::cout<<"Case A2"<<std::endl;
                    node = node->parent;
                    left_rotate(node);
                }
                //std::cout<<"Case A3"<<std::endl;
                dynamic_cast<RB_Node *>(node->parent)->color = BLACK;
                dynamic_cast<RB_Node *>(node->parent->parent)->color = RED;
                right_rotate(node->parent->parent);
            }
        }
        else
        {
            //std::cout<<"Case B"<<std::endl;
            Node *y = node->parent->parent->left;
            s->comps++;
            if (dynamic_cast<RB_Node *>(y)->color == RED)
            {
                //std::cout<<"Case B1"<<std::endl;
                dynamic_cast<RB_Node *>(node->parent)->color = BLACK;
                dynamic_cast<RB_Node *>(y)->color = BLACK;
                dynamic_cast<RB_Node *>(node->parent->parent)->color = RED;
                node = node->parent->parent;
            }
            else
            {
                s->comps++;
                if (node == node->parent->left)
                {
                    //std::cout<<"Case B2"<<std::endl;
                    node = node->parent;
                    right_rotate(node);
                }
                //std::cout<<"Case B3"<<std::endl;
                dynamic_cast<RB_Node *>(node->parent)->color = BLACK;
                dynamic_cast<RB_Node *>(node->parent->parent)->color = RED;
                left_rotate(node->parent->parent);
            }
        }
    }
    dynamic_cast<RB_Node *>(root)->color = BLACK;
}

void RB_Tree::delete_fixUp(Node *node)
{

    Node *m;
    s->comps++;
    while (node != root && dynamic_cast<RB_Node *>(node)->color == BLACK)
    {
        //CASE A
        //node is left child
        s->comps++;
        if (node == node->parent->left)
        {
            m = node->parent->right;

            //Case 1: node's sibling m is red.
            s->comps++;
            if (dynamic_cast<RB_Node *>(m)->color == RED)
            {
                //std::cout<<"Case A1"<<std::endl;
                dynamic_cast<RB_Node *>(m)->color = BLACK;
                dynamic_cast<RB_Node *>(node->parent)->color = RED;
                left_rotate(node->parent);
                m = node->parent->right;
            }
            //Case 2: node's sibling m is black,  and both of m's children are black
            s->comps++;
            if (dynamic_cast<RB_Node *>(m->left)->color == BLACK && dynamic_cast<RB_Node *>(m->right)->color == BLACK)
            {
                //std::cout<<"Case A2"<<std::endl;
                dynamic_cast<RB_Node *>(m)->color = RED;
                node = node->parent;
            }
            else
            { //Case 3: node's sibling m is black, m's left child is red, and m's right child is black
                s->comps++;
                if (dynamic_cast<RB_Node *>(m->right)->color == BLACK)
                {
                    //std::cout<<"Case A3"<<std::endl;
                    dynamic_cast<RB_Node *>(m->left)->color = BLACK;
                    dynamic_cast<RB_Node *>(m)->color = RED;
                    right_rotate(m);
                    m = node->parent->right;
                }

                dynamic_cast<RB_Node *>(m)->color = dynamic_cast<RB_Node *>(node->parent)->color; //node's sibling m is black, and m's right child is red
                dynamic_cast<RB_Node *>(node->parent)->color = BLACK;
                dynamic_cast<RB_Node *>(m->right)->color = BLACK;
                left_rotate(node->parent);
                node = root;
            }
        }
        else
        {
            m = node->parent->left;

            s->comps++;
            if (dynamic_cast<RB_Node *>(m)->color == RED)
            {
                //std::cout<<"Case B1"<<std::endl;
                dynamic_cast<RB_Node *>(m)->color = BLACK;
                dynamic_cast<RB_Node *>(node->parent)->color = RED;
                right_rotate(node->parent);
                m = node->parent->left;
            }

            s->comps++;
            if (dynamic_cast<RB_Node *>(m->right)->color == BLACK && dynamic_cast<RB_Node *>(m->left)->color == BLACK)
            {
                //std::cout<<"Case B2"<<std::endl;
                dynamic_cast<RB_Node *>(m)->color = RED;
                node = node->parent;
            }
            else
            {
                s->comps++;
                if (dynamic_cast<RB_Node *>(m->left)->color == BLACK)
                {
                    //std::cout<<"Case B3"<<std::endl;
                    dynamic_cast<RB_Node *>(m->right)->color = BLACK;
                    dynamic_cast<RB_Node *>(m)->color = RED;
                    left_rotate(m);
                    m = node->parent->left;
                }

                dynamic_cast<RB_Node *>(m)->color = dynamic_cast<RB_Node *>(node->parent)->color;
                dynamic_cast<RB_Node *>(node->parent)->color = BLACK;
                dynamic_cast<RB_Node *>(m->left)->color = BLACK;
                right_rotate(node->parent);
                node = root;
            }
        }
    }

    dynamic_cast<RB_Node *>(node)->color = BLACK;
}

void RB_Tree::rbt_delete(Node *node)
{
    Node *m, *n;

    //Do BST Delete.
    s->comps++;
    if (node->left == null_leaf || node->right == null_leaf)
    {
        n = node;
    }
    else
    {
        n = bst_successor(node);
    }
    s->comps++;
    if (n->left != null_leaf)
    {
        m = n->left;
    }
    else
    {
        m = n->right;
    }

    m->parent = n->parent;

    s->comps++;
    if (n->parent == null_leaf)
    {
        root = m;
    }
    else if (n == n->parent->left)
    {
        s->comps++;
        n->parent->left = m;
    }
    else
    {
        s->comps++;
        n->parent->right = m;
    }
    s->comps++;
    if (n != node)
    {
        node->key = n->key;
    }

    //Fix properties of RBT if node to delete is black.
    s->comps++;
    if (dynamic_cast<RB_Node *>(n)->color == BLACK)
    {   
        delete_fixUp(m);
    }
    delete n;
}

void RB_Tree::rb_print(const std::string &prefix, const Node *node, bool isLeft)
{
    if (node != null_leaf)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        std::string color = ((RB_Node *)node)->color == RED ? "\u2B55" : "\u26AB";
        std::cout << node->key << "(" << color << ")" << std::endl;

        // enter the next tree level - left and right branch
        rb_print(prefix + (isLeft ? "│   " : "    "), node->left, true);
        rb_print(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void RB_Tree::print()
{
    const Node *node = root;
    rb_print("", node, false);
}
