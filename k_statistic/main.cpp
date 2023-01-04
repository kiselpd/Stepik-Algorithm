#include<iostream>
#include<vector>


size_t find_pivot(std::vector<int> vec, size_t left, size_t right)
{
    size_t mid = (left + right) / 2;

     if(vec[left] <= vec[mid])
    {
        if(vec[mid] <= vec[right])
            return mid;
        
        return (vec[left] > vec[right]) ? left : right;
    }
    else
    {
        if(vec[mid] >= vec[right])
            return mid;

        return (vec[left] <= vec[right]) ? left : right;
    }
}

int partition(std::vector<int> &mas, int left, int right) {
    if (left != right)
        std::swap(mas[find_pivot(mas, left, right)], mas[right]);

    int pivot = mas[right];
    
    size_t i = 0, j = right - 1;

    while(i<=j)
    {
        for (; mas[i] < pivot; i++) {}
        for (;(mas[j] > pivot) && (j >= left); j--) {}
        if(i<j)
            std::swap(mas[i++], mas[j--]);
    }

    std::swap(mas[i], mas[right]);

     return i;
}

int k_statistic(std::vector<int> &mas, int k)
{
    size_t left = 0, right = mas.size() - 1, pos;

    do
    {
        pos = partition(mas, left, right);

        if(pos < k)
            left = pos + 1;
        else if(pos > k)
            right = pos - 1;
    } while (k != pos);

    return mas[pos];
}

void solution()
{
    size_t count;
    int k;

    std::cin >> count >> k;

    std::vector<int> vec(count);

    for(size_t i = 0; i<count; i++)
        std::cin >> vec[i];

    std::cout << k_statistic(vec, k) << std::endl;
}

int main()
{
    solution();
    return 0;
}

