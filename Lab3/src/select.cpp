
#include "functions.hpp"

int median_partition(Stats *s, int arr[], int l, int r, int x);
void insertion_sort(Stats *s, int arr[], int n);

int findMedian(Stats *s, int arr[], int n)
{
	insertion_sort(s, arr, n); // Sort the array
	return arr[n/2]; // Return middle element
}

// Returns k'th smallest element in arr[l..r] 
int median_select(Stats *s, int arr[], int l, int r, int k, int group_size)
{
	// If k is smaller than number of elements in array
	if (k > 0 && k <= r - l + 1)
	{
		int n = r-l+1; // Number of elements in arr[l..r]

		// Divide arr[] in groups of size group, calculate median
		// of every group and store it in median[] array.
		int i, median[(n+group_size-1)/group_size]; // There will be floor((n+ group_size-1)/ group_size) groups;
		for (i=0; i<n/group_size; i++)
			median[i] = findMedian(s, arr+l+i*group_size, group_size);
		if (i*group_size < n) //For last group with less than group_size elements
		{
			median[i] = findMedian(s, arr+l+i*group_size, n%group_size);
			i++;
		}	

		// Find median of all medians using recursive call.
		// If median[] has only one element, then no need
		// of recursive call
		int medOfMed = (i == 1)? median[i-1]:
								median_select(s, median, 0, i-1, i/2, group_size);
        if(s->print) std::cerr << "MedianOfMedian: " <<medOfMed<< std::endl;
		// Partition the array around a median element and
		// get position of pivot element in sorted array
		int pos = median_partition(s, arr, l, r, medOfMed);

		// If position is same as k
		if (pos-l == k-1){
            s->index=pos;
            return arr[pos];
        }
		if (pos-l > k-1) // If position is more, recur for left
			return median_select(s, arr, l, pos-1, k, group_size);

		// Else recur for right subarray
		return median_select(s, arr, pos+1, r, k-pos+l-1, group_size);
	}

	// If k is more than number of elements in array
	return INT_MAX;
}


// It searches for x in arr[l..r], and partitions the array
// around x.
int median_partition(Stats *s, int arr[], int l, int r, int x)
{
	// Search for x in arr[l..r] and move it to end bcs it is lomuto partition
	int i;
	for (i=l; i<r; i++){
        if(s->print) std::cerr << "Comp: " << arr[i] << " = " << x << std::endl;
        s->cmp_count++;
        if (arr[i] == x)
		    break;
    }

	if(s->print) std::cerr << "Swap: " << arr[i] << " <-> " << arr[r] << std::endl;
    s->shift_count++;
	std::swap(arr[i], arr[r]);

	// Standard partition algorithm
	i = l;
	for (int j = l; j <= r - 1; j++)
	{   
        if(s->print) std::cerr << "Comp: " << arr[j] << " = " << x << std::endl;
        s->cmp_count++;
		if (arr[j] <= x)
		{   
            if(s->print) std::cerr << "Swap: " << arr[i] << " <-> " << arr[j] << std::endl;
            s->shift_count++;
			std::swap(arr[i], arr[j]);
			i++;
		}
	}
    if(s->print) std::cerr << "Swap: " << arr[i] << " <-> " << arr[r] << std::endl;
    s->shift_count++;
	std::swap(arr[i], arr[r]);
	return i;
}

/* Function to sort an array using insertion sort*/
void insertion_sort(Stats *s, int arr[], int n)
{
    int i, key, j;
    bool firstTime;
    for (i = 1; i < n; i++)
    {
        firstTime = true;
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        if(s->print) std::cerr << "Comp: " << arr[j] << " = " << arr[j] << std::endl;
        s->cmp_count++;
        while (j >= 0 && arr[j] > key)
        {   
            if(!firstTime){
                if(s->print) std::cerr << "Swap: " << arr[j+1] << " <-> " << arr[j] << std::endl;
                s->shift_count++;
            }
            arr[j + 1] = arr[j];
            j = j - 1;
            firstTime = false;
        }
        arr[j + 1] = key;
    }
}
