#include<iostream>
#include<vector>

struct Layers
{
    int first;
    int second;

    friend bool operator>(const Layers &first, const Layers &second);
    friend bool operator==(const Layers &first, const Layers &second);
    friend std::ostream &operator << (std::ostream &out, const Layers &layers);
    friend std::istream &operator >> (std::istream &in, Layers &layers);
};

bool operator>(const Layers &first, const Layers &second)
{
    if(first.first == second.first)
        return first.second > second.second;

    return first.first > second.first;
}

std::istream &operator >> (std::istream &in, Layers &layers)
{
    in >> layers.first;
    in >> layers.second;

    return in;
}

bool operator==(const Layers &first, const Layers &second)
{
    return (first.first == second.first) && (first.second == second.second);
}

std::ostream& operator<<(std::ostream &out, const Layers &layers)
{
    out << layers.first << " " << layers.second << std::endl;
    return out;
}

template<typename T>
void merge(typename std::vector<T>::iterator it_first_begin, typename std::vector<T>::iterator it_first_end, typename std::vector<T>::iterator it_second_begin, typename std::vector<T>::iterator it_second_end)
{
    std::vector<T> out;
    auto it_first_tmp = it_first_begin;
    auto it_second_tmp = it_second_begin;
    size_t i = 0;

    while (true)
    {
        if(((*it_first_tmp) > (*it_second_tmp)) && (it_second_tmp != it_second_end))
        {
            out.push_back(*it_second_tmp);
            it_second_tmp++;
        }
        else if(it_first_tmp != it_first_end)
        {
            out.push_back(*it_first_tmp);
            it_first_tmp++;
        }
        else
            break;
    }

    std::copy(out.begin(), out.end(), it_first_begin);
}

template<typename T>
void merge_sort(typename std::vector<T>::iterator it_begin, typename std::vector<T>::iterator it_end)
{
    if((it_end - it_begin) <= 1)
        return;

    int first_length = (it_end - it_begin) / 2;
    int second_length = (it_end - it_begin) - first_length;

    merge_sort<T>(it_begin, it_begin + first_length);
    merge_sort<T>(it_begin + first_length, it_end);

    merge<T>(it_begin, it_begin + first_length, it_begin + first_length, it_end);
}

size_t length_single_layer(const std::vector<Layers> &vec)
{
    std::vector<std::pair<int, bool>> out_vec(vec.size() * 2);

    for (size_t i = 0; i < vec.size(); i++)
    {
        out_vec[i*2] = std::make_pair (vec[i].first, false);
		out_vec[i*2+1] = std::make_pair (vec[i].second, true);
    }

    merge_sort<std::pair<int, bool>>(out_vec.begin(), out_vec.end());
    size_t result = 0;
    int count_iter = 0;

    for (size_t i = 0; i < out_vec.size(); i++)
    {
        if((count_iter==1) && i)
            result += out_vec[i].first - out_vec[i - 1].first;

        if(out_vec[i].second)
            --count_iter;
        else
            ++count_iter;
    }

    return result;
}

void solution()
{
    size_t count;

    std::cin>>count;

    std::vector<Layers> vec;

    for (size_t i = 0; i < count; i++)
    {
        Layers tmp;
        std::cin >> tmp;
        vec.push_back(tmp);
    }

    std::cout << length_single_layer(vec) << std::endl;
}

int main()
{
    solution();

    return EXIT_SUCCESS;
}