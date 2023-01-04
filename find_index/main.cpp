#include<iostream>
#include<vector>
#include<cmath>

std::pair<size_t, size_t> exponential_search(const std::vector<int> &vec, const int element)
{
    size_t right_index = 2, left_index = 0, step = 1;

    while (vec.at(right_index) < element)
    {
        left_index = right_index;
        right_index = pow(right_index, step);
        step++;

        if(right_index >= vec.size())
        {
            right_index = vec.size() - 1;
            break;
        }

    }

    return {left_index, right_index};
}

size_t binary_search(const std::vector<int> &vec, size_t left, size_t right, const int element)
{
    while(left < right)
    {
        size_t mid = (right + left) / 2;

        if(element <= vec.at(mid))
            right = mid;
        else
            left = mid + 1;
    }

    return left;
}

void scanf_vector(std::vector<int> &vec)
{
    for (size_t i = 0; i < vec.size(); i++)
        std::cin >> vec[i];
}

void solution()
{
    size_t count1, count2;

    std::cin>>count1;
    std::vector<int> vec1(count1);
    scanf_vector(vec1);

    std::cin>>count2;
    std::vector<int> vec2(count2);
    scanf_vector(vec2);
    

    for(auto tmp : vec2)
    {
        auto indexes = exponential_search(vec1, tmp);

        auto index_answer = binary_search(vec1, indexes.first, indexes.second, tmp);

        if (index_answer)
            if(abs(tmp - vec1.at(index_answer)) >= abs(tmp - vec1.at(index_answer - 1)))
                index_answer--;

        std::cout << index_answer << " ";

    }

    std::cout << std::endl;
}

int main()
{
    solution();
    return EXIT_SUCCESS;
}