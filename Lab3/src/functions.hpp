#ifndef _functions

#define _functions
#include <string>
#include <cstring>
#include <iostream>
#include <random>
#include <ctime>
#include <climits>


typedef struct Stats {
  int cmp_count = 0;
  int shift_count = 0;
  bool print = false;
  int index = 0;
} Stats;



int randomized_select(Stats *s,int arr[], int l, int r, int k);
int median_partition(Stats *s, int arr[], int l, int r, int x);
int median_select(Stats *s, int arr[], int l, int r, int k, int GROUP_SIZE);


int getRand(const int& A, const int& B);
void fillWithRandom(int *arr, int n);
void fillWithPermutation(int *arr, int n);

bool isSorted(int arr[], int length);

void displayArrayWithHighlight(int *arr, int n, int idxForHighlight);
void displayArray(int *arr, int n);

void ex1_from_input(char arrType, int n, int k);
void ex1_to_csv();
void ex2_to_csv();
void ex3_to_csv();
void ex4_to_csv();

double calculateSD(int data[], double mean);
double calculateSDT(clock_t data[], clock_t mean);

void quick_sort(Stats *s, int arr[], int l, int r);
void quick_sort_dp(Stats *s, int arr[], int left, int right);

void quick_sort_with_median(Stats *s, int arr[], int l, int h);
void quick_sort_dp_with_median(Stats *s, int arr[], int left, int right);

#endif