#include "functions.hpp"
#include <fstream>
#include <iomanip>
#include <stdlib.h>

/*
#define modes 2;
#define attempts 100;
#define numOfk 3;
#define numOfAlgos 2;
#define numOfStats 2;
*/
using namespace std;

double calculateSD(int data[], double mean);
double calculateSDT(clock_t data[], clock_t mean);

void ex1_to_csv(){

    //0 - index of randSelect
    //1 - index of medianSelect

    /*arrayStruct 
        fd[rand/perm][k][algos][cmp/shift]
    */
    std::ofstream file[2][3][2][3];

    for(int mode=0; mode<2; mode++){
        for(int k=0; k<3; k++){
            for(int algo=0; algo<2; algo++){
                for(int stat=0; stat<3; stat++){
                    size_t length = strlen("./OUTPUT_DATA/ex1/csv/mode%dk%dalgo%dstat%d.csv");
                    char buffer[length];
                    sprintf(buffer, "./OUTPUT_DATA/ex1/csv/mode%dk%dalgo%dstat%d.csv", mode, k, algo, stat);
                    file[mode][k][algo][stat].open(buffer, std::ios::trunc | std::ios::out);
                    file[mode][k][algo][stat]<<"n;avg;min;max;standard_deviation"<<endl;
                }
            }
        }
    }
    int avgCmp[3][2] = {{0}};
    int minCmp[3][2] = {{0}};
    int maxCmp[3][2] = {{0}};
    int avgShifts[3][2] = {{0}};
    int minShifts[3][2] = {{0}};
    int maxShifts[3][2] = {{0}};
    int arrOfCmp[3][2][100] = {{{0}}};
    int arrOfShifts[3][2][100] = {{{0}}};
    clock_t avgTime[3][2] = {{0}};
    clock_t maxTime[3][2] = {{0}};
    clock_t minTime[3][2] = {{0}};
    clock_t arrOfTimes[3][2][100] = {{{0}}};
    clock_t time;

    Stats *s = new Stats;
    s->print=false;
    int *arrCp;
    int *arrForTest;
    int toFind;
    int kthElem;
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
                    for(int algo=0; algo<2; algo++){
                        
                        copy(arrCp, arrCp + n, arrForTest);
                        
                        s->cmp_count=0;
                        s->shift_count=0;
                        if(algo==0){
                            time = clock();
                            kthElem = randomized_select(s, arrForTest, 0, n-1, toFind);
                            time = clock() - time;
                        }
                        else{
                            time = clock();
                            kthElem = median_select(s, arrForTest, 0, n-1, toFind, 5);
                            time = clock() - time;
                        }
                        time = 1000000*time/CLOCKS_PER_SEC; //conversion to milisecs
                        
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
                            minCmp[k][algo] = s->cmp_count;
                            minShifts[k][algo] = s->shift_count;
                            minTime[k][algo] = time;
                        }

                        avgCmp[k][algo] += s->cmp_count;
                        avgShifts[k][algo] += s->shift_count;
                        avgTime[k][algo] += time;

                        if(s->cmp_count > maxCmp[k][algo])
                            maxCmp[k][algo] = s->cmp_count;
                        else if(s->cmp_count < minCmp[k][algo])
                            minCmp[k][algo] = s->cmp_count;

                        if(s->shift_count > maxShifts[k][algo])
                            maxShifts[k][algo] = s->shift_count;
                        else if(s->shift_count < minShifts[k][algo])
                            minShifts[k][algo] = s->shift_count;

                        if(time > maxTime[k][algo])
                            maxTime[k][algo] = time;
                        else if(time < minTime[k][algo])
                            minTime[k][algo] = time;

                        arrOfCmp[k][algo][attempt] = s->cmp_count;
                        arrOfShifts[k][algo][attempt] = s->shift_count;
                        arrOfTimes[k][algo][attempt] = time;
                    }
                }
            }
            
            for(int k1=0; k1<3; k1++){
                for(int algo1=0; algo1<2; algo1++){
                    for(int stat1=0; stat1<3; stat1++){
                        if(stat1==0){
                            double retAvgCmp = (double)(avgCmp[k1][algo1])/100.0;
                            double sdCmp = calculateSD(arrOfCmp[k1][algo1], retAvgCmp);
                            file[mode][k1][algo1][stat1] << n << ";" << 
                                std::fixed << std::setprecision(2)<< retAvgCmp <<
                                ";" << minCmp[k1][algo1] << ";" <<  maxCmp[k1][algo1] << ";"
                                << sdCmp << std::endl; 
                        }
                        else if(stat1 == 1){
                            double retAvgShifts = (double)(avgShifts[k1][algo1])/100.0;
                            double sdSh = calculateSD(arrOfShifts[k1][algo1], (double)retAvgShifts);
                            file[mode][k1][algo1][stat1] << n << ";" << 
                                std::fixed << std::setprecision(2) << retAvgShifts <<
                                ";" << minShifts[k1][algo1] << ";" << maxShifts[k1][algo1] <<";"
                                << sdSh << std::endl;   
                        }
                        else{
                            clock_t retAvgTime = avgTime[k1][algo1]/100;
                            double sdT = calculateSDT(arrOfTimes[k1][algo1], retAvgTime);
                            file[mode][k1][algo1][stat1] << n << ";" << 
                                std::fixed << std::setprecision(2)<< retAvgTime <<
                                ";" << minTime[k1][algo1] << ";" << maxTime[k1][algo1]<<";"
                                << sdT << std::endl;  
                        }
                    }
                }
            }   
            
            fill(avgCmp[0] + 0, avgCmp[3] + 2, 0);
            fill(minCmp[0] + 0, minCmp[3] + 2, 0);
            fill(maxCmp[0] + 0, maxCmp[3] + 2, 0);

            fill(avgShifts[0] + 0, avgShifts[3] + 2, 0);
            fill(minShifts[0] + 0, minShifts[3] + 2, 0);
            fill(maxShifts[0] + 0, maxShifts[3] + 2, 0);

            fill(avgTime[0] + 0, avgTime[3] + 2, 0);
            fill(minTime[0] + 0, minTime[3] + 2, 0);
            fill(maxTime[0] + 0, maxTime[3] + 2, 0);

            memset(arrOfCmp, 0, sizeof(arrOfCmp[0][0][0]) * 100 * 3 * 2);
            memset(arrOfShifts, 0, sizeof(arrOfShifts[0][0][0]) * 100 * 3 * 2);
            memset(arrOfTimes, 0, sizeof(arrOfShifts[0][0][0]) * 100 * 3 * 2);
            
            delete[] arrForTest;
            delete[] arrCp;
        }
    }

    for(int mode=0; mode<2; mode++)
        for(int k=0; k<3; k++)
            for(int algo=0; algo<2; algo++)
                for(int stat=0; stat<3; stat++)
                    file[mode][k][algo][stat].close();
    return;                               
}

