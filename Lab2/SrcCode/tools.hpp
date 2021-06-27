#ifndef _tools

#define _tools
#include <string>
#include <cstring>
#include <iostream>
#include <random>

typedef struct Stats {
  int cmp_count = 0;
  int shift_count = 0;
  bool print = false;
} Stats;

template <typename T> 
struct myData{
    bool (*comparator)(T, T);
    int length = 0;
    T* array; 
};

std::string* cmdParser(int argc, char **argv);
int getRand(const int& A, const int& B);
template<typename T>
void fillWithRandom(T *arr, int n);
template<typename T>
auto getComparator(bool asc) -> auto (*)(T, T) -> bool;

//with templates
template<typename T>
void displayArray(struct myData<T> *data){
    for(int i=0; i<data->length; i++){
        std::cout<<data->array[i]<<" ";
    }
    std::cout<<std::endl;
}

template<typename T>
bool isSorted(struct myData<T> *data){

    for(int i = 0; i < data->length-1; i++) 
    {
        if(!data->comparator(data->array[i], data->array[i+1])){
            if(data->array[i]!=data->array[i+1]) return false;
        }
    }
    return true;
}

template<typename T>
int countSortedElems(T* prev, struct myData<T> *data){
    int counter = 0;
    for(int i=0; i<data->length; i++)
        if(data->array[i]!=prev[i]) 
            counter++;
    return counter;
}


#endif