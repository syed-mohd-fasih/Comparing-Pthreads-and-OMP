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
} MergeArgs;

void merge(int arr[], int left, int mid, int right);
void *merge_sort(void *arg);
void *merge_parts(void *arg);
void randomize_array(int arr[], int size);

int main()
{
    int arr[SIZE];

    randomize_array(arr, SIZE);

    printf("Original array: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");

    MergeArgs args = {arr, 0, SIZE - 1};

    pthread_t tid;

    clock_t start_time, end_time;

    start_time = clock();

    pthread_create(&tid, NULL, merge_sort, (void *)&args);

    pthread_join(tid, NULL);

    end_time = clock();

    double final_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Sorted array: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
    printf("Time taken: %f seconds\n", final_time);

    return 0;
}

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void *merge_parts(void *arg)
{
    MergeArgs *args = (MergeArgs *)arg;
    int left = args->left;
    int right = args->right;
    int mid1 = left + (right - left) / 4;
    int mid2 = left + 2 * (right - left) / 4;
    int mid3 = left + 3 * (right - left) / 4;

    merge(args->arr, left, mid1, mid2);
    merge(args->arr, mid2 + 1, mid3, right);
    merge(args->arr, left, mid2, right);

    pthread_exit(NULL);
}

void *merge_sort(void *arg)
{
    MergeArgs *args = (MergeArgs *)arg;
    int left = args->left;
    int right = args->right;

    if (left < right)
    {
        int mid1 = left + (right - left) / 4;
        int mid2 = left + 2 * (right - left) / 4;
        int mid3 = left + 3 * (right - left) / 4;

        pthread_t threads[4];
        MergeArgs parts[] = {
            {args->arr, left, mid1},
            {args->arr, mid1 + 1, mid2},
            {args->arr, mid2 + 1, mid3},
            {args->arr, mid3 + 1, right}};

        for (int i = 0; i < 4; i++)
        {
            pthread_create(&threads[i], NULL, merge_sort, (void *)&parts[i]);
        }

        for (int i = 0; i < 4; i++)
        {
            pthread_join(threads[i], NULL);
        }

        MergeArgs merge_args = {args->arr, left, right};
        pthread_t tid_merge;
        pthread_create(&tid_merge, NULL, merge_parts, (void *)&merge_args);
        pthread_join(tid_merge, NULL);
    }
    pthread_exit(NULL);
}

void randomize_array(int arr[], int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 100;
}
