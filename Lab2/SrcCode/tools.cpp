#include "tools.hpp"

std::string* cmdParser(int argc, char **argv){
    
    int len = 5;
    std::string* resParam = new std::string[len];
    //newer compare from C++ requires strings not char*
    for(int i=1; i < argc; i++){
        if(strcmp(argv[i], "--type")==0) 
            resParam[0]=argv[i+1];
        else if(strcmp(argv[i], "--comp")==0) 
            resParam[1]=argv[i+1];
        else if(strcmp(argv[i], "--stat")==0){
            resParam[2]=argv[i+1];
            resParam[3]=argv[i+2];
        }
        else if(strcmp(argv[i], "--data")==0){
            resParam[4]=argv[i+1];
        }
    }
    return resParam;
}

int getRand(const int& A, const int& B) {
    static std::random_device randDev;
    static std::mt19937 twister(randDev());
    static std::uniform_int_distribution<int> dist;

    dist.param(std::uniform_int_distribution<int>::param_type(A, B));
    return dist(twister);
}

void fillWithRandom(int* arr, int n){
    
}

template<>
auto getComparator<int>(bool asc) -> auto (*)(int, int) -> bool {
    if (asc)
        return [](int x, int y) { return x < y; };
    else
        return [](int x, int y) { return x > y; };
}

template<>
auto getComparator<std::string>(bool asc) -> auto (*)(std::string, std::string) -> bool {
    if (asc)
        return [](std::string x, std::string y) { return x < y; };
    else
        return [](std::string x, std::string y) { return x > y; };
}
template<>
void fillWithRandom<int>(int *arr, int n){
    for(int i=0; i<n; i++){
        arr[i]=getRand(1,20000);
    }
}
template<>
void fillWithRandom<std::string>(std::string *arr, int n){
    int wordLength = getRand(1, 40);
    std::string *stringArr = new std::string[n];
    char letter;
    for(int i=0; i<n; i++){
        stringArr[i] = "";
        for(int j=0; j<wordLength;j++){
            letter = 'A'+getRand(0,57);
            stringArr[i].push_back(letter);
        }
        arr[i] = stringArr[i];
    }
}