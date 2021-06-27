#include "tools.hpp"
#include "bs-Tree.hpp"
#include "rb-Tree.hpp"
#include "splay-Tree.hpp"

void read_from_file(std::string tree_type, std::string inputFile_name, std::string outputFile_name)
{   
    Tree *tree;
    if (tree_type.compare("bst") == 0){
        tree = new BS_Tree();
    }
    else if (tree_type.compare("rbt") == 0){
        tree = new RB_Tree();
    }
    else if (tree_type.compare("spl") == 0){
        tree = new Splay_Tree();
    }
    else 
    {
        std::cerr<<"Wrong tree type"<<std::endl;
        return;
    }
    handle_input(tree, inputFile_name, outputFile_name);
}

void handle_input(Tree *tree, std::string inFile_name, std::string outFile_name) 
{
    std::ifstream input_file;
    
    input_file.open(inFile_name, std::ifstream::in);
    
    if(input_file)
    {   
        int commands_number; 
        std::string returned;
        std::ofstream out_file;
        std::string line; //Line from input.
        std::istringstream iss;
        std::getline (input_file, line);
        iss.str(line);
        iss >> commands_number;
        out_file.open(outFile_name, std::ofstream::out | std::ofstream::trunc);
        
        auto begin = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < commands_number; i++) {
            std::getline(input_file, line);
            returned = do_instruction (line, tree);
            if(returned.compare("") != 0){
                out_file << returned << std::endl;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        out_file.close();
        print_stats(tree->getStats(), elapsed);
    }
    else
    {
        std::cerr<<"Wrong input filename: "<<inFile_name<<std::endl;
    }
    input_file.close();

}

std::string do_instruction(std::string line, Tree *tree)
{
    std::string to_return = "";
    std::vector<std::string> *command = split(line);
    
    if (command->at(0).compare("insert") == 0)
    {   
        tree->insert(remove_char(command->at(1)));
    }
    else if (command->at(0).compare("delete") == 0)
    {
        tree->del_node(remove_char(command->at(1)));
    }
    else if (command->at(0).compare("load") == 0)
    {
        std::string file_name = repair_file(command->at(1));
        tree->load(file_name);
    }
    else if (command->at(0).compare("find") == 0)
    {
        to_return = std::to_string(tree->find(remove_char(command->at(1))));
    }
    else if (command->at(0).compare("min") == 0)
    {
        to_return = tree->min();
    }
    else if (command->at(0).compare("max") == 0)
    {
        to_return = tree->max();
    }
    else if (command->at(0).compare("successor") == 0)
    {
        to_return = tree->successor(remove_char(command->at(1)));
    }
    else if (command->at(0).compare("inorder") == 0)
    {   
        tree->inorder();
        std::cout<<std::endl;
    }
    else if (command->at(0).compare("print") == 0)
    {
        tree->print();
        std::cout<<std::endl;
    }
    else
    {
        std::cerr << "Invalid command!" << std::endl;
        std::cerr << "\n";
    }

    delete command;
    return to_return;
}

void print_stats(stats *s, std::chrono::high_resolution_clock::duration elapsed_time)
{
    std::cerr<<"Elapsed time: " << elapsed_time.count() << " micro-secs" << std::endl;
    std::cerr<<"Inserts: " << s->inserts << std::endl;
    std::cerr<<"Loads: " << s->loads << std::endl;
    std::cerr<<"Deletes: " << s->deletes << std::endl;
    std::cerr<<"Finds: " << s->finds << std::endl;
    std::cerr<<"Mins: " << s->mins << std::endl;
    std::cerr<<"Maxs: " << s->maxs << std::endl;
    std::cerr<<"Successors: " << s->successors << std::endl;
    std::cerr<<"Inorders: " << s->inorders << std::endl;
    std::cerr<<"Max_size: " << s->max_size << std::endl;
    std::cerr<<"Final_size: " << s->curr_size << std::endl;
    std::cerr<<"Comps: " << s->comps << std::endl;
}