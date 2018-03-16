#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int* quicksort(int* array, int size);

void printArray(int* array, int size);

int main(void) {
	
	clock_t programStart = clock();	
	
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
	/*
	printf("Unsorted: ");
	printArray(array, size);
	*/
	quicksort(array, size);
	
	clock_t numbersSorted = clock();
	
	printf("Sorted: ");
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
	
	if (size > 1)
	{
		bool* isLessThan = malloc(size*sizeof(bool));
		int lsize = 0;
		int msize = 0;
		int li = 0;
		int mi = 0;
		
		int head = array[0];
		
		for (int i=1; i<size; i++)
		{
			if (array[i] < head)
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
		
		int* lessThanHead = malloc(lsize*sizeof(int));
		int* moreThanHead = malloc(msize*sizeof(int));
		
		for (int i=1; i<size; i++)
		{
			if (isLessThan[i])
			{
				lessThanHead[li] = array[i];
				li++;
			}
			else
			{
				moreThanHead[mi] = array[i];
				mi++;
			}
		}
		
		free(isLessThan);
		/*
		printf("head = %d\nlessThanHead = ", head);
		printArray(lessThanHead, li);
		printf("moreThanHead = ");
		printArray(moreThanHead, mi);
		printf("-\n");*/
		
		quicksort(lessThanHead, li);
		quicksort(moreThanHead, mi);
		
		int ai;
		for (ai=0; ai<li; ai++)
		{
			array[ai] = lessThanHead[ai];
		}
		
		array[ai] = head;
		
		int midpoint = li+1;
		for (ai=0; ai<mi; ai++)
		{
			array[midpoint+ai] = moreThanHead[ai];
		}
		
		free(lessThanHead);
		free(moreThanHead);
	}
}

void printArray(int* array, int size) {
	
	for (int i=0; i<size; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}