#include <iostream>
#include "algorithms.hpp"
#include <cstring>
#include <ctime>
#include "tools.hpp"
#include "output.hpp"


int main(int argc, char *argv[]){
    
    std::string* params;
    params = cmdParser(argc, argv);
    //check if we want write to file
    // comparator, filename, k
    if(params[4].compare("string") != 0){
        
        switch(argc){
            //default ./main --type ' ' --comp ' ' --data int
            case 7:
                defaultExecution<int>(params);
                return 0;
                break;
            // ./main --comp ' ' --data int
            case 5:
                testInConsole<int>(params);
                return 0;
                break;         //not necessary 
            // ./main --comp ' ' --stat file k --data ' ' 
            case 8:
                clock_t time = clock();
                statsToFile<int>(params);
                time = clock() - time;
                int minutes = (time/CLOCKS_PER_SEC)/60;
                int secs = (time/CLOCKS_PER_SEC)%60;
                std::cout<<"All time: "<<minutes<<"mins "<<secs<<"secs"<<std::endl;
                return 0;           //not necessary
                break;
        }
    }
    else{
        
        switch(argc){
            //default ./main --type ' ' --comp ' ' --data int
            case 7:
                defaultExecution<std::string>(params);
                return 0;
                break;
            case 5:
                testInConsole<std::string>(params);
                return 0;
                break;         //not necessary   
            case 8:
                clock_t time = clock();
                statsToFile<std::string>(params);
                time = clock() - time;
                int minutes = (time/CLOCKS_PER_SEC)/60;
                int secs = (time/CLOCKS_PER_SEC)%60;
                std::cout<<"All time: "<<minutes<<"mins "<<secs<<"secs"<<std::endl;
                return 0;           //not necessary
                break;
        }
    } 
}