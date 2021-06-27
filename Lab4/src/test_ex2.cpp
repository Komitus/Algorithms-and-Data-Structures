#include "tools.hpp"
#include "splay-Tree.hpp"
#include "rb-Tree.hpp"
#include <memory>

void test_ex2()
{
    std::cout << "Test EX2 started" << std::endl;
    //for shuffles
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};
    
    
    const int numOfStats = 2; //time/comp
    const int numOfTrees = 3;
    const int numOfIdxTypes = 4;
    const int numOfIndexes = 40;
    const int nJumpSize = 1000;

    int n;
    int numOfShuffles = 0;
    int lastIndexOfFile = 0;
    

    std::unique_ptr<Tree> tree;
    //test for lotr.txt is in ex1
    std::string file_name= "./Test_Data/in_files/aspell";
    std::string statNames[2] = {"_comps", "_time(ns)"};
    std::string indexes_positions[4] = {"start", "mid", "end", "rand"};

    std::string statsTypes;
    std::string treeName;
    std::string outputDir;
    std::ofstream outputFiles[numOfIdxTypes][numOfStats];

    uint32_t statsArray[numOfIdxTypes][numOfTrees];
    std::chrono::high_resolution_clock::duration elapsedArray[numOfIdxTypes][numOfTrees];

    //std::vector<std::string> loaded_file;
    //std::vector<uint32_t> lastIndexOfFile;
    std::string *aspellSorted;
    std::string *aspellShuffled;

    uint32_t array_indexes[numOfIdxTypes][numOfIndexes];
    uint32_t *helper_idxes_array;
    std::string tmpString;
    uint32_t tmpStat;

    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::high_resolution_clock::duration elapsed;

   

    for (int testFile = 0; testFile < 2; testFile++)
    {   
        switch (testFile)
        {
        case 0:
            outputDir = "./Test_Data/out_files/ex2/csv/aspell/";
            numOfShuffles = 0;
            lastIndexOfFile = countLinesInFile(file_name + ".txt") - 1;
            load_into_array(aspellSorted, file_name + "FIXED.txt", lastIndexOfFile+1);
            break;
        case 1:
            outputDir = "./Test_Data/out_files/ex2/csv/aspell_permut/";
            numOfShuffles = 99;   //in fact 100 bcs from 0 to (included) 99
            break;
        }

        n = 1000;
    
        for (int i = 0; i < numOfIdxTypes; i++)
            for (int j = 0; j < numOfStats; j++)
            {
                outputFiles[i][j].open(outputDir + indexes_positions[i] + statNames[j] + ".csv", std::ofstream::trunc | std::ofstream::out);
                outputFiles[i][j] << "n;BST;RBT;SPL" << std::endl;
            }

        
        while (n < lastIndexOfFile)
        {   
            aspellShuffled = new std::string[n];
            
            for(int i=0; i < n; i++)
                aspellShuffled[i] = aspellSorted[i];

            for (int i = 0; i < numOfIndexes; i++)
            {
                array_indexes[0][i] = 20*(n/nJumpSize)+i; 
                if(i < numOfIndexes/2)
                    array_indexes[1][i] = ((n-1)/2)-(numOfIndexes-i);
                else
                    array_indexes[1][i] = ((n-1)/2)+i;
                array_indexes[2][i] = n-20*(n/nJumpSize)-1-(numOfIndexes-1-i);
                array_indexes[3][i] = getRand(0, n-1);
            }

            for (int i = 0; i < numOfIdxTypes; i++)
                    for (int j = 0; j < numOfStats; j++)
                        outputFiles[i][j] << n << ";";

            for (int i = 0; i < numOfTrees; i++)
            {
                for (int j = 0; j < numOfIdxTypes; j++)
                {
                    statsArray[j][i] = 0;
                    elapsedArray[j][i].zero();
                }
            }

            for (int shuffles = 0; shuffles <= numOfShuffles; shuffles++)
            {   
                if(numOfShuffles > 0)
                    std::shuffle(aspellShuffled, aspellShuffled+n, rng);

                for (int treeType = 0; treeType < numOfTrees; treeType++)
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

                    for (int i = 0; i < n; i++)
                        tree->insert(aspellShuffled[i]);   //i dont do shuffle when i have first file

                    for (int idxType = 0; idxType < numOfIdxTypes; idxType++)
                    {
                        elapsed.zero();
                        tree->resetCompares();

                        helper_idxes_array = array_indexes[idxType];

                        for (int i = 0; i < numOfIndexes; i++)
                        {   
                            tmpString = aspellSorted[helper_idxes_array[i]];
                            begin = std::chrono::high_resolution_clock::now();
                            tree->find(tmpString);
                            end = std::chrono::high_resolution_clock::now();
                            elapsed = elapsed + (end - begin);
                        }
                        elapsed /= numOfIndexes;
                        tmpStat = (uint32_t)std::round((double)tree->getStats()->comps / (double)numOfIndexes);
                        statsArray[idxType][treeType] += tmpStat;
                        elapsedArray[idxType][treeType] += elapsed;
                    }
                }
            }
            //i don't want i/o interrupts that is why i do it one time in loop
            //instead of writing after every operation type on tree
            for (int i = 0; i < numOfIdxTypes; i++)
            {
                //i don't want do this in loop bcs i want one line, dont want unnecessary interrupts
                outputFiles[i][0]
                    << (uint32_t)std::round((double)statsArray[i][0] / (double)(numOfShuffles+1)) << ";" 
                    << (uint32_t)std::round((double)statsArray[i][1] / (double)(numOfShuffles+1)) << ";" 
                    << (uint32_t)std::round((double)statsArray[i][2] / (double)(numOfShuffles+1))
                    << std::endl;

                elapsedArray[i][0]/=(numOfShuffles+1); 
                elapsedArray[i][1]/=(numOfShuffles+1);
                elapsedArray[i][2]/=(numOfShuffles+1);
                
                outputFiles[i][1] 
                    << std::chrono::duration_cast<std::chrono::nanoseconds>(
                        elapsedArray[i][0]
                        ).count() << ";" 
                    << std::chrono::duration_cast<std::chrono::nanoseconds>(
                        elapsedArray[i][1]
                        ).count() << ";" 
                    << std::chrono::duration_cast<std::chrono::nanoseconds>(
                        elapsedArray[i][2]
                        ).count()
                    << std::endl; 
            }

            delete[] aspellShuffled;
            n += nJumpSize;
        }

        for (int i = 0; i < numOfIdxTypes; i++)
            for (int j = 0; j < numOfStats; j++)
                outputFiles[i][j].close();
    }
    delete[] aspellSorted;
}