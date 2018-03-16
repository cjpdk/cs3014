//compile with the following command
//gcc -o quicksort quicksort.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int* quicksort(int* array, int size);

void printArray(int* array, int size);

int main(void) {
	
	clock_t programStart = clock();	
	
	//read numbers from an external file into an array
	FILE* numbers;
	int size = 100000;
	int* array = malloc(size*sizeof(int));
	numbers = fopen("100000n.txt", "r");
	for (int i=0; i<size; ++i)
	{
		fscanf(numbers, "%d", &array[i]);
	}
	fclose(numbers);
	clock_t numbersRead = clock();
	
	//quicksort function is called for the first time
	//all other calls are recursively decended from this call
	quicksort(array, size);
	clock_t numbersSorted = clock();
	
	printArray(array, size);
    clock_t programEnd = clock();
	
    double timeToRead = (double)(numbersRead - programStart) / CLOCKS_PER_SEC;
    double timeToSort = (double)(numbersSorted - programStart) / CLOCKS_PER_SEC;
    double timeToPrint = (double)(programEnd - programStart) / CLOCKS_PER_SEC;
	printf("\nNumbers read in %d\n", timeToRead);
	printf("Numbers sorted in %d\n", timeToSort);
	printf("Numbers printed in %d\n", timeToPrint);
}

int* quicksort(int* array, int size) {
	
	//an array with with 0 or 1 elements is always sorted
	//therefore this function does nothing if size is less than 2
	if (size > 1)
	{
		bool* isLessThan = malloc(size*sizeof(bool));
		int lsize = 0;
		int msize = 0;
		int li = 0;
		int mi = 0;
		
		int pivot = array[0];
		
		for (int i=1; i<size; i++)
		{
			if (array[i] < pivot)
			{
				isLessThan[i] = true;
				lsize++;
			}
			else
			{
				isLessThan[i] = false;
				msize++;
			}
		}
		
		int* lessThanPivot = malloc(lsize*sizeof(int));
		int* moreThanPivot = malloc(msize*sizeof(int));
		
		for (int i=1; i<size; i++)
		{
			if (isLessThan[i])
			{
				lessThanPivot[li] = array[i];
				li++;
			}
			else
			{
				moreThanPivot[mi] = array[i];
				mi++;
			}
		}
		
		//we free arrays as quickly as possible
		//because of the space complexity
		free(isLessThan);
		quicksort(lessThanPivot, li);
		quicksort(moreThanPivot, mi);
		
		for (int ai=0; ai<li; ai++)
		{
			array[ai] = lessThanPivot[ai];
		}
		free(lessThanPivot);
		
		array[li] = pivot;
		int midpoint = li+1;
		
		for (int ai=0; ai<mi; ai++)
		{
			array[midpoint+ai] = moreThanPivot[ai];
		}
		free(moreThanPivot);
	}
}

void printArray(int* array, int size) {
	
	for (int i=0; i<size; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}