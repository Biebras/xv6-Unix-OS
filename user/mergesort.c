#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

///
// l - left index of arr
// m - middle index of arr
// r - right index of arr
///
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) 
	{
        if (L[i] <= R[j]) 
		{
            arr[k] = L[i];
            i++;
        }
        else 
		{
            arr[k] = R[j];
            j++;
        }

        k++;
    }
 
    //Copy the remaining elements of L[], if there are any
    while (i < n1) 
	{
        arr[k] = L[i];
        i++;
        k++;
    }
 
    //Copy the remaining elements of R[], if there are any
    while (j < n2) 
	{
        arr[k] = R[j];
        j++;
        k++;
    }
}

///
// arr - arr to be sorted
// l - left index of arr
// r - right index of arr
///
void mergeSort(int arr[], int l, int r)
{
	if (l < r) 
	{
        // Same as (l+r)/2, but avoids overflow for
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
		
		//Merge arrays
        merge(arr, l, m, r);
    }
}

void printArray(int A[], int size)
{
	for(int i = 0; i < size; i++)
		printf("%d ", A[i]);

	printf("\n");
}

int main(int argc, char *argv[])
{
	//There should be atleast two integers to sort
	if(argc <= 2)
	{
		printf("Mergesort: there should be atleast 2 integers to sort\n");
		exit(-1);
	}

	//return error, if there are more than 8 numbers to sort.
	//we check if 9, because command name is included in argv
	if(argc > 9)
	{
		printf("Mergesort: max 8 integers\n");
		exit(-1);	
	}

	int arr[argc - 1];

	//convert from char to int
	for(int i = 1; i < argc; i++)
	{
		int number = atoi(argv[i]);
		arr[i - 1] = number;
	}
	
	//Sort array
	mergeSort(arr, 0, argc - 2);

	//Print array
	printArray(arr, argc-1);

	exit(0);
}
