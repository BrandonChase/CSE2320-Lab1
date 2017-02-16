/*
	Lab 1
	Brandon Chase
	ID: 1001132518

	Description: This program creates two dynamically allocated arrays from user input, A and X, and calculates
	the maximum interleave factor of X such that X is a subsequence of A. Outputted is the trace of the successes and 
	failures of the binary search loop as well as the max interleave factor.

	Compile Command: gcc lab1.c -o lab1.out
*/

#include <stdlib.h>
#include <stdio.h>

void populateArrayWithStdin(int* arr, int arr_len);
int isSubsequence(int* x, int x_len, int* a, int a_len, int interleave_factor);
int calculateMaxInterleaveFactor(int* x, int x_len, int* a, int a_len);

int main(int argc, char *argv[])
{
	int *a, *x, a_len, x_len;

	scanf("%d", &a_len);
	scanf("%d", &x_len);

	a = (int*)calloc(a_len, sizeof(int));
	x = (int*)calloc(x_len, sizeof(int));

	populateArrayWithStdin(a, a_len);
	populateArrayWithStdin(x, x_len);
	
	printf("Maximum repeats is %d\n", calculateMaxInterleaveFactor(x, x_len, a, a_len));

	//replacement for getchar() because there are numerous \n in stdin buffer and getchar() would be skipped
	int temp;
	scanf("%d", &temp); 

	return 0;
}

/*
	@desc Populates an array with a specified number of ints from stdin 
	@param int* arr - pointer to the first element of the array
	@param int arr_len - size of the array
*/
void populateArrayWithStdin(int* arr, int arr_len)
{
	int i;
	for (i = 0; i < arr_len; ++i)
	{
		scanf("%d", &arr[i]);
	}

	int temp;
	scanf("%d", &temp); //ignore -999999999 that separates array data
}

/*
	@desc Determines whether or not the interleaved sequence that results from applying the given interleave factor to 
	array X is a subsequence of array A
	@param int* x - pointer to first element of array X
	@param x_len - size of array X
	@param int* a - pointer to the first element of array A 
	@param int a_len - size of the array A
	@param int interleave_factor - the interleave factor that is applied to array X
	@return (bool)int - is X^(interleave factor) a subsequence of A or not 
*/
int isSubsequence(int* x, int x_len, int* a, int a_len, int interleave_factor)
{
	int is_subsequence = 0, a_index = 0, x_index = 0;
	int num_of_matches_at_index = 0; 

	while (a_index <= a_len) // while A deck isn't empty
	{
		if (x[x_index] == a[a_index])
		{
			num_of_matches_at_index++;
		}

		/* this logic removes need to create an array of the
		actual interleaved sequence
		Ex: if interleave_factor is 3, there need to be 3 matches at
		one card in X before moving onto the next*/
		if (num_of_matches_at_index == interleave_factor) 
		{
			x_index++; // move to next card in X deck
			num_of_matches_at_index = 0;
		}

		if (x_index == x_len) // if X deck is empty aka 
		{
			is_subsequence = 1;
			break;
		}

		a_index++; // move to next card in A deck
	}
	return is_subsequence;
}

/*
	@desc Calculates the highest interleave factor for X such that X is a subsequence of A
	@param int* x - pointer to first element of array X
	@param x_len - size of array X
	@param int* a - pointer to the first element of array A
	@param int a_len - size of the array A
	@return int - the highest interleave factor for X such that X is a subsequence of A
*/
int calculateMaxInterleaveFactor(int* x, int x_len, int* a, int a_len)
{
	int max_possible_interleave = a_len / x_len; /*  anything higher and X^(i) has more elements than A 
															and can't be its subsequence*/
	int low = 0, high = max_possible_interleave;
	int max_successful_interleave_factor = 0;

	/* Loop that applies a binary search to the possible values of the interleave factor
	   and then tests if the interleaved sequence of X with that factor is a subsequence of A. */
	while (low <= high) 
	{
		int interleave_factor = (low + high) / 2;

		printf("low %d mid %d high %d ", low, interleave_factor, high); //print trace

		int is_subsequence = isSubsequence(x, x_len, a, a_len, interleave_factor);

		if (is_subsequence)
		{
			printf("passed\n");
			max_successful_interleave_factor = interleave_factor;
			low = interleave_factor + 1; /* all interleave factors below current one must also be a subsequence
										    so don't need to check */
		}
		else
		{
			printf("failed\n");
			high = interleave_factor - 1; /* all interleave factors above current one cannot be a subsequence
										    so don't need to check */
		}
	}

	return max_successful_interleave_factor;
}