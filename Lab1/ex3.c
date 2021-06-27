#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


typedef struct ElementOfList {
    int value;
    struct  ElementOfList *next;
    struct  ElementOfList *prev;
}ListElement;

//this structure is becease i wanted to have size and avoid messing up with double pointers
typedef struct List {
    int size;
    ListElement *head;
}List;

List* createList();
void addToList (List* list, int value);
void showAll (List* list);
int* findByIndex (List* list, int index);
bool ifExists (List* list, int value);
bool removeByIndex (List* list, int index);
List* merge (List* list1, List* list2);
int iterationsFindByIndex (List* list, int index);
int main(){
    //Testing functionality
    
    List* list = createList();
    addToList(list, 4);
    addToList(list, 5);
    addToList(list, 6);
    addToList(list, 7);
    printf("Not found, pointer is null?: %d\n", findByIndex(list, 7)==NULL);
    printf("%d\n", *findByIndex(list, 2));
    printf("If value '5' exists?: %d\n", ifExists(list,5));
    removeByIndex(list, 2);
    //showAll(list);
    List* list2 = createList();
    addToList(list2, 8);
    addToList(list2, 9);
    List* merged = merge(list, list2);
    showAll(list);
    printf("\n");
    showAll(list2);
    printf("\n");
    showAll(merged);
    
    //----------------Measures-------------------------------

    List* test = createList();
    //Adding random values to the list.
    int germ; //zarodek
    int n = 1000; //amount of elements added to the list
    time_t tt;
    germ = time(&tt);
    srand(germ);
    int tmp; 
    for(int i = 1; i <= n; i++) { 
        tmp = 1 + (int)(rand() / (RAND_MAX + 1.0) * 2137);
        addToList(test,tmp);
    }
    //showAll(test);
    
   
    double executionTime;
    clock_t startTime;
    clock_t endTime;
    printf("Clock test\n------------------------------------------\n");
    //Testing the same element everytime with random index.
    int index = rand() % n+1;
    

    int numbOfTests = 500000;

    //Starting the measurement of time.
    startTime = clock();
    for (int i = 0; i < numbOfTests; i++) {
        //Testing the same element numbOfTests times.
        findByIndex(test,index);
    }
    endTime = clock();
   
    executionTime = (double) (endTime - startTime) / (CLOCKS_PER_SEC * numbOfTests);
    printf ("Checking element on %d index everytime takes an average of %0.15f in %d attempts.\n", index, executionTime, numbOfTests);

    //Random elements part

    
    int* randomIndex = malloc (numbOfTests * sizeof (int));
    
    for (int i = 0; i < numbOfTests; i++) {
        randomIndex[i] = (int)(rand() / (RAND_MAX + 1.0) * n);
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
    
    
    printf("---------------------------------------\nIterations part\n-----------------------------------------------\n");
    int sum = 0;
    for (int i = 0; i < numbOfTests; i++) {
        //Testing the same element numbOfTests times.
        sum=sum+iterationsFindByIndex(test, index);
    }
    printf("Random element, index: %d, everytime, average : %d iterations\n", index, (int)(sum/numbOfTests));
    sum=0;
    for (int i = 0; i < numbOfTests; i++) {
        //Testing numbOfTests random elements.
        sum=sum+iterationsFindByIndex (test, randomIndex[i]);
    }
    printf("Random index everytime: average : %d iterations\n", (int)(sum/numbOfTests));

    free (randomIndex);
    return 0;
}


List* createList () {
    List* list = malloc (sizeof (List));
    list -> head = NULL;
    list -> size = 0;
    return list;
}


void addToList (List* list, int value) {
    if (list->size == 0) {
        ListElement* element = malloc (sizeof (ListElement));
        element -> value = value;
        element -> next = element;
        element -> prev = element;
        list -> head = element;
        list -> size = 1;
        return;
    }
    ListElement* element = malloc (sizeof (ListElement));
    element -> value = value;
    element -> prev = list -> head -> prev; //element before head is last element
    element -> next = list -> head;
    
    list -> head -> prev -> next = element; //field: pointer "next" of "head -> prev" is new element
    list -> head -> prev = element;
   
    list -> size++;
}

void showAll (List* list) {
    if (list->size == 0) {
        printf ("List is empty\n");
        return;
    }
    ListElement* tmp = list -> head;

    for (int i = 0; i < list -> size; i++) {
        printf ("%d. %d\n", i, tmp -> value);
        tmp = tmp -> next;
    }
    
}
int* findByIndex (List* list, int index) {
    
    if (index >= list -> size) {
        return NULL;
    }

    ListElement* tmp = list -> head;
    int* result = malloc(sizeof(int));
    //When index is in "first part" of list we search from 0 to given value of index.
    if (index < list -> size / 2) {
        for (int i = 1; i <= index; i++) {
            tmp = tmp -> next;
        }
    } else {
        //Otherwise we are decrementing from biggest to given index
        int start = list -> size - 1; //bc index is starting with 0

        for (int i = start; i >= index; i--) {
            tmp = tmp -> prev;
        }
    }
    *result = tmp->value; 
    //Returning pointer to variable containing value of searched element.
    return result;
}

bool ifExists (List* list, int value) {
   
    ListElement* tmp = list -> head;

    for (int i = 0; i < list -> size; i++) {
        if (tmp -> value ==  value) return true;
        tmp = tmp -> next;
    }
    return false;
}

bool removeByIndex (List* list, int index) {
    
    if (index >= list -> size) {
        return false;
    }

    ListElement* tmp = list -> head;;

    //When index is first element on the list
    if (index == 0) {
        tmp -> next -> prev = tmp -> prev;  //pointer "prev" in element after head is set to last element (head->prev)
        tmp -> prev -> next = tmp -> next; //pointer "next" in last element (head->prev) is set to head->nex
        list -> head = tmp -> next;   //head is moved to next element
        free (tmp);
        list -> size--;
        return true;
    }

    //choosing "proper parts" of list 
    if (index < list -> size / 2) {
        for (int i = 1; i <= index; i++) {
            tmp = tmp -> next;
        }
    } else {
       
        int start = list -> size - 1;

        for (int i = start; i >= index; i--) {
            tmp = tmp -> prev;
        }
    }

    //changing pointer on next and prev elements.
    tmp -> next -> prev = tmp -> prev;
    tmp -> prev -> next = tmp -> next;
    //Decrementing size of list.
    list -> size--;
    free (tmp);
    return true;
}

List* merge (List* list1, List* list2) {
    List* merged = createList ();
    // ListElement* prev;
    //I will add elements from list provided as arguments to new list
    
    ListElement* tmp = list1 -> head;
    for (int i = 0; i < list1 -> size; i++) {
        addToList (merged, tmp -> value);
       // prev = tmp;
        tmp = tmp -> next;
       // free(prev);
        
    }
    /*
    for(int i = 0; list1->size; i++){
        removeByIndex(list1,i);
    }
    */
    tmp = list2 -> head;
    for (int i = 0; i < list2 -> size; i++) {
        addToList (merged, tmp -> value);
        //prev = tmp;
        tmp = tmp -> next;
        //free(prev);
    }
    /* very slow
    for(int i = 0; list2->size; i++){
        removeByIndex(list2,i);
    }
    */
    //Returning merged list.
    return merged;
}

int iterationsFindByIndex (List* list, int index) {
    
    int counter = 0;
    if (index >= list -> size) {
        return 0;
    }

    ListElement* tmp = list -> head;
    int* result = malloc(sizeof(int));
    //When index is in "first part" of list we search from 0 to given value of index.
    if (index < list -> size / 2) {
        for (int i = 1; i <= index; i++) {
            tmp = tmp -> next;
        }
        return index;
    } else {
        //Otherwise we are decrementing from biggest to given index
        int start = list -> size - 1; //bc index is starting with 0

        for (int i = start; i >= index; i--) {
            tmp = tmp -> prev;
        }
        return start-index+1;
    }
   
}
