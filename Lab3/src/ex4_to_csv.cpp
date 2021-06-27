#include "functions.hpp"

#include <fstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

void ex4_to_csv(){

    int attempts = 100;
    int *array;
    int *arrayCp;
    
    Stats *s = new Stats;
    s->print = false;

    uint64_t mid_swaps[4]; 
    uint64_t mid_compares[4];
    clock_t mid_time[4];
    clock_t time;

    std::ofstream file[2][4];
    string directory;
    
    for(int dataType=0; dataType<2; dataType++){

        string dtype = "";
        switch(dataType){
            case 0:
                dtype.append("rand");
                break;
            case 1:
                dtype.append("worst");
                break;
        }

        for(int algo=0; algo<4; algo++){

            directory = "./OUTPUT_DATA/ex4/csv/";
            string algoType ="";
            switch (algo)
            {
            case 0:
                algoType = "QS";
                break;
            case 1:
                algoType = "QS_DP";
                break;
            case 2:
                algoType = "QS_MEDIAN";
                break;
            case 3:
                algoType = "QS_DP_MEDIAN";
                break;
            }
            directory = directory.append(dtype).append(algoType).append(".csv");
            file[dataType][algo].open(directory, std::ios::trunc | std::ios::out);
            file[dataType][algo]<<"n;compares;shifts;time"<<endl;
        }
    }
    
    for(int dataType=0; dataType<2; dataType++){
     
        for (int n = 100; n <= 10000; n += 100){

            std::fill(mid_compares, mid_compares+4, 0);
            std::fill(mid_swaps, mid_swaps+4, 0);
            std::fill(mid_time, mid_time+4, 0);

            array = new int[n];
            arrayCp = new int[n];

            for (int j = 0; j < attempts; j++){
                
                if(dataType == 0)
                    fillWithRandom(array, n);
                else
                    for(int i=0; i<n; i++)
                        array[i]=i;
                    
                for (int algo = 0; algo < 4; algo++){

                    s->cmp_count = 0;
                    s->shift_count = 0;
                    std::copy(array, array + n, arrayCp);
                
                    switch (algo){
                        
                        case 0:
                            time = clock();
                            quick_sort(s, arrayCp, 0, n-1);
                            time = clock() - time;
                            break;
                        case 1:
                            time = clock();
                            quick_sort_dp(s, arrayCp, 0, n-1);
                            time = clock() - time;
                            break;
                        case 2:
                            time = clock();
                            quick_sort_with_median(s, arrayCp, 0, n-1);
                            time = clock() - time;
                            break;
                        case 3:
                            time = clock();
                            quick_sort_dp_with_median(s, arrayCp, 0, n-1);
                            time = clock() - time;
                            break;
                    }
                    if (!isSorted(arrayCp, n)){
                        std::cerr << "Not sorted by algo nr " << algo << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    
                    mid_compares[algo] += s->cmp_count;
                    mid_swaps[algo] += s->shift_count;
                    mid_time[algo] += time;
                }
            }
            delete[] array;
            delete[] arrayCp;
            //after performing k measures
            for (int i = 0; i < 4; i++)
            {   
                uint64_t final_compares = (uint64_t)(mid_compares[i] / attempts);
                uint64_t final_shifts = (uint64_t)(mid_swaps[i] / attempts);
                double final_time = (double)((double)mid_time[i] / CLOCKS_PER_SEC) / ((double)attempts) * 1000000.0;
                file[dataType][i] << n << ";" << final_compares << ";" << final_shifts << ";" 
                    << std::fixed << std::setprecision(2) << final_time << std::endl;
            }
        }
        
    }
    delete s;
    for(int i=0; i<2; i++)
        for (int j = 0; j < 4; j++)
            file[i][j].close();
    return;
}