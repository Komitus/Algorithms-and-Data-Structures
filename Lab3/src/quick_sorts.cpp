#include "functions.hpp"


int LomutoPartition (Stats *s, int arr[], int l, int r)
{
    int pivot = arr[r]; 
    int i = (l - 1);
 
    for (int j = l; j <= r - 1; j++)
    {
        s->cmp_count++;
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            s->shift_count++;
            std::swap(arr[i], arr[j]);
        }
    }
    s->shift_count++;
    std::swap(arr[i + 1], arr[r]);
    return (i + 1);
}
 
void quick_sort(Stats *s, int arr[], int l, int r)
{
    if (l < r)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = LomutoPartition(s, arr, l, r);
 
        // Separately sort elements before
        // partition and after partition
        quick_sort(s, arr, l, pi - 1);
        quick_sort(s, arr, pi + 1, r);
    }
}


void quick_sort_dp(Stats *s, int arr[], int left, int right){

    int p,q;
    int i, j,k,d;
 
    
    if(right <= left)
        return;
    
    s->cmp_count++;
    if(arr[right] < arr[left]){
        
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
    quick_sort_dp(s, arr, left, i-2);
    quick_sort_dp(s, arr, i, k);
    quick_sort_dp(s, arr, k+2, right);
}