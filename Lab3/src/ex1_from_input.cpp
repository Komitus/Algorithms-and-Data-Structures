#include "functions.hpp"

void ex1_from_input(char arrType, int n, int k){
    
    int *arrForTest = new int[n];
    int *arrCp = new int[n];
    int searched;
    if(arrType=='r')
        fillWithRandom(arrCp, n);
    else
        fillWithPermutation(arrCp, n);

      std::copy(arrCp, arrCp + n, arrForTest);

    Stats *s = new Stats;
    s->print=true;

    if(s->print)displayArray(arrForTest, n);
    printf("\n");
    printf("Randomized_Select:\n");
    searched = randomized_select(s, arrForTest, 0, n-1,k);
    if(s->print)displayArrayWithHighlight(arrForTest, n, s->index);
    printf("Searched %dth elem: %d\n\n", k, searched);
    printf("Random: %d compares, %d shifts\n\n", s->cmp_count, s->shift_count);

    std::copy(arrCp, arrCp + n, arrForTest);
    if(s->print)displayArray(arrForTest, n);
    printf("\n");
    s->cmp_count = 0;
    s->shift_count = 0;
    printf("Median_Select:\n");
    searched = median_select(s, arrForTest, 0, n-1, k, 5);
    if(s->print)displayArrayWithHighlight(arrForTest, n, s->index);
    printf("Searched %dth elem: %d\n\n", k, searched);
    printf("Median: %d compares, %d shifts\n\n", s->cmp_count, s->shift_count);
    

}