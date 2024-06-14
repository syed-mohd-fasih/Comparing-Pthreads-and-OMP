#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 5

void Cocktail_Sort(int *A, int size)
{
    int start = 0, end = size - 1;
    int swap;
    int counter = 0;
    while (counter != size / 2 + 1)
    {
        swap = 0;
#pragma omp parallel sections num_threads(2)
        {
#pragma omp section
            {
#pragma omp parallel for shared(A, swap, start)
                for (int i = start; i < end; i += 2)
                {
                    if (A[i] > A[i + 1])
                    {
                        int temp = A[i];
                        A[i] = A[i + 1];
                        A[i + 1] = temp;
                        swap = 1;
                    }
                }
            }
#pragma omp section
            {
#pragma omp parallel for shared(A, swap)
                for (int j = end; j > start; j -= 2)
                {
                    if (A[j] < A[j - 1])
                    {
                        int temp = A[j];
                        A[j] = A[j - 1];
                        A[j - 1] = temp;
                        swap = 1;
                    }
                }
            }
        }

        if (!swap)
        {
            break;
        }

        (start == 0) ? start++ : start--;
        (end == size - 1) ? end-- : end++;
        counter++;
    }
}

int *merge(int *P, int n)
{
    int *FP = (int *)calloc(n, sizeof(int));
    int i = 0, j = n / 2 + 1, k = 0;
    for (; i <= n / 2; k++)
    {
        if (P[i] < P[j] || j >= n)
        {
            FP[k] = P[i];
            i++;
        }
        else
        {
            if (j < n)
            {
                FP[k] = P[j];
                j++;
            }
        }
    }
    while (j < n)
    {
        FP[k] = P[j];
        j++;
        k++;
    }
    return FP;
}

int main(void)
{
    srand(time(NULL));
    int n = SIZE;
    struct timeval stop, start;
    int *ptr = (int *)calloc(n, sizeof(int));
    printf("Original Array: ");
    for (int i = 0; i < n; i++)
    {
        *(ptr + i) = rand() % (n * 10);
        printf("%d ", *(ptr + i));
    }
    printf("\n");

    clock_t startTime = clock();
    gettimeofday(&start, NULL);
    Cocktail_Sort(ptr, n);

    int *fp = merge(ptr, n);
    gettimeofday(&stop, NULL);
    clock_t endTime = clock();

    printf("Sorted Array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", (fp[i]));
    }
    printf("\n");

    double timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Time Taken : %lf seconds\n", timeTaken);

    return 0;
}
