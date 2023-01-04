#include<iostream>
#include<vector>
#include<algorithm>

std::pair<int, int> findIndexMax(const std::vector<int> &vec1, const std::vector<int> &vec2)
{
    std::pair<int, int> answer;

    int max = vec1.at(0) + vec2.at(0);
    size_t index_max_vec1 = 0;

    for (size_t i = 0; i < vec2.size(); i++)
    {   
        if(vec1.at(i) > vec1.at(index_max_vec1))
            index_max_vec1 = i;

        if(vec1.at(index_max_vec1) + vec2.at(i) > max)
        {
            max = vec1.at(index_max_vec1) + vec2.at(i);
            answer.second = i;
            answer.first = index_max_vec1;
        }
    }

    return answer;
}

int main()
{
    size_t count;
    std::cin >> count;

    std::vector<int> vec1(count), vec2(count);

    for (size_t i = 0; i < count; i++)
        std::cin >> vec1[i];

    for (size_t i = 0; i < count; i++)
        std::cin >> vec2[i];

    auto answer = findIndexMax(vec1, vec2);

    std::cout << answer.first << " " << answer.second << std::endl;

    return EXIT_SUCCESS;
}