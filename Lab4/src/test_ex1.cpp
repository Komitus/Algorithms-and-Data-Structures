#include "tools.hpp"
#include "splay-Tree.hpp"
#include "rb-Tree.hpp"
#include <memory>

void test_ex1()
{
    std::cout << "Test EX1 started" << std::endl;
    
    const int nJumpSize = 1000;
    const int attempts = 40;
    int n;
    std::unique_ptr<Tree> tree;

    std::string file_name[2] = {"./Test_Data/in_files/lotr", "./Test_Data/in_files/aspell"};
    std::string statNames[2] = {"_comps", "_time(ns)"};
    std::string operationsNames[7] = {"insert", "max", "min", "succesor", "find", "delete", "inorder"};

    std::string statsTypes;
    std::string treeName;
    std::string outputDir;
    std::ofstream outputFiles[7][2];

    uint32_t statsArray[7][3];
    std::chrono::high_resolution_clock::duration elapsedArray[7][3];

    //std::vector<std::string> loaded_file;
    //std::vector<uint32_t> lastIndexOfFile;
    std::string *loaded_file;
    uint32_t indexesOfFile[attempts];
    std::string tmpString;

    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::high_resolution_clock::duration elapsed;

    for (int testFile = 0; testFile < 2; testFile++)
    {
        switch (testFile)
        {
        case 0:
            outputDir = "./Test_Data/out_files/ex1/csv/lotr/";
            break;
        case 1:
            outputDir = "./Test_Data/out_files/ex1/csv/aspell/";
            break;
        }

        int lastIndexOfFile = countLinesInFile(file_name[testFile]+".txt") - 1;
        load_into_array(loaded_file, file_name[testFile]+"FIXED.txt", lastIndexOfFile + 1);

        n = 1000;
        
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 2; j++)
            {
                outputFiles[i][j].open(outputDir + operationsNames[i] + statNames[j] + ".csv", std::ofstream::trunc | std::ofstream::out);
                outputFiles[i][j] << "n;BST;RBT;SPL" << std::endl;
            }

        while (n < lastIndexOfFile)
        {
            for (int i = 0; i < attempts; i++)
                indexesOfFile[i] = getRand(0, n - 1);

            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 2; j++)
                    outputFiles[i][j] << n << ";";

            for (int treeType = 0; treeType < 3; treeType++)
            {
                switch (treeType)
                {
                case 0:
                    tree.reset(new BS_Tree());
                    break;
                case 1:
                    tree.reset(new RB_Tree());
                    break;
                case 2:
                    tree.reset(new Splay_Tree());
                    break;
                }

                for (int statType = 0; statType < 7; statType++)
                {

                    elapsed.zero();
                    tree->resetCompares();

                    switch (statType)
                    {
                    case 0:
                        statsTypes = "insert";
                        //I earlier loaded file into memory
                        for (int i = 0; i < n; i++)
                        {
                            //here calls to array/vector index causes enormous ram consumption idk why
                            //stops at 4GB
                            tmpString = loaded_file[i];
                            begin = std::chrono::high_resolution_clock::now();
                            tree->insert(tmpString);
                            end = std::chrono::high_resolution_clock::now();
                            elapsed = elapsed + (end - begin);
                        }
                        elapsed /= n;
                        tree->getStats()->comps = (uint32_t)std::round((double)tree->getStats()->comps / (double)n);
                        break;
                    case 1:
                        statsTypes = "max";
                        begin = std::chrono::high_resolution_clock::now();
                        tree->max();
                        end = std::chrono::high_resolution_clock::now();
                        elapsed = elapsed + (end - begin);
                        break;
                    case 2:
                        statsTypes = "min";
                        begin = std::chrono::high_resolution_clock::now();
                        tree->min();
                        end = std::chrono::high_resolution_clock::now();
                        elapsed = elapsed + (end - begin);
                        break;
                    case 3:
                        statsTypes = "successor";
                        for (int i = 0; i < attempts; i++)
                        {
                            begin = std::chrono::high_resolution_clock::now();
                            tree->successor(loaded_file[indexesOfFile[i]]);
                            end = std::chrono::high_resolution_clock::now();
                            elapsed = elapsed + (end - begin);
                        }
                        elapsed /= attempts;
                        tree->getStats()->comps = (uint32_t)std::round((double)tree->getStats()->comps / (double)attempts);
                        break;
                    case 4:
                        statsTypes = "find";
                        for (int i = 0; i < attempts; i++)
                        {
                            begin = std::chrono::high_resolution_clock::now();
                            tree->find(loaded_file[indexesOfFile[i]]);
                            end = std::chrono::high_resolution_clock::now();
                            elapsed = elapsed + (end - begin);
                        }
                        elapsed /= attempts;
                        tree->getStats()->comps = (uint32_t)std::round((double)tree->getStats()->comps / (double)attempts);
                        break;
                    case 5:
                        statsTypes = "delete";
                        for (int i = 0; i < attempts; i++)
                        {
                            begin = std::chrono::high_resolution_clock::now();
                            tree->del_node(loaded_file[indexesOfFile[i]]);
                            end = std::chrono::high_resolution_clock::now();
                            elapsed = elapsed + (end - begin);
                        }
                        elapsed /= attempts;
                        tree->getStats()->comps = (uint32_t)std::round((double)tree->getStats()->comps / (double)attempts);
                        break;
                    case 6:
                        statsTypes = "inorder";
                        begin = std::chrono::high_resolution_clock::now();
                        tree->inorder();
                        end = std::chrono::high_resolution_clock::now();
                        elapsed = elapsed + (end - begin);
                        break;
                    }
                    statsArray[statType][treeType] = tree->getStats()->comps;
                    elapsedArray[statType][treeType] = elapsed;
                }
            }
            //i don't want i/o interrupts that is why i do it one time in loop
            //instead of writing after every operation type on tree
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 2; j++)
                {

                    if (j == 0)
                    {
                        outputFiles[i][j] << statsArray[i][0] << ";" << 
                        statsArray[i][1] << ";" << 
                        statsArray[i][2];
                    }
                    else
                    {
                        outputFiles[i][j] << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsedArray[i][0]).count() << ";" << 
                        std::chrono::duration_cast<std::chrono::nanoseconds>(elapsedArray[i][1]).count() << ";" << 
                        std::chrono::duration_cast<std::chrono::nanoseconds>(elapsedArray[i][2]).count();
                    }

                    outputFiles[i][j] << std::endl;
                }
            }  
            n += nJumpSize;
        }
        delete[] loaded_file;
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 2; j++)
                outputFiles[i][j].close();
    }
}