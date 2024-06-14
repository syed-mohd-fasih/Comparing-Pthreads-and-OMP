#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 5000

typedef struct
{
    int *arr;
    int left;
    int right;
} SortArgs;

void cocktail_sort(int arr[], int size);
void *bubble_sort_forward(void *arg);
void *bubble_sort_backward(void *arg);

int main()
{
    int arr[SIZE];

    printf("Original array: ");
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");

    clock_t start_time = clock();

    cocktail_sort(arr, SIZE);

    clock_t end_time = clock();

    double final_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Sorted array: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Time taken: %f seconds\n", final_time);

    return 0;
}

void cocktail_sort(int arr[], int size)
{
    pthread_t forward_tid, backward_tid;
    SortArgs forward_args = {arr, 0, size - 1};
    SortArgs backward_args = {arr, 0, size - 1};

    while (forward_args.left < forward_args.right && backward_args.left < backward_args.right)
    {
        pthread_create(&forward_tid, NULL, bubble_sort_forward, (void *)&forward_args);
        pthread_create(&backward_tid, NULL, bubble_sort_backward, (void *)&backward_args);

        pthread_join(forward_tid, NULL);
        pthread_join(backward_tid, NULL);

        forward_args.left++;
        forward_args.right--;
        backward_args.left++;
        backward_args.right--;
    }
}

void *bubble_sort_forward(void *arg)
{
    SortArgs *args = (SortArgs *)arg;
    int *arr = args->arr;
    int left = args->left;
    int right = args->right;

    for (int i = left; i < right; i++)
    {
        for (int j = left; j < right - i + left; j++)
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

void *bubble_sort_backward(void *arg)
{
    SortArgs *args = (SortArgs *)arg;
    int *arr = args->arr;
    int left = args->left;
    int right = args->right;

    for (int i = right; i > left; i--)
    {
        for (int j = right; j > left; j--)
        {
            if (arr[j] < arr[j - 1])
            {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }

    pthread_exit(NULL);
}
