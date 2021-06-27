#include "functions.hpp"

int main(int argc, char *argv[]){

    int k,n;
    char arrayType;
    std::string testType;
    if(strcmp(argv[1], "-r")==0)
        arrayType=argv[1][1];
    else if(strcmp(argv[1], "-p")==0)
        arrayType=argv[1][1];
    else if(strcmp(argv[1], "ex1")==0){
        printf("EX1 TO CSV\n");
        clock_t time = clock();
        ex1_to_csv();
        time = clock() - time;
        printf("Running time: %ld s\n", time/CLOCKS_PER_SEC);
        return 0;
    }
    else if(strcmp(argv[1], "ex2")==0){
        printf("EX2 TO CSV\n");
        clock_t time = clock();
        ex2_to_csv();
        time = clock() - time;
        printf("Running time: %ld s\n", time/CLOCKS_PER_SEC);
        return 0;
    }
    else if(strcmp(argv[1], "ex3") == 0){
        printf("EX3 TO CSV\n");
        clock_t time = clock();
        ex3_to_csv();
        time = clock() - time;
        printf("Running time: %ld s\n", time/CLOCKS_PER_SEC);
        return 0;
    }
    else if(strcmp(argv[1], "ex4") == 0){
        printf("EX4 TO CSV\n");
        clock_t time = clock();
        ex4_to_csv();
        time = clock() - time;
        printf("Running time: %ld s\n", time/CLOCKS_PER_SEC);
        return 0;
    }

    printf("Type n and k\n");
    std::cin>>n>>k;
    ex1_from_input(arrayType,n,k);

    return 0;
}


