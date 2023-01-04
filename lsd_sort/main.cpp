#include<iostream>
#include<cstring>

const long long size_lsd = 256;

void counting_sort(long long *arr, const size_t size, const size_t byte)
{
    long long *c = new long long[size_lsd];
    for (size_t i = 0; i < size_lsd; i++)
        c[i] = 0;

    for (size_t i = 0; i < size; i++)
        ++c[(arr[i] >> (byte * sizeof(long long))) & (size_lsd - 1)];

    int sum = 0;

    for (size_t i = 0; i < size_lsd; i++)
    {
        long long tmp = c[i];
        c[i] = sum;
        sum += tmp;
    }

    long long *b = new long long[size];
    for (int i = 0; i < size ; ++i)
        b[c[(arr[i] >> (byte * sizeof(long long))) & (size_lsd - 1)]++] = arr[i];

    
    delete[] c;
    memcpy(arr, b, size * sizeof(long long));
    delete[] b;
}

void lsd_sort(long long *arr, const size_t size)
{
    for (size_t i = 0; i < sizeof(long long); i++)
        counting_sort(arr, size, i);
}

void solution()
{
    size_t count;

    std::cin >> count;

    long long *arr = new long long[count];

    for (size_t i = 0; i < count; i++)
        std::cin >> arr[i];

    lsd_sort(arr, count);

    for (size_t i = 0; i < count; i++)
        std::cout << arr[i] << " ";

    std::cout << std::endl;

    delete[] arr;
}

int main()
{
    solution();

    return EXIT_SUCCESS;
}