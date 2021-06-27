#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct element {
  int value;       
  struct element *ptr;     
};
struct element *stack;

void build() { 
    stack = NULL;
}

int stackIsEmpty(){
    return stack == NULL;
}

void push(int x){
    struct element *tmp;
    tmp = malloc(sizeof(struct element));
    tmp->value = x;
    tmp->ptr = stack;
    stack = tmp;
}

int* pop(){

    if(stackIsEmpty()) return NULL;
    else{
        struct element *tmp;
        tmp = stack;
        int *retValue;
        retValue= malloc(sizeof(int));
        *retValue = stack->value;
        stack=stack->ptr;
        free(tmp);
        
        return retValue; //pamiętajmy o tym żeby potem zwolnić tą pamięć po wywołaniu funkcji
    }


}

void showAll(){
    int i=1;
    int *tmp;
    int counter = 0;
    tmp = pop();
    while(tmp != NULL){
        printf("%d. %d\n", i++, *tmp);
        free(tmp);
        tmp = pop();
        counter++;
    }
    printf("Counter int showAll-> while is : %d\n", counter);
    free(tmp);
}

int main(){

    build();
    int germ; //zarodek
    time_t tt;
    germ = time(&tt);
    srand(germ);
    int tmp; 
    for(int i = 1; i <= 100; i++) { 
        tmp = (int)(rand() / (RAND_MAX + 1.0) * 101.0);
        printf("%d. %d\n", i, tmp);
        push(tmp);
    }
    printf("\n");
    showAll();
    

    return 0;
}