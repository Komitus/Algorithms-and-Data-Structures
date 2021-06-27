#include "functions.hpp"
#include<climits>

int randomPartition(Stats *s, int arr[], int l, int r);

// This function returns k'th smallest element in arr[l..r] using QuickSort 
int randomized_select(Stats *s, int arr[], int l, int r, int k)
{
	// If k is smaller than number of elements in array
	if (k > 0 && k <= r - l + 1)
	{
		// Partition the array around a random element and
		// get position of pivot element in sorted array
		int pos = randomPartition(s, arr, l, r);

		// If position is same as k
		if (pos-l == k-1){
            s->index=pos;
            return arr[pos];
        }
			
		if (pos-l > k-1) // If position is more, recur for left subarray
			return randomized_select(s, arr, l, pos-1, k);

		// Else recur for right subarray
		return randomized_select(s, arr, pos+1, r, k-pos+l-1);
	}

	// If k is more than the number of elements in the array
	return INT_MAX;
}



// Standard partition process of QuickSort(). It considers the last
// element as pivot and moves all smaller element to left of it and
// greater elements to right. This function is used by randomPartition()
int partition(Stats *s,int arr[], int l, int r)
{
	int x = arr[r], i = l;
    if(s->print) std::cerr << "Pivot: "<<x<< std::endl;
	for (int j = l; j <= r - 1; j++)
	{   
        if(s->print) std::cerr << "Comp: " << arr[j] << " = " << x << std::endl;
        s->cmp_count++;
		if (arr[j] <= x)
		{   if(s->print) std::cerr << "Swap: " << arr[i] << " <-> " << arr[j] << std::endl;
            s->shift_count++;
			std::swap(arr[i], arr[j]);
			i++;
		}
	}
    if(s->print) std::cerr << "Swap: " << arr[i] << " <-> " << arr[r] << std::endl;
	std::swap(arr[i], arr[r]);
	return i;
}

// Picks a random pivot element between l and r and partitions
// arr[l..r] around the randomly picked element using partition()
int randomPartition(Stats *s,int arr[], int l, int r)
{
	int n = r-l+1;
	int pivot = rand() % n;
    if(s->print) std::cerr << "Swap: " << arr[l+pivot] << " <-> " << arr[r] << std::endl;
	std::swap(arr[l + pivot], arr[r]);
	return partition(s,arr, l, r);
}
