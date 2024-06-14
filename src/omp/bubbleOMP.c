#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 10

int arr[SIZE];

void generate_random_array(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }
}

void merge(int left, int mid, int right)
{
    int size1 = mid - left + 1;
    int size2 = right - mid;

    int leftArr[size1], rightArr[size2];
    int i, j, k;

    for (i = 0; i < size1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < size2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < size1 && j < size2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < size1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < size2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void bubble_sort(int start, int end)
{
    int i, j;
    for (i = start; i <= end; i++)
    {
        for (j = start; j < end - i - start; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    printf("Before sorting:\n");

    generate_random_array(arr, SIZE);

    int i;
    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    clock_t start_time, end_time;
    double final_time;

    start_time = clock();

#pragma omp parallel num_threads(4)
    {
#pragma omp sections
        {
#pragma omp section
            bubble_sort(0, SIZE / 4 - 1);

#pragma omp section
            bubble_sort(SIZE / 4, SIZE / 2 - 1);

#pragma omp section
            bubble_sort(SIZE / 2, 3 * SIZE / 4 - 1);

#pragma omp section
            bubble_sort(3 * SIZE / 4, SIZE - 1);
        }
    }

    merge(0, SIZE / 4 - 1, SIZE / 2 - 1);
    merge(SIZE / 2, 3 * SIZE / 4 - 1, SIZE - 1);
    merge(0, (SIZE - 1) / 2, SIZE - 1);

    end_time = clock();

    final_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("After sorting:\n");
    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Time taken: %f seconds\n", final_time);

    return 0;
}
