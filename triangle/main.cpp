#include<iostream>
#include<string>

long long find_triangle_digital(long long input_digital);

long long is_digital(std::string input_str);

int main()
{
    std::string input_str;

    std::cin >> input_str;

    std::cout << find_triangle_digital(is_digital(input_str));

    return 0;
}

long long is_digital(std::string input_str)
{
    long long digital = 0;
    size_t i = 0;

    if(input_str[0] == '+')
        i++;

    for (; i < input_str.size(); i++)
    {
        if((input_str[i] >= '0') && (input_str[i] <= '9'))
            digital = digital * 10 + (long long)(input_str[i] - '0');
        else
            return 0;
    }

    return digital;
}

long long find_triangle_digital(long long input_digital)
{
    long long tmp = 0;
    long long sum = 0;

    while((sum != input_digital) && (sum<input_digital))
    {
        tmp++;
        sum += tmp;
    }

    if (sum==input_digital)
        return tmp;
    else
        return 0;
}
