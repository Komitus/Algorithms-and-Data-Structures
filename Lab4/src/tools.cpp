#include "tools.hpp"
#include <memory>
#include <iterator>

std::string remove_char (std::string str) 
{
    str.erase(std::remove_if(str.begin(), str.end(), &ispunct), str.end());
    //str.erase(std::remove_if(str.begin(), str.end(), &isspace), str.end());
    //str.erase(std::remove_if(str.begin(), str.end(), &isdigit), str.end()); --to erase digits
    return str;
}

std::string repair_file(std::string file_name)
{
    std::ifstream in_file;
    std::string tmpFile_name;
    in_file.open(file_name, std::ifstream::in);
    
    std::string word;
    if (in_file)
    {   
        std::ofstream out_file;
        tmpFile_name = file_name.substr(0, file_name.find_last_of('.'));
        tmpFile_name = tmpFile_name.append("FIXED.txt");
        out_file.open(tmpFile_name, std::ofstream::out);
        while (in_file >> word)
            out_file << remove_char(word)<<std::endl;

        out_file.close();
    }
    else
    {
        std::cout << "File doesn't exist";
    }

    in_file.close();
    
    return tmpFile_name;
}

std::vector<std::string> * split(const std::string txt)
{
    std::istringstream iss(txt);
    std::vector<std::string> *splitted = new std::vector<std::string>;

    std::string str;
    do {
        iss >> str;
        splitted->push_back(str);
    } while (iss);

    return  splitted;
}

std::string *cmdParser(int argc, char **argv)
{
    int len = 3;
    std::string *resParam = new std::string[len];
    //newer compare from C++ requires strings not char*
      
    for (int i = 1; i < argc; i++)
    {   
        if (strcmp(argv[i], "test_ex1") == 0)
        {
            resParam[0] = argv[i];
            return resParam;
        }
        else if (strcmp(argv[i], "test_ex2") == 0)
        {
            resParam[0] = argv[i];
            return resParam;
        }
        else if (strcmp(argv[i], "tests") == 0)
        {
            resParam[0] = argv[i];
            return resParam;
        }
        else if (strcmp(argv[i], "--type") == 0)
            resParam[0] = argv[i + 1];        
        else if (strcmp(argv[i], "<") == 0)
            resParam[1] = argv[i + 1];
        else if (strcmp(argv[i], ">") == 0)
            resParam[2] = argv[i + 1];
        
    }
    return resParam;
}

void load_into_vector(std::vector<std::string> &myVector, std::string file_name){

    std::ifstream in_file;
    in_file.open(file_name, std::ifstream::in);
    
    std::string word;
    if (in_file)
    {   
        while (in_file >> word)
            myVector.push_back(remove_char(word));
    }
    else
    {
        std::cout << "File doesn't exist";
    }

    in_file.close();
}

int getRand(const int& A, const int& B) {
    static std::random_device randDev;
    static std::mt19937 twister(randDev());
    static std::uniform_int_distribution<int> dist;

    dist.param(std::uniform_int_distribution<int>::param_type(A, B));
    return dist(twister);
}
//we must here pass fixed file
void load_into_array(std::string *&array, std::string filename, uint32_t size)
{
    std::ifstream in_file;

    in_file.open(filename, std::ifstream::in);
    
    if(in_file)
    {
        std::string word;
        array = new std::string[size];
        for(uint32_t i = 0; i < size; i++) 
        {
            in_file >> word;
            array[i] = word;
        }       
    }
    else
        std::cout<<"No such file"<<std::endl;
     
}

uint32_t countLinesInFile(std::string filename)
{   
    std::ifstream in_file;
    std::string repaired_file = repair_file(filename);
    uint32_t number_of_lines = 0;
    if(!repaired_file.empty()){

        in_file.open(repaired_file, std::ifstream::in);
        in_file.unsetf(std::ios_base::skipws);

        // count the newlines with an algorithm specialized for counting:
        number_of_lines = std::count(
        std::istream_iterator<char>(in_file),
        std::istream_iterator<char>(),
        '\n');
    }
    return number_of_lines;
}