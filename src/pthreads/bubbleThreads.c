#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 5

int arr[SIZE];

typedef struct
{
    int start;
    int end;
} Range;

void *bubble_sort(void *arg)
{
    Range *range = (Range *)arg;
    int i, j;
    for (i = range->start; i <= range->end; i++)
    {
        for (j = range->start; j < range->end - i + range->start; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    pthread_exit(NULL);
}

void merge(int left, int mid, int right)
{
    int size1 = mid - left + 1;
    int size2 = right - mid;

    int leftArr[size1], rightArr[size2];

    for (int i = 0; i < size1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < size2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
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

void merge_sort(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort(left, mid);
        merge_sort(mid + 1, right);
        merge(left, mid, right);
    }
}

void parallel_bubble_sort(int num_threads)
{
    pthread_t threads[num_threads];
    int i;
    int range_size = SIZE / num_threads;

    for (i = 0; i < num_threads; i++)
    {
        Range *range = (Range *)malloc(sizeof(Range));
        range->start = i * range_size;
        range->end = (i == num_threads - 1) ? SIZE - 1 : (i + 1) * range_size - 1;
        pthread_create(&threads[i], NULL, bubble_sort, (void *)range);
    }

    for (i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    merge_sort(0, SIZE - 1);
}

void randomize_array()
{
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % 100;
    }
}

int main()
{
    printf("Before sorting:\n");
    int i;
    clock_t start_time, end_time;
    double final_time;

    randomize_array();

    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    start_time = clock();

    parallel_bubble_sort(4);

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
