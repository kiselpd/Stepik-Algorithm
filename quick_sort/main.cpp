#include<stdio.h>
#include<iostream>

const size_t index_partition = 40;

void insertion_sort(int *arr, const size_t size)
{
    for (size_t i = 1; i < size; ++i)
    {
        int tmp = arr[i];
        int j = i - 1;

        for (; j>=0 && tmp < arr[j]; --j)
            arr[j + 1] = arr[j];

        arr[j + 1] = tmp;
    }
}

size_t find_pivot(int *arr, const size_t size)
{
    size_t mid = size / 2;

     if(arr[0] <= arr[mid])
    {
        if(arr[mid] <= arr[size - 1])
            return mid;
        
        return (arr[0] > arr[size - 1]) ? 0 : (size - 1);
    }
    else
    {
        if(arr[mid] >= arr[size - 1])
            return mid;

        return (arr[0] <= arr[size - 1]) ? 0 : (size - 1);
    }
}

size_t partition(int *arr, const size_t size)
{
    if(size <=1)
        return 0;

    size_t index = find_pivot(arr, size);

    if(index != size - 1)
        std::swap(arr[index], arr[size - 1]);

    const int &pivot = arr[size - 1];

    size_t i = 0, j = size - 2;

    while(i <= j)
    {
        for (; arr[i] < pivot; ++i) {}
        for (;!(arr[j] < pivot) && (j >= 0); j--) {}

        if(i < j)
            std::swap(arr[i++], arr[j--]);
    }

    std::swap(arr[i], arr[size - 1]);

    return i;
}

void quick_sort(int *arr, const int size)
{
    size_t index = partition(arr, size);
    
    if(index >= index_partition - 1)
        quick_sort(arr, index);
    if(index_partition < size - index)
        quick_sort(arr + index + 1, size - index - 1);
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    
    int arr[2000000];
    int element;
    size_t i = 0;

    while( fscanf( stdin, "%d", &element ) != EOF )
        arr[i++]= element;

    quick_sort(arr, i);
    insertion_sort(arr, i);

    for (size_t j = 9; j <= i; j+=10)
        printf("%d ", arr[j]);

    printf("\n");

    delete[] arr;
    return 0;
}