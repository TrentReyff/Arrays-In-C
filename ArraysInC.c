/*
Title: Assignment 3
Author: Trent Reyff   Date: 10/16/19
Description: Practice with dynamic allocation of arrays
*/
#include <stdio.h>
#include <time.h>
#include<stdlib.h>

int* generateArray(int*, int, int, int);
void manualArray(int*, int*, int, int);
int* sortArray(int*, int);
void arrayAnalysis(int*, int*, int, int);
int disjoint(int*, int*, int, int);
int* intersection(int*, int*, int, int);
int* uniqueNums(int*, int*, int, int);
int* leftDiff(int*, int*, int, int);
int* symDiff(int*, int*, int, int);
void outputArr(int*, int);
int sharedIntsCount(int*, int*, int, int);
int duplicateCount(int*, int);
int intsInOtherArr(int*, int*, int, int);

int main()
{
	srand(time(0)); // used for random number generation

	int num = -1;
	int size1 = 0;
	int size2 = 0;
	int* arr1;
	int* arr2;
	int minimum;
	int maximum;

	printf("Welcome to the Set Analyzer!\n");

	while (num != 0) // will continue looping unless 0 is given to end the program
	{
		printf("1 %c Manual Input\n", '-');
		printf("2 %c Random Generation\n0 %c Exit\n", '-', '-');
		scanf("%d", &num);

		if (num == 1 || num == 2)
		{
			if (num == 1)
			{
				printf("You have chosen Manual Input\nEnter Array Size 1: ");
				scanf("%d", &size1);
				arr1 = (int*)malloc(size1 * sizeof(int));
				printf("Enter Array Size 2: ");
				scanf("%d", &size2);
				arr2 = (int*)malloc(size2 * sizeof(int));
				manualArray(arr1, arr2, size1, size2);
			}
			else
			{
				printf("You have chosen Random Generation\nEnter Array Size 1: ");
				scanf("%d", &size1);
				arr1 = (int*)malloc(size1 * sizeof(int));
				printf("Enter Array Size 2: ");
				scanf("%d", &size2);
				arr2 = (int*)malloc(size2 * sizeof(int));
				printf("Enter minimum integer value: ");
				scanf("%d", &minimum);
				printf("Enter maximum integer value: ");
				scanf("%d", &maximum);
				arr1 = generateArray(arr1, size1, minimum, maximum);
				arr2 = generateArray(arr2, size2, minimum, maximum);
			}
			arrayAnalysis(arr1, arr2, size1, size2);
			free(arr1);
			free(arr2);
			printf("\n");
		}
		else if (num == 0)
		{
			printf("Program terminated.");
		}
		else
		{
			printf("Invalid character, try again.\n");
		}
		
	}
	return 0;
}

// generates random numbers for each index of the array based on the minimum and maximum value
int* generateArray(int* arr, int size, int minimum, int maximum)
{
	for (int i = 0; i < size; i++)
	{
		*(arr + i) = (rand() % (maximum - minimum + 1)) + minimum;
	}
	return arr;
}

// loops through the indexes of each array in turn and puts the user input values into each 
void manualArray(int* arr1, int* arr2, int size1, int size2)
{
	int count = 0;
	int num = 0;
	printf("\nNow collecting input for Array #1:\nEnter values for each index:\n");
	while (count < size1)
	{
		printf("%d: ", count);
		scanf("%d", &num);
		*(arr1 + count) = num;
		count++;
	}
	count = 0;
	printf("\nNow collecting input for Array #2:\nEnter values for each index:\n");
	while (count < size2)
	{
		printf("%d: ", count);
		scanf("%d", &num);
		*(arr2 + count) = num;
		count++;
	}
}

// sorts an array using the bubblesort algorithm
int* sortArray(int* arr, int size)
{
	int end = size - 1;
	int temp = 0;
	int last;
	while (end > 0) 
	{
		last = 0;
		for (int i = 0; i < end; i++) 
		{
			if (arr[i] > arr[i + 1]) 
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				last = i;
			}	
		}
		end = last;
	}
	return arr;
}

// performs the analysis comparing two arrays
void arrayAnalysis(int* arr1, int* arr2, int size1, int size2)
{
	sortArray(arr1, size1);
	sortArray(arr2, size2);

	int sharedNumsCount = sharedIntsCount(arr1, arr2, size1, size2);
	int uniqueNumsCount = size1 + size2 - duplicateCount(arr1, size1) - duplicateCount(arr2, size2) - sharedNumsCount;
	int leftDiffCount = size1 - intsInOtherArr(arr1, arr2, size1, size2);
	int symDiffCount = size1 + size2 - intsInOtherArr(arr1, arr2, size1, size2) - intsInOtherArr(arr2, arr1, size2, size1);

	printf("Running set operations!\nDisjoint? ");

	if (disjoint(arr1, arr2, size1, size2) == 1)
	{
		printf("YES\n");
		return;
	}

	printf("NO\nUnion: ");
	outputArr(uniqueNums(arr1, arr2, size1, size2), uniqueNumsCount);
	printf("Intersection: ");
	outputArr(intersection(arr1, arr2, size1, size2), sharedNumsCount);
	printf("Left Difference: ");
	outputArr(leftDiff(arr1, arr2, size1, size2), leftDiffCount);
	printf("Symmetric Difference: ");
	outputArr(symDiff(arr1, arr2, size1, size2), symDiffCount);
}

// returns 0 if arrays are disjointed, otherwise returns 1
int disjoint(int* arr1, int* arr2, int size1, int size2)
{
	int sharedNums = sharedIntsCount(arr1, arr2, size1, size2);
	if (sharedNums == 0)
	{
		return 1;
	}
	return 0;
}

// returns an array of the ints shared by both array
int* intersection(int* arr1, int* arr2, int size1, int size2)
{
	int lastNum = 0;
	int count = 0;
	int sharedNums = sharedIntsCount(arr1, arr2, size1, size2);
	int* intersect = (int*)malloc(sharedNums * sizeof(int));
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			if (arr2[j] == arr1[i] && (arr2[j] != lastNum || count == 0))
			{
			    intersect[count] = arr2[j];
				lastNum = arr2[j];
				count++;
			}
		}
	}
	return intersect;
}

// returns an array containing all of the unique ints between the two arrays
int* uniqueNums(int* arr1, int* arr2, int size1, int size2)
{
	int i = 0;
	int j = 0;
	int lasti = arr1[0];
	int lastj = arr2[0];
	int count = 0;
	int size = size1 + size2 - duplicateCount(arr1, size1) - duplicateCount(arr2, size2) - sharedIntsCount(arr1, arr2, size1, size2);
	int* unionNums = (int*)malloc(size * sizeof(int));
	while (count < size)
	{
		if (i == size1 && j < size2)
		{
			if (arr2[j] != lastj )
			{
				unionNums[count] = arr2[j];
				count++;
			}
			lastj = arr2[j];
			j++;
		}
		else if (j == size2 && i < size1)
		{
			if (arr1[i] != lasti)
			{
				unionNums[count] = arr1[i];
				count++;
			}
			lasti = arr1[i];
			i++;
		}
		else if (arr1[i] < arr2[j])
		{
			if (i == 0 || arr1[i] != lasti)
			{
				unionNums[count] = arr1[i];
				count++;
			}
			lasti = arr1[i];
			i++;
		}
		else if(arr1[i] > arr2[j])
		{
			if (j == 0 || arr2[j] != lastj)
			{
				unionNums[count] = arr2[j];
				count++;
			}
			lastj = arr2[j];
			j++;
		}
		else if(arr2[j] == arr1[i])
		{
			if (count == 0 || ((arr2[j] != lastj || j == 0) && (arr1[i] != lasti || i == 0)))
			{
				unionNums[count] = arr2[j];
					count++;
			}
			lasti = arr1[i];
			i++;
			lastj = arr2[j];
			j++;
		}
		else
		{
			count++;
		}
	}
	return unionNums;
}

// returns an array containing the ints in arr1 that aren't in arr2
int* leftDiff(int* arr1, int* arr2, int size1, int size2)
{
	int isSame = 0;
	int count = 0;
	int size = size1 - intsInOtherArr(arr1, arr2, size1, size2);
	int* diff = (int*)malloc(size * sizeof(int));

	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			if (arr1[i] == arr2[j])
			{
				isSame++;
			}
		}
		if (isSame == 0)
		{
			diff[count] = arr1[i];
			count++;
		}
		isSame = 0;
	}
	return diff;
}

//returns an array containing the ints that are not shared by both arrays
int* symDiff(int* arr1, int* arr2, int size1, int size2)
{
	int i = 0;
	int j = 0;
	int count = 0;
	int leftSize = size1 - intsInOtherArr(arr1, arr2, size1, size2);  //Amount of numbers in arr1 not in arr2
	int rightSize = size2 - intsInOtherArr(arr2, arr1, size2, size1); //Amount of numbers in arr2 not in arr1
	int size = (leftSize + rightSize);
	int* left = leftDiff(arr1, arr2, size1, size2);
	int* right = leftDiff(arr2, arr1, size2, size1);
	int* diff = (int*)malloc(size * sizeof(int));

	while (count < size)
	{
		if (i == leftSize || (right[j] < left[i] && j != rightSize))
		{
			diff[count] = right[j];
			count++;
			j++;
		}
		else
		{
			diff[count] = left[i];
			count++;
			i++;
		}
	}
	free(left);
	free(right);
	return diff;

}

// prints the array
void outputArr(int* arr, int size)
{
	if (size == 0)
	{
		printf("%c%c\n", '[', ']');
	}
	else
	{
		printf("%c", '[');
		for (int i = 0; i < size - 1; i++)
		{
			printf("%d, ", arr[i]);
		}
		printf("%d%c\n", arr[size - 1], ']');
	}
}

// helper method that counts the number of unique ints shared by both array
int sharedIntsCount(int* arr1, int* arr2, int size1, int size2)
{
	int lastNum = 0;
	int count = 0;
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			if (arr2[j] == arr1[i] && (arr2[j] != lastNum || count == 0))
			{
				lastNum = arr2[j];
				count++;
			}
		}
	}

	
	return count;
}

// helper method that returns the number of duplicate ints in an array
int duplicateCount(int* arr, int size)
{
	int count = 0;
	int lastNum = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] == lastNum)
		{
			count++;
		}
		else
		{
			lastNum = arr[i];
		}
	}
	return count;
}

// helper method that returns the number of ints in arr1 that are in arr2
int intsInOtherArr(int* arr1, int* arr2, int size1, int size2)
{
	int count = 0;
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			if (arr1[i] == arr2[j])
			{
				count++;
				break;
			}
		}
	}
	return count;
}