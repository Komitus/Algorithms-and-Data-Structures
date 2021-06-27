#ifndef _tools
#define _tools
#include <fstream>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "tree.hpp"
#include <chrono>
#include <random>
//parsers and other stuff
std::string remove_char(std::string str);
std::string repair_file(std::string file_name);

std::vector<std::string> * split(const std::string txt);
void handle_input(Tree *tree, std::string inFile_name, std::string outFile_name);
void read_from_file(std::string tree_type, std::string inputFile_name, std::string outputFile_name);
std::string do_instruction (std::string line, Tree *tree);
std::string* cmdParser(int argc, char **argv);
void print_stats(stats *s, std::chrono::high_resolution_clock::duration elapsed_time);
void load_into_vector(std::vector<std::string> &myVector, std::string file_name);
int getRand(const int& A, const int& B);
void test_ex1();
void test_ex2();
void load_into_array(std::string *&array, std::string filename, uint32_t size);
uint32_t countLinesInFile(std::string filename);

#endif