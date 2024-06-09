#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 10

void merge(int arr[], int left, int mid, int right);
void merge_sort(int arr[], int left, int right);

int main()
{
    int arr[SIZE];
    srand(time(NULL));
    printf("Original array: ");
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");

    double start_time = omp_get_wtime();

    merge_sort(arr, 0, SIZE - 1);

    double end_time = omp_get_wtime();

    printf("Sorted array: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Time taken: %f seconds\n", end_time - start_time);

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

void merge_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid1 = left + (right - left) / 4;
        int mid2 = left + (right - left) / 2;
        int mid3 = left + 3 * (right - left) / 4;

#pragma omp parallel sections
        {
#pragma omp section
            merge_sort(arr, left, mid1);
#pragma omp section
            merge_sort(arr, mid1 + 1, mid2);
#pragma omp section
            merge_sort(arr, mid2 + 1, mid3);
#pragma omp section
            merge_sort(arr, mid3 + 1, right);
        }

        merge(arr, left, mid1, mid2);
        merge(arr, mid2 + 1, mid3, right);
        merge(arr, left, mid2, right);
    }
}
