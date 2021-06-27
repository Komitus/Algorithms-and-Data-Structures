#ifndef _algos

#define _algos
#include <iostream>
#include "tools.hpp"


template<typename T>
void insertionSort(struct myData<T> *data, Stats *stats)
{ 
    int length = data -> length; //Length of array to sort.
    T* array = data -> array; //Pointer to array to sort.
    T key;
    int i,j;
    bool firstTime;   // to solve problem with index of array below 0
    for (i = 1; i < length; i++)
    { 
        firstTime = true;
        key = array[i];
        j = i - 1; 
         if(stats->print) std::cerr<<"Compare: A["<<i<<"]="<<key<<" "<<"comparator"<<" "<<array[j]<<"=["<<j<<"]A"<<std::endl; 
        stats->cmp_count++;
        while (j >= 0 && data->comparator(key, array[j]))  // we want check if smt with less index is !"comparator" than our key
        {   
            if(!firstTime) {  //this can change measured time of algo but is neccessary
                 if(stats->print) std::cerr<<"Compare: A["<<i<<"]="<<key<<" "<<"comparator"<<" "<<array[j]<<"=["<<j<<"]A"<<std::endl; 
                stats->cmp_count++;
            }
             if(stats->print) std::cerr<<"Shift: "<<array[j+1]<<" <-> "<<array[j]<<std::endl;
            stats->shift_count++;
            array[j + 1] = array[j]; 
            j = j - 1;
            firstTime = false;
        } 
        
        array[j + 1] = key; 
    } 
} 

template<typename T>
void merge(struct myData<T> *data, Stats* stats, int l, int m, int h)
{   
    T *arr = data->array;
    int n1 = m - l + 1;
    int n2 = h - m;
    
    // Create temp arrays
    T* L = new T[n1];
    T* R = new T[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
 
    // Initial index of first subarray
    int i = 0;
 
    // Initial index of second subarray
    int j = 0;
 
    // Initial index of merged subarray
    int k = l;
 
    while (i < n1 && j < n2) {

    	stats->cmp_count++;
         if(stats->print) std::cerr << "Compare: " << "L["<<i<<"]="<<L[i]<<" "<< "comparator" <<" " << R[j]<<"=["<<j<<"]R" << std::endl;
        
        if (data->comparator(L[i], R[j])) {     
            stats->shift_count++;  
             if(stats->print) std::cerr << "Shift: A[" << k <<"]:=" << L[i] << std::endl; 
            arr[k] = L[i];
            i++;
        }
        else {
            stats->shift_count++;
             if(stats->print) std::cerr << "Shift: A[" << k <<"]:=" << R[j] << std::endl; 
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        stats->shift_count++;  
         if(stats->print) std::cerr << "Shift: A[" << k <<"]:=" << L[i] << std::endl; 
        arr[k] = L[i];
        i++;
        k++;
    }
    delete[] L;
    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        stats->shift_count++;
         if(stats->print) std::cerr << "Shift: A[" << k <<"]:=" << R[j] << std::endl; 
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] R;
}
// l is for low index and h is
// h index of the sub-array
// of arr to be sorted */
template<typename T>
void mergeSort(struct myData<T> *data, Stats *stats, int l, int h){
    if(l>=h){
        return;//returns recursively
    }
    int m =l+ (h-l)/2;
    mergeSort(data, stats, l, m);
    mergeSort(data, stats, m+1, h);
    merge<T>(data,stats, l, m, h);
}
//helper function for quickSort
template<typename T>
int HoaresPartition (struct myData<T> *data, Stats* stats, int low, int high) 
{   
    int pivot_index = (int)((low+high)/2);
    T pivot = data->array[pivot_index];
    int i = low-1;
    int j = high+1;
    
    while(true) {
        do{
            i++;
            stats->cmp_count++;
            if(stats->print) std::cerr << "Compare: " << "A["<<i<<"]="<<data->array[i]<<" "<< "comparator" <<" " << pivot<<"= pivot" << std::endl;
        }while(data->comparator(data->array[i], pivot));

        do{
            j--;
            stats->cmp_count++;
            if(stats->print) std::cerr << "Compare: " << "Pivot ="<<pivot<<" "<< "comparator"<<" "<<"A["<< data->array[j]<<"]" << std::endl;
        }while(data->comparator(pivot, data->array[j]));
        if(i>=j) return j;
            stats->shift_count++;
            if(stats->print) std::cerr<<"Shift: A[" << i <<"]="<<data->array[i]<<" <-> "<<data->array[j]<<"=["<<j<<"]A"<<std::endl;
            std::swap(data->array[i], data->array[j]);
    }
    
}

//The main function of quicksort
template<typename T>
void quickSort(struct myData<T> *data, Stats* stats, int low, int high) 
{ 
    if (low < high) //we dont want to cross
    { 
        int p = HoaresPartition<T>(data, stats, low, high); //pivot
        quickSort(data, stats, low, p); 
        quickSort(data, stats, p + 1, high); 
    } 
} 


template<typename T>
void quickSortDP(struct myData<T> *data, Stats *stats, int left, int right){

    T p,q;
    int i, j,k,d;
    T* arr = data->array;
    bool print = stats->print;
    
    if(right <= left)
        return;

        if(print) std::cerr<<"Compare: A[" << right<<"]= "<<arr[right]<<" comparator "<<arr[left]<<" =["<<left<<"]A"<<std::endl;
        stats->cmp_count++;

    if(data->comparator(arr[right], arr[left])){
            if(print) std::cerr<<"Shift: A[" << right<<"]= "<<arr[right]<<" <-> "<<arr[left]<<" =["<<left<<"]A"<<std::endl;
            stats->shift_count++;
        std::swap(arr[right], arr[left]);    
    }
        
    p=arr[left];
    q=arr[right];

    i=left+1;
    k=right-1;
    j=i;
    d=0;   //difference between numb of smaller elements (si-1) than p
    //and larger (li-1) than q
    //or larger and smaller (in case of input >=)
    while(j<=k){
        if(d>=0){

                if(print) std::cerr<<"Compare: A["<<j<<"]= "<<arr[j]<<" comparator "<<p<<" =p"<<std::endl;
                stats->cmp_count++;
            //we had more smaller elems than larger or std::swap this sentence before xd
            if(data->comparator(arr[j],p)){  
                    if(print) std::cerr<<"Shift: A["<<i<<"]= "<<arr[i]<<" <-> "<<arr[j]<<" =["<<j<<"]A"<<std::endl;
                    stats->shift_count++;
                std::swap(arr[i], arr[j]);
                i++; j++; d++;    
            }
            else{
                //it is in right position, we can go to next  
                    if(print) std::cerr<<"Compare: A["<<j<<"]= "<<arr[j]<<" comparator "<<q<<" =q"<<std::endl;
                    stats->cmp_count++;
                if(data->comparator(arr[j],q)){
                    j++;
                }
                //we have found element greater than q it must go at right
                else{    
                        if(print) std::cerr<<"Shift: A["<<j<<"]= "<<arr[j]<<" <-> "<<arr[k]<<" =["<<k<<"]A"<<std::endl;  
                        stats->shift_count++;
                    std::swap(arr[j], arr[k]);
                    k--; d--;
                }
            }
        }
        else{
                if(print) std::cerr<<"Compare: q= "<<q<<" comparator "<<arr[k]<<" =["<<k<<"]"<<std::endl;
                stats->cmp_count++;
            if(data->comparator(q, arr[k])){
                k--; d--;
            }
            else{
                    if(print) std::cerr<<"Compare: A["<<k<<"]= "<<arr[k]<<" comparator "<<q<<" =q"<<std::endl;
                    stats->cmp_count++;
                if(data->comparator(arr[k],p)){
                        if(print) std::cerr<<"Shift: A["<<k<<"]= "<<arr[k]<<" <-> "<<arr[j]<<" =["<<j<<"]A"<<std::endl; 
                    std::swap(arr[k],arr[j]);
                        if(print) std::cerr<<"Shift: A["<<j<<"]= "<<arr[j]<<" <-> "<<arr[i]<<" =["<<i<<"]A"<<std::endl; 
                    std::swap(arr[j],arr[i]);
                    i++; d++;
                        stats->shift_count+=2;
                }
                else{
                        if(print) std::cerr<<"Shift: A["<<j<<"]= "<<arr[j]<<" <-> "<<arr[k]<<" =["<<k<<"]A"<<std::endl; 
                        stats->shift_count++;
                    std::swap(arr[j],arr[k]);
                }
                j++;
            }
        } 
    }
    std::swap(arr[left], arr[i-1]);    //assigning value of p to arr[i-1]
    std::swap(arr[right], arr[k+1]);
    quickSortDP(data, stats, left, i-2);
    quickSortDP(data, stats, i, k);
    quickSortDP(data, stats, k+2, right);
}

template<typename T>
void insertionSortForHybrid(struct myData<T> *data, Stats *stats, int left, int right)
{ 
    T* array = data -> array; //Pointer to array to sort.
    T key;
    int i,j;
    bool firstTime;   // to solve problem with index of array below 0
    for (i = left+1; i < right+1; i++)
    { 
        firstTime = true;
        key = array[i];
        j = i - 1; 
         if(stats->print) std::cerr<<"Compare: A["<<i<<"]="<<key<<" "<<"comparator"<<" "<<array[j]<<"=["<<j<<"]A"<<std::endl; 
        stats->cmp_count++;
        while (j >= 0 && data->comparator(key, array[j]))  // we want check if smt with less index is !"comparator" than our key
        {   
            if(!firstTime) {  //this can change measured time of algo but is neccessary
                 if(stats->print) std::cerr<<"Compare: A["<<i<<"]="<<key<<" "<<"comparator"<<" "<<array[j]<<"=["<<j<<"]A"<<std::endl; 
                stats->cmp_count++;
            }
             if(stats->print) std::cerr<<"Shift: "<<array[j+1]<<" <-> "<<array[j]<<std::endl;
            stats->shift_count++;
            array[j + 1] = array[j]; 
            j = j - 1;
            firstTime = false;
        } 
        
        array[j + 1] = key; 
    } 
} 

template<typename T>
void hybridSort(struct myData<T> *data, Stats *stats, int left, int right, int switchingBound){
    
    if(right-left <= switchingBound){
        insertionSortForHybrid(data, stats, left, right);
        return;
    }

    int pivot = HoaresPartition(data, stats, left, right);

    hybridSort(data, stats, left, pivot, switchingBound);
    hybridSort(data, stats, pivot+1, right, switchingBound);
}

#endif