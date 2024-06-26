#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>

#define Size 5000

struct timeval Stop2, start2;
int n1[Size];
int n2[Size];
typedef struct dim
{
	int start;
	int end;
} limit;

typedef struct joined
{
	int Start;
	int mid;
	int End;
} join;

int binary_search(int move, int start, int end)
{
	if (end <= start)
	{
		if (move > n1[end])
		{
			return (end + 1);
		}
		else
		{
			return end;
		}
	}

	int mid = (start + end) / 2;
	if (move == n1[mid])
	{
		return mid + 1;
	}
	if (move > n1[mid])
	{
		return binary_search(move, mid + 1, end);
	}
	return binary_search(move, start, mid - 1);
}

void *merge(void *args)
{
	struct joined *params = (struct joined *)args;
	int begin = params->Start,
		mid = params->mid,
		end = params->End;

	int i = begin, j = mid, tpos = begin;

	while (i < mid && j <= end)
	{
		if (n1[i] < n1[j])
			n2[tpos++] = n1[i++];
		else
			n2[tpos++] = n1[j++];
	}

	while (i <= mid)
		n2[tpos++] = n1[i++];

	while (j <= end)
		n2[tpos++] = n1[j++];
	return NULL;
}

void *insertion(void *l)
{
	limit *l1 = (limit *)l;
	int i = l1->start;
	i++;
	int j, k, move;
	while (i <= l1->end)
	{
		j = i - 1;
		move = n1[i];
		k = binary_search(move, l1->start, j);
		while (j >= k)
		{
			n1[j + 1] = n1[j];
			j--;
		}
		n1[j + 1] = move;
		i++;
	}
	return NULL;
}

void fill_array(int size)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++)
		n1[i] = rand() % 100;
}

void print_array(int *list, int size)
{
	int i;
	for (i = 0; i < size - 1; i++)
		printf("%d, ", list[i]);
	printf("%d\n", list[i]);
}

int main()
{
	fill_array(Size);

	printf("Original Array: ");
	print_array(n1, Size);

	limit l1, l2;
	l1.start = 0;
	l1.end = Size / 2;
	l2.start = l1.end + 1;
	l2.end = Size - 1;
	join j1;
	j1.Start = l1.start;
	j1.mid = l2.start;
	j1.End = l2.end;

	double start_time = omp_get_wtime();

	gettimeofday(&start2, NULL);
#pragma omp parallel sections num_threads(2)
	{
#pragma omp section
		{
			insertion(&l1);
		}
#pragma omp section
		{
			insertion(&l2);
		}
	}

	merge(&j1);

	double end_time = omp_get_wtime();

	double final_time = end_time - start_time;

	printf("\nSorted Array: ");
	print_array(n2, Size);
	printf("Time Taken : %lf\n", final_time);

	return 0;
}
