#include "functions.hpp"

#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <chrono>

using namespace std;

bool binary_search(int &compares, int arr[], int l, int r, int x){

    if(r>=l){
        int mid = (r+l)/2;
        
        compares++;
        if(arr[mid] == x){
            return true;
        }
        compares++;
        if(arr[mid]>x){
            return binary_search(compares, arr, l, mid-1, x);
        }
        return binary_search(compares, arr, mid + 1, r, x);
        
    }
    return false;
}

void ex3_to_csv(){

    std::ofstream file[5];
    string directory = "./OUTPUT_DATA/ex3/csv/";
    for(int elem_position=0; elem_position<5; elem_position++){

        string position = "";
        switch(elem_position){
            case 0:
                position.append("begin");
                break;
            case 1:
                position.append("mid");
                break;
            case 2:
                position.append("end");
                break;
            case 3:
                position.append("rand");
                break;
            case 4:
                position.append("outside");
                break;
        }
        directory.append(position.append(".csv"));
        file[elem_position].open(directory, std::ios::trunc | std::ios::out);
        file[elem_position]<<"n;compares;time"<<endl;
        directory = "./OUTPUT_DATA/ex3/csv/";
        
    }

    int *arrForTest;
    int toFind;
    int compares  = 0;
    
    auto begin = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    for(int n=1000; n<=100000; n+=1000){

        arrForTest = new int[n];

        for(int i=0; i<n; i++)
                    arrForTest[i]=i;
        for(int elem_position=0; elem_position<5; elem_position++){
            
            if(elem_position<3){
                compares = 0;

                switch(elem_position){
                    case 0:
                        toFind = arrForTest[6*(n/1000)];  //i dynamically change position proper to the length
                        break;
                    case 1:
                        toFind = arrForTest[(n-1)/2];
                        break;
                    case 2:
                        toFind = arrForTest[n-(6*(n/1000)+1)];
                        break;
                }
               
                begin = std::chrono::high_resolution_clock::now();
                binary_search(compares, arrForTest, 0, n-1, toFind);
                end = std::chrono::high_resolution_clock::now();
                elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            }
            else{
                int tmpCompares = 0;

                auto tmpElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                tmpElapsed.zero();
                if(elem_position == 4){
                    arrForTest[0]=0;
                    for(int i=1; i<n; i++)
                        arrForTest[i]=arrForTest[i-1]+2;    
                }
                
                for(int m=0; m<1000; m++){
                    //rand
                    if(elem_position == 3) 
                        toFind = arrForTest[getRand(0,n-1)];
                    else    
                        toFind = arrForTest[getRand(0, n-1)]+1;
                    begin = std::chrono::high_resolution_clock::now();
                    binary_search(tmpCompares, arrForTest, 0, n-1, toFind);
                    end = std::chrono::high_resolution_clock::now();
                    tmpElapsed += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                    
                }
                elapsed = tmpElapsed/1000; 
                compares = tmpCompares/1000;
            }
            
            file[elem_position]<<n<<";"<<compares<<";"<<elapsed.count()<<endl;
        }
        delete[]arrForTest;
    }

    for(int elem_position=0; elem_position<5; elem_position++)
        file[elem_position].close();   
    return; 
}


