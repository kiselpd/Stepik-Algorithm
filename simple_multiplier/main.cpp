#include<iostream>
#include<vector>

size_t TWO = 2;

bool is_simple(size_t digital)
{
    if((digital == 1) || (digital == 2))
        return true;

    for (size_t i = TWO; i < digital; i++)
        if(!(digital % (i*i)))
            return false;

    return true;
}

size_t get_simple_multiplie(size_t digital, std::vector<size_t> &answer_vec)
{
    if(!digital)
        return digital;
        
    size_t i = TWO;

    while(digital != 1)
    {
        if(!(digital % i) && (is_simple(i)))
        {
            answer_vec.push_back(i);
            digital /= i;
        }
        else
            i++;
    }

    return answer_vec.size();
}

void print_vec(const std::vector<size_t> &vec)
{
    for(auto tmp : vec)
        std::cout<<tmp<<" ";

    std::cout << std::endl;
}

void solution()
{
    size_t digital;

    std::cin>>digital;

    std::vector<size_t> answer_vec;

    size_t answer_size = get_simple_multiplie(digital, answer_vec);

    if(answer_size)
        print_vec(answer_vec);
}

int main()
{
    solution();

    return EXIT_SUCCESS;
}