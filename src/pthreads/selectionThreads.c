#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 5000

int arr[SIZE];

void randomizer(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        array[i] = rand() % 1000;
    }
}

typedef struct
{
    int start;
    int end;
} ThreadArgs;

void *selectionSort(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int start = args->start;
    int end = args->end;

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

    pthread_exit(NULL);
}

int main()
{

    randomizer(arr, SIZE);

    int i;
    clock_t start_time, end_time;
    double total_time;

    pthread_t threads[2];
    ThreadArgs args1 = {0, SIZE / 2};
    ThreadArgs args2 = {SIZE / 2, SIZE};

    start_time = clock();

    pthread_create(&threads[0], NULL, selectionSort, (void *)&args1);
    pthread_create(&threads[1], NULL, selectionSort, (void *)&args2);

    for (i = 0; i < 2; i++)
    {
        pthread_join(threads[i], NULL);
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
