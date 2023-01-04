#include<vector>
#include<iostream>

void binary_insert(std::vector<int> &vec, int index)
{
    auto value = vec.at(index);
    int left = 0;
    int right = index;

    while(left < right)
    {
        size_t mid = (right + left) / 2;

        if(value <= vec.at(mid))
            right = mid;
        else
            left = mid + 1;
    }

    vec.insert(vec.begin() + left, value);
}

void insertion_sort(std::vector<int> &vec)
{
    for (size_t i = 1; i < vec.size(); i++)
    {
        binary_insert(vec, i);
        vec.erase(vec.begin() + i + 1);
    }
}

void solution()
{
    std::vector<int> vec;
    int value;

    while(std::cin>>value)
        vec.push_back(value);

    insertion_sort(vec);

    for(auto tmp : vec)
        std::cout << tmp << " ";

    std::cout << std::endl;
}

int main()
{
    solution();

    return EXIT_SUCCESS;
}