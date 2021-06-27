#include "functions.hpp"
#include <algorithm>

int getRand(const int& A, const int& B) {
    static std::random_device randDev;
    static std::mt19937 twister(randDev());
    static std::uniform_int_distribution<int> dist;

    dist.param(std::uniform_int_distribution<int>::param_type(A, B));
    return dist(twister);
}

void fillWithRandom(int *arr, int n){
    for(int i=0; i<n; i++){
        arr[i]=getRand(1,6*n);
    }
}

int myrandom (int i) { return std::rand()%i;}
void fillWithPermutation(int *arr, int n){

    std::srand ( unsigned ( std::time(0) ) );

    for(int i=0; i<n; i++)
        arr[i]=i;
    std::random_shuffle(arr, arr+n, myrandom);    
}

void displayArrayWithHighlight(int *arr, int n, int idxForHighlight){
    
    for(int i=0; i<n; i++){
        if(i==idxForHighlight){
                printf("\033[31;1;4m%d \033[0m",arr[i]);
        }
        else
            printf("%d ",arr[i]); 
    }
        printf("\n");
} 
    
void displayArray(int *arr, int n){
    for(int i=0; i<n; i++){
        printf("%d ",arr[i]); 
    }
    printf("\n");
} 
double calculateSD(int data[], double mean)
{
    double standardDeviation = 0.0;

    int i;
    int attempts = 100;

    for(i = 0; i < attempts; ++i)
        standardDeviation += pow((double)data[i] - mean, 2);

    return (double)sqrt(standardDeviation / (double)attempts);
}

double calculateSDT(clock_t data[], clock_t mean)
{
    double standardDeviation = 0.0;

    int i;
    int attempts = 100;

    for(i = 0; i < attempts; ++i)
        standardDeviation += pow((double)data[i] - mean, 2);

    return sqrt(standardDeviation / (double)attempts);
}

bool isSorted(int arr[], int length){

    for(int i = 0; i < length-1; i++) 
    {
        if(arr[i] > arr[i+1]){
            if(arr[i]!=arr[i+1]) return false;
        }
    }
    return true;
}