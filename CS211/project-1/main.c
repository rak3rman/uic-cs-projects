#include <stdio.h>
#include <stdlib.h>

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS211 - Project 01 - 02/03/2021
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

// Function prototypes
void makeArrayCopy (int fromArray[], int toArray[], int size);
void myFavoriteSort (int arr[], int size);
void indexComparison (int unsortedArray[], int sortedArray[], int size, int *counter);
int targetSum (int arr[], int size, int target, int* index1, int* index2);
void printArray(int arr[], int size);

int main (int argc, char** argv)
{
    int val;
    int userInput = 0;

    /* setup arr1 */
    int *arr1;
    int size_arr1 = 5;
    arr1 = (int*)malloc(sizeof(int) * size_arr1);

    /* prompt the user for input */
    printf ("Enter in a list of numbers to be stored in a dynamic array.\n");
    printf ("End the list with the terminal value of -999\n");

    /* loop until the user enters -999 */
    int count1 = 0;
    scanf ("%d", &val);
    while (val != -999) {
        /* store the value into an array */
        if (count1 >= size_arr1) {
            /* set tmp to refer to the location of old array*/
            int *tmp ;
            tmp = arr1;
            /*allocate new space for the larger array*/
            arr1 = (int*)malloc(sizeof(int) * size_arr1 * 2);
            /*copy the existing values from the
            original array to the larger array*/
            for (int k = 0; k < size_arr1; k++)
                arr1[k] = tmp[k];
            /* return the allocated memory from the
              original array back to the OS*/
            free(tmp);
            /* update the size1 variable to properly
               reflect the current size of the array*/
            size_arr1 = size_arr1 * 2;
        }
        /* store value in array */
        arr1[count1] = val;
        count1++;
        /* get next value */
        scanf("%d", &val);
    }

    /* setup arr2 */
    int *arr2;
    int size_arr2 = size_arr1;
    arr2 = (int*)malloc(sizeof(int) * size_arr2);

    /* call function to make a copy of the array of values */
    makeArrayCopy(arr1, arr2, count1);

    /* call function to sort one of the arrays */
    myFavoriteSort(arr2, count1);

    /* repeat function call until proper value is inputted */
    printf("Enter 1 to perform index comparison, enter 2 to perform target sum.\n");
    while (!(userInput == 1 || userInput == 2)) {
        /* Prompt user to enter a value to pick a task */
        scanf("%d", &userInput);
        if (userInput == 1) {
            /* If user input is 1, perform index comparison */
            int counter = 0;
            indexComparison(arr1, arr2, count1, &counter);
            if (counter == 0) {
                printf("All elements change location in the sorted array.\n");
            } else {
                printf("%d values are in the same location in both arrays.\n", counter);
            }
        } else if (userInput == 2) {
            /* If user input is 2, perform target sum */
            /* loop until the user enters -999 */
            printf ("Enter in a list of numbers to use for searching.  \n");
            printf ("End the list with a terminal value of -999\n");
            scanf ("%d", &val);
            while (val != -999) {
                /* call function to perform target sum operation */
                int index1 = 0;
                int index2 = 0;
                int result = targetSum(arr2, count1, val, &index1, &index2);
                /* print out info about the target sum results  */
                if (result == 1) {
                    printf("Success! Elements at indices %d and %d add up to %d\n", index1, index2, val);
                } else if (result == -1) {
                    printf("Target sum failed!\n");
                }
                /* get next value */
                scanf("%d", &val);
            }
        } else {
            printf("Invalid input. Enter 1 or 2.\n");
        }
    }

    printf ("Good bye\n");
    return 0;
}

// Make copy of an array
void makeArrayCopy(int fromArray[], int toArray[], int size) {
    /* loop through each value and copy  */
    for (int i = 0; i < size; i++) {
        toArray[i] = fromArray[i];
    }
}

// Sort an array into descending order
void myFavoriteSort(int arr[], int size) {
    int i, key, j;
    /* sort using insertion sort  */
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Compare two arrays and return counter
void indexComparison(int unsortedArray[], int sortedArray[], int size, int *counter) {
    /* loop through each value in unsorted array  */
    for (int i = 0; i < size; i++) {
        if (unsortedArray[i] == sortedArray[i]) {
            *counter = *counter + 1;
        }
    }
}

// Calculate the target sum of two arrays
int targetSum(int arr[], int size, int target, int* index1, int* index2){
    int i;
    *index1 = 0;
    *index2 = size - 1;
    /* move from front to back and eval sum  */
    while (*index1 != *index2) {
        if(arr[*index1] + arr[*index2] > target){
            *index2 = *index2 - 1;
        } else if(arr[*index1] + arr[*index2] < target){
            *index1 = *index1 + 1;
        } else if(arr[*index1] + arr[*index2] == target){
            return 1;
        }
    }
    return -1;
}

// Print array for debugging purposes
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
