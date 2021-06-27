#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct element {
  int value;       
  struct element *ptr;     
};
struct element* queue = NULL;

int queueIsEmpty(){
    return queue == NULL;
}

void addElement(int x){
    struct element *tmp;
    tmp = queue;
    if(queue == NULL){
        struct element *tmpElem;
        tmpElem = malloc(sizeof(struct element));
        tmpElem->value = x;
        tmpElem->ptr = NULL;
        queue = tmpElem;
    }
    else {
        
        while(tmp->ptr != NULL)
            tmp = tmp->ptr;
        struct element *tmpElem;
        tmpElem = malloc(sizeof(struct element));
        tmpElem->value = x;
        tmp->ptr = tmpElem;
        tmpElem->ptr = NULL;
    }
}

int* removeElement() {
    
    if (queueIsEmpty()) {
        printf("%s", "Empty queue\n");
        return NULL;
    }
    else {
        struct element *tmp;    
        int* retValue = malloc(sizeof(int));    
        *retValue = queue->value; 
        tmp = queue;       
        queue = queue->ptr;    
        free(tmp);

        return retValue;   
    }
   
}
void showAll(){
    int i=1;
    int *tmp;
    int counter = 0;
    tmp = removeElement();
    while(tmp != NULL) {
        printf("%d. %d\n", i++, *tmp);
        free(tmp);
        tmp = removeElement(); 
        counter++;
    }
    printf("Counter int showAll-> while is : %d\n", counter);
    free(tmp);
}
int main(){

    struct element* queue = NULL;
    
    int germ; //zarodek
    time_t tt;
    germ = time(&tt);
    srand(germ);
    int tmp; 
    for(int i = 1; i <= 100; i++) { 
        tmp = (int)(rand() / (RAND_MAX + 1.0) * 101.0);
        printf("%d. %d\n", i, tmp);
        addElement(tmp);
    }
    printf("\n");
    showAll(queue);
    


    return 0;
}