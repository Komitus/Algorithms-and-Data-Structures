#include "functions.hpp"

void quick_sort_with_median(Stats *s, int arr[], int l, int r)
{
    if (l < r)
    {
        // Find size of current subarray
        int n = r-l+1;
        // Find median of arr[].
        int med = median_select(s, arr, l, r, n/2, 5);
        // Partition the array around median
        int p = median_partition(s, arr, l, r, med);
        // Recur for left and right of partition
        quick_sort_with_median(s, arr, l, p - 1);
        quick_sort_with_median(s, arr, p + 1, r);
    }
}


void quick_sort_dp_with_median(Stats *s, int arr[], int left, int right){

    int p,q;
    int i, j,k,d;
    
    if(right <= left)
        return;

    int bound = left+(right-left)/2;
    int pos1 = (bound-left+1)/2;
    int pos2 = (right-(bound+1)+1)/2;

    if(pos1 > 0 && pos2 > 0){
    int medLeft = median_select(s, arr, left, bound, pos1 , 5);
    int medRight = median_select(s, arr, bound+1, right, pos2, 5);

    if (medLeft == INT_MAX || medRight == INT_MAX)
    {
        std::cerr << "NOT MEDIAN FOUND ERROR" << std::endl;
        return;
    }

    int iter;
    int founded = 0;
    for (iter = left; iter < right; iter++)
    {

        s->cmp_count++;
        if (arr[iter] == medLeft)
        {
            founded++;
            std::swap(arr[iter], arr[left]);
        }

        s->cmp_count++;
        if (arr[iter] == medRight)
        {
            std::swap(arr[iter], arr[right]);
            founded++;
        }

        if (founded > 2)
            break;
    }
    }
    s->cmp_count++;
    if (arr[right] < arr[left])
    {
        s->shift_count++;
        std::swap(arr[right], arr[left]);
    }

    p=arr[left];
    q=arr[right];

    i=left+1;
    k=right-1;
    j=i;
    d=0;   //difference between numb of smaller elements (si-1) than p
    //and larger (li-1) than q
    //or larger and smaller (in case of input >=)
    while(j<=k){
        if(d>=0){
            s->cmp_count++;
            //we had more smaller elems than larger or std::swap this sentence before xd
            if((arr[j] < p)){  
                s->shift_count++;
                std::swap(arr[i], arr[j]);
                i++; j++; d++;    
            }
            else{
                //it is in right position, we can go to next  
                s->cmp_count++;
                if(arr[j] < q){
                    j++;
                }
                //we have found element greater than q it must go at right
                else{    
                    s->shift_count++;
                    std::swap(arr[j], arr[k]);
                    k--; d--;
                }
            }
        }
        else{
            s->cmp_count++;
            if(q < arr[k]){
                k--; d--;
            }
            else{
                   
                s->cmp_count++;
                if(arr[k] < p){
                    std::swap(arr[k],arr[j]);
                    std::swap(arr[j],arr[i]);
                    i++; d++;
                        s->shift_count+=2;
                }
                else{
                    s->shift_count++;
                    std::swap(arr[j],arr[k]);
                }
                j++;
            }
        } 
    }
    std::swap(arr[left], arr[i-1]);    //assigning value of p to arr[i-1]
    std::swap(arr[right], arr[k+1]);
    quick_sort_dp_with_median(s, arr, left, i-2);
    quick_sort_dp_with_median(s, arr, i, k);
    quick_sort_dp_with_median(s, arr, k+2, right);
}