#include "functions.hpp"

#include <fstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

double calculateSD(int data[], double mean);
double calculateSDT(clock_t data[], clock_t mean);

void ex2_to_csv(){

    //0 - index of randSelect
    //1 - index of medianSelect

    /*arrayStruct 
        fd[rand/perm][k][algos][cmp/shift]
    */
    std::ofstream file[2][3][13][3];   //index[0] at group_size unused
    
    for(int mode=0; mode<2; mode++){
        for(int k=0; k<3; k++){
            for(int group_size=3; group_size<=25; group_size+=2){
                for(int stat=0; stat<3; stat++){
                    size_t length = strlen("./OUTPUT_DATA/ex2/csv/mode%dk%dgroupSize%dstat%d.csv");
                    char buffer[length];
                    sprintf(buffer, "./OUTPUT_DATA/ex2/csv/mode%dk%dgroupSize%dstat%d.csv", mode, k, group_size, stat);
                    file[mode][k][group_size/2][stat].open(buffer, std::ios::trunc | std::ios::out);
                    file[mode][k][group_size/2][stat]<<"n;avg;min;max;standard_deviation"<<endl;
                }
            }
        }
    }
    
    //12 is numb of groupSizes
    // numb of k then numb of groupsTests
    int avgCmp[3][13] = {{0}};
    int minCmp[3][13] = {{0}};
    int maxCmp[3][13] = {{0}};
    int avgShifts[3][13] = {{0}};
    int minShifts[3][13] = {{0}};
    int maxShifts[3][13] = {{0}};
    int arrOfCmp[3][13][100] = {{{0}}};
    int arrOfShifts[3][13][100] = {{{0}}};
    clock_t avgTime[3][13] = {{0}};
    clock_t maxTime[3][13] = {{0}};
    clock_t minTime[3][13] = {{0}};
    clock_t arrOfTimes[3][13][100] = {{{0}}};
    clock_t time;
   
    Stats *s = new Stats;
    s->print=false;
    int *arrCp;
    int *arrForTest;
    int toFind;
    int kthElem;
    int idx_of_group_size;

    for(int mode=0; mode<2; mode++){

        for(int n=100; n<=10000; n+=100){

            arrForTest = new int[n];
            arrCp = new int[n];
            
            for(int attempt=0; attempt<100; attempt++){

                if(mode==0)
                    fillWithRandom(arrCp,n);
                else
                    fillWithPermutation(arrCp,n);

                for(int k=0; k<3; k++){

                    switch(k){
                        case 0:
                            toFind = 50;
                            break;
                        case 1:
                            toFind = n/2;
                            break;
                        case 2:
                            toFind = n-20;
                            break;
                        }
                    
                    for(int group_size=3; group_size<=25; group_size+=2){
                        
                        idx_of_group_size = group_size/2;
            
                        copy(arrCp, arrCp + n, arrForTest);
                        s->cmp_count=0;
                        s->shift_count=0;

                        time = clock();
                        kthElem = median_select(s, arrForTest, 0, n-1, toFind, group_size);
                        time = clock() - time;
                        time = 1000000*time/CLOCKS_PER_SEC; //conversion to micro_secs
                        
                        quick_sort_dp(s, arrForTest, 0, n-1);
                        if(!isSorted){
                            std::cerr<<"ArrayNotSorted";
                            return;
                        } 
                        if(arrForTest[toFind-1]!=kthElem){
                            std::cerr<<"K'th elem isn't properly found";
                            return;
                        }
                        
                        if(attempt==0){
                            minCmp[k][idx_of_group_size] = s->cmp_count;
                            minShifts[k][idx_of_group_size]= s->shift_count;
                            minTime[k][idx_of_group_size] = time;
                        }

                        avgCmp[k][idx_of_group_size] += s->cmp_count;
                        avgShifts[k][idx_of_group_size] += s->shift_count;
                        avgTime[k][idx_of_group_size] += time;

                        if(s->cmp_count > maxCmp[k][idx_of_group_size])
                            maxCmp[k][idx_of_group_size]= s->cmp_count;
                        else if(s->cmp_count < minCmp[k][idx_of_group_size])
                            minCmp[k][idx_of_group_size]= s->cmp_count;

                        if(s->shift_count > maxShifts[k][idx_of_group_size])
                            maxShifts[k][idx_of_group_size]= s->shift_count;
                        else if(s->shift_count < minShifts[k][idx_of_group_size])
                            minShifts[k][idx_of_group_size]= s->shift_count;

                        if(time > maxTime[k][idx_of_group_size])
                            maxTime[k][idx_of_group_size]= time;
                        else if(time < minTime[k][idx_of_group_size])
                            minTime[k][idx_of_group_size]= time;

                        arrOfCmp[k][idx_of_group_size][attempt] = s->cmp_count;
                        arrOfShifts[k][idx_of_group_size][attempt]= s->shift_count;
                        arrOfTimes[k][idx_of_group_size][attempt] = time;
                    }
                }
            }
            
            for(int k1=0; k1<3; k1++){
                for(int group_size1=3; group_size1<=25; group_size1+=2){
                    for(int stat1=0; stat1<3; stat1++){
                        idx_of_group_size = group_size1/2;
                        if(stat1==0){
                            double retAvgCmp = (double)(avgCmp[k1][idx_of_group_size])/100.0;
                            double sdCmp = calculateSD(arrOfCmp[k1][idx_of_group_size], retAvgCmp);
                            file[mode][k1][idx_of_group_size][stat1] << n << ";" << 
                                std::fixed << std::setprecision(2)<< retAvgCmp <<
                                ";" << minCmp[k1][idx_of_group_size] << ";" <<  maxCmp[k1][idx_of_group_size] << ";"
                                << sdCmp << std::endl; 
                        }
                        else if(stat1 == 1){
                            double retAvgShifts = (double)(avgShifts[k1][idx_of_group_size])/100.0;
                            double sdSh = calculateSD(arrOfShifts[k1][idx_of_group_size], (double)retAvgShifts);
                            file[mode][k1][idx_of_group_size][stat1] << n << ";" << 
                                std::fixed << std::setprecision(2) << retAvgShifts <<
                                ";" << minShifts[k1][idx_of_group_size] << ";" << maxShifts[k1][idx_of_group_size] <<";"
                                << sdSh << std::endl;   
                        }
                        else{
                            clock_t retAvgTime = avgTime[k1][idx_of_group_size]/100;
                            double sdT = calculateSDT(arrOfTimes[k1][idx_of_group_size], retAvgTime);
                            file[mode][k1][idx_of_group_size][stat1] << n << ";" << 
                                std::fixed << std::setprecision(2)<< retAvgTime <<
                                ";" << minTime[k1][idx_of_group_size] << ";" << maxTime[k1][idx_of_group_size]<<";"
                                << sdT << std::endl;  
                        }
                    }
                }
            }   
            
            fill(avgCmp[0] + 0, avgCmp[3] + 12, 0);
            fill(minCmp[0] + 0, minCmp[3] + 12, 0);
            fill(maxCmp[0] + 0, maxCmp[3] + 12, 0);

            fill(avgShifts[0] + 0, avgShifts[3] + 12, 0);
            fill(minShifts[0] + 0, minShifts[3] + 12, 0);
            fill(maxShifts[0] + 0, maxShifts[3] + 12, 0);

            fill(avgTime[0] + 0, avgTime[3] + 12, 0);
            fill(minTime[0] + 0, minTime[3] + 12, 0);
            fill(maxTime[0] + 0, maxTime[3] + 12, 0);

            memset(arrOfCmp, 0, sizeof(arrOfCmp[0][0][0]) * 100 * 3 * 12);
            memset(arrOfShifts, 0, sizeof(arrOfShifts[0][0][0]) * 100 * 3 * 12);
            memset(arrOfTimes, 0, sizeof(arrOfShifts[0][0][0]) * 100 * 3 * 12);
            
            delete[] arrForTest;
            delete[] arrCp;
            
        }
    }

    for(int mode=0; mode<2; mode++)
        for(int k=0; k<3; k++)
            for(int group_size=3; group_size<=25; group_size+=2)
                for(int stat=0; stat<3; stat++)
                    file[mode][k][group_size/2][stat].close();
    return;
}

