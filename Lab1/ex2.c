#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


typedef struct ElementOfList {
    int value;
    struct  ElementOfList *next;
}ListElement;



void showAll(ListElement *list);
int* findByIndex(ListElement *list, u_int32_t index);
void removeByIndex(ListElement **list, u_int32_t index);
void addAfterIndex(ListElement *list, u_int32_t index, int value);
void addToList(ListElement **list, int value);
bool ifExists(ListElement *list, int value);
//void merge(ListElement **list1, ListElement **list2);
ListElement* merge (ListElement* list1, ListElement* list2);
int main(){
    /*
    //testing
    ListElement *list = (ListElement*)malloc(sizeof(ListElement));
    list->next = NULL;
    list->value = 10;
    addAfterIndex(list, 0, 14);
    addAfterIndex(list, 1, 16);
    removeByIndex(&list,0);
    showAll(list);
    if(findByIndex(list, 5) == NULL) printf("not found\n");
    int *value = findByIndex(list, 1);
    if(value != NULL) printf("Found %d at index 1\n",*value);
    */
    ListElement *list1 = NULL;
    addToList(&list1, 4);
    addToList(&list1, 5);
    addToList(&list1, 6);
    showAll(list1);

    ListElement *list2 = NULL;
    addToList(&list2, 7);
    addToList(&list2, 8);
    showAll(list2);
    ListElement *merged = merge(list1, list2); //merging into new list
    showAll(merged);
    printf("check: 5 %d\n", ifExists(merged,5));
    
    // Time measeurement 
    
    ListElement* test = NULL;
    //test->next=NULL;
    //test->value = 4;
    //Adding random values to the list.
    int germ; //zarodek
    int n = 1000; //amount of elements added to the list
    time_t tt;
    germ = time(&tt);
    srand(germ);
    int tmp; 
    for(int i = 1; i <= n; i++) { 
        tmp = 1 + (int)(rand() / (RAND_MAX + 1.0) * 2137);
        addToList(&test,tmp);
    }
    showAll(test);
    
   
    double executionTime;
    clock_t startTime;
    clock_t endTime;

    //Testing the same element everytime with random index.
    int index = rand() % n+1;
    
    //Number of tests.
    int numbOfTests = 20000;

    //Starting the measurement of time.
    startTime = clock();
    for (int i = 0; i < numbOfTests; i++) {
        //Testing the same element numbOfTests times.
        findByIndex(test,index);
    }
    endTime = clock();

    //number of iterations necessary to find element on a list is just value of the index
   
    executionTime = (double) (endTime - startTime) / (CLOCKS_PER_SEC * numbOfTests);
    printf ("Checking element on %d index everytime takes an average of %0.15f in %d attempts.\n", index, executionTime, numbOfTests);

    //Random elements part

    
    int* randomIndex = malloc (numbOfTests * sizeof (int));
    int sum = 0;
    for (int i = 0; i < numbOfTests; i++) {
        randomIndex[i] = (int)(rand() / (RAND_MAX + 1.0) * n);
        sum=sum+randomIndex[i];
    }

    //Starting measuring time.
    startTime = clock();
    for (int i = 0; i < numbOfTests; i++) {
        //Testing numbOfTests random elements.
        findByIndex (test, randomIndex[i]);
    }
    endTime = clock();

    //Calculating execution time fore single function call
    executionTime = (double) (endTime - startTime) / (CLOCKS_PER_SEC * numbOfTests);
    printf ("Checking random elements takes an average of %0.15f.\n", executionTime);
    printf("Checking random, counting time as checked elements: %0.2f\n", (float)(sum/numbOfTests)); //just expected value
    free (randomIndex);
    return 0;

    
}


void addAfterIndex(ListElement *list, u_int32_t index, int value) {
    u_int32_t counter = -1;  //head of list is counted as 0's element
    ListElement *tmpList = list;
    ListElement *prev = list;
    bool indexFound = 0;
    while(tmpList != NULL){
        counter++;
        if(counter == index){
            ListElement *tmpElem = (ListElement*)malloc(sizeof(ListElement));
            tmpElem->value = value;
            ListElement *tmpNext = tmpList->next;
            tmpList->next = tmpElem;
            tmpElem->next = tmpNext;
            indexFound = true;
        }
        tmpList = tmpList->next;
    }
    if(!indexFound) printf("No such index\n");
}

void showAll(ListElement *list) {
    if(list == NULL) printf("List is empty\n");
    else{
        int i=-1;
        ListElement *tmp;
        int counter = 0;
        tmp = list;
        while(tmp != NULL) {
            printf("%d. %d\n", ++i, tmp->value);
            tmp = tmp->next; 
            counter++;
        }
        printf("Counter int showAll-> while is : %d\n", counter);
        
    }
    
}

int* findByIndex(ListElement *list, u_int32_t index){

    if(list == NULL)  printf("List is empty\n");
    else{
        ListElement *tmp;
        int counter = 0;
        tmp = list;
        int *tmpValue = malloc(sizeof(int));
        while(tmp != NULL) {
            if(counter == index) {
                *tmpValue = tmp->value;
                return tmpValue;
            } 
            tmp = tmp->next; 
            counter++;
        }   
    }
    return NULL;  //if index is bigger or list is empty return null, must be handled later
    
}

void removeByIndex(ListElement **list, u_int32_t index){

    ListElement* tmp;
    ListElement* tmpNext;
    tmp = *list;
    if(index == 0){
        *list = (*list)->next;
        free(tmp);
    }
    else{
        int counter = 0; 
        while(tmp != NULL) {
            if(counter+1 == index) break;
            tmp = tmp->next;
            counter++;
        }
        if(tmp == NULL) printf("No such index");
        else if(tmp->next->next == NULL){ //deleting at the end
            tmpNext = tmp->next;
            tmp->next=NULL;
            free(tmpNext);
        }
        else{
            tmpNext = tmp->next;
            tmp->next = tmpNext->next;
            free(tmpNext);
        }


    }

}

void addToList(ListElement **list, int value) {

    ListElement *tmpList = *list;
    ListElement *tmpPrev = *list;
    if(*list == NULL){
       ListElement *tmpElem = (ListElement*)malloc(sizeof(ListElement));
       tmpElem->value = value;
       tmpElem->next = NULL;
       *list = tmpElem;
    }
    else { 
        while(tmpList != NULL){
            tmpPrev = tmpList;
            tmpList = tmpList->next;
        }
        ListElement *tmpElem = (ListElement*)malloc(sizeof(ListElement));
        tmpElem->value = value;
        tmpElem->next = NULL;
        tmpPrev->next = tmpElem;
    }
}

/*void merge(ListElement **list1, ListElement **list2){
    ListElement *tmp = *list1;
    ListElement *tmpPrev = *list1; 
    while(tmp != NULL){
        tmpPrev = tmp;
        tmp=tmp->next;
    }
    tmpPrev->next = *list2;
}
*/

ListElement* merge (ListElement* list1, ListElement* list2) {
    ListElement* merged = NULL;
    ListElement* tmp = list1;
    ListElement* tmpRemove = list1;
    //Adding elements from first list to new lists.
    while (tmp != NULL) {
        addToList (&merged, tmp -> value);
        tmpRemove = tmp;
        tmp = tmp -> next;
        //free(tmpRemove);
    }

    tmp = list2;

    //Adding elements from second list to new lists.
    while (tmp != NULL) {
        addToList (&merged, tmp -> value);
        tmpRemove = tmp;
        tmp = tmp -> next;
        //free(tmpRemove);
    }

    return merged;
}
bool ifExists(ListElement *list, int value){
    if(list == NULL) return false;
    else{
        ListElement *tmp = list;
        while(tmp != NULL){
            if(tmp->value == value) return true;
            tmp=tmp->next;
        }
    }
}