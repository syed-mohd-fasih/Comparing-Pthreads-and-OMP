#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 100
int arr[SIZE];

void randomizer(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        array[i] = rand() % 1000;
    }
}

void selectionSort(int start, int end)
{
    int i, j;
    for (i = start; i < end; i++)
    {
        int min_index = i;
        for (j = i + 1; j < SIZE; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

int main()
{

    randomizer(arr, SIZE);

    int i;
    clock_t start_time, end_time;
    double total_time;

    start_time = clock();

#pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();
        int chunk_size = SIZE / 2;
        int start = thread_id * chunk_size;
        int end = start + chunk_size;
        if (thread_id == 1)
        {
            end = SIZE;
        }
        selectionSort(start, end);
    }

    end_time = clock();

    total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Sorted array: ");
    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Time taken: %f seconds\n", total_time);

    return 0;
}
