#include<iostream>
#include<vector>
#include<queue>

template<typename T>
class MinHeap
{
private:
    std::vector<T> vec_;

    size_t size() const;
    void siftUp(size_t index);
    void siftDown(size_t index);


public:
    T getMax();
    bool isEmpty() const;
    void heapSort(std::vector<T> &sort_vec);
    void push(T push_element);
};

template<typename T>
size_t MinHeap<T>::size() const
{
    return this->vec_.size();
}

template<typename T>
bool MinHeap<T>::isEmpty() const
{
    return this->vec_.empty();
}

template<typename T>
void MinHeap<T>::siftUp(size_t index) 
{
    size_t index_parent = (index - 1) / 2;

    if(index && this->vec_[index] < this->vec_[index_parent])
    {
        std::swap(this->vec_[index], this->vec_[index_parent]);
        this->siftUp(index_parent);
    }
}

template<typename T>
void MinHeap<T>::siftDown(size_t index) 
{
    size_t left = index * 2 + 1;
    size_t right = index * 2 + 2;
    int largest = index;

    if ((left < this->size()) && this->vec_[left] < this->vec_[index])
        largest = left;

    if ((right < this->size()) && this->vec_[right] < this->vec_[largest])
        largest = right;

    if(largest != index)
    {
        std::swap(this->vec_[index], this->vec_[largest]);
        this->siftDown(largest);
    }
}

template<typename T>
T MinHeap<T>::getMax() 
{
    T get_element = this->vec_[0];

    this->vec_[0] = this->vec_.back();
    this->vec_.pop_back();

    this->siftDown(0);

    return get_element;
}

template<typename T>
void MinHeap<T>::push(T push_element) 
{
    this->vec_.push_back(push_element);
    this->siftUp(this->size() - 1);
}

template<typename T>
void MinHeap<T>::heapSort(std::vector<T> &sort_vec)
{
    for(auto tmp : sort_vec)
        this->push(tmp);

    for (int i = sort_vec.size(); i > 0; i--)
        sort_vec[i - 1] = this->getMax();
}

void share(const std::vector<int> &input_vec, size_t number_of_parts, std::vector<std::queue<int>> &output_vecs)
{
    for (size_t i = 0; i < input_vec.size(); i++)
        output_vecs[i % number_of_parts].push(input_vec.at(i));
}

void improved_split_sort(std::vector<int> &input_vec, size_t number_of_parts)
{
    std::vector<std::queue<int>> divided_vecs(number_of_parts);
    share(input_vec, number_of_parts, divided_vecs);
    input_vec.clear();

    MinHeap<std::pair<int, size_t>> heap_element;
    
    for (size_t i = 0; i < number_of_parts; i++)
    {
        heap_element.push(std::make_pair(divided_vecs[i].front(), i));
        divided_vecs[i].pop();
    }

    while (!heap_element.isEmpty())
    {
        auto tmp = heap_element.getMax();
        input_vec.push_back(tmp.first);

        if(!divided_vecs[tmp.second].empty())
        {
            heap_element.push(std::make_pair(divided_vecs[tmp.second].front(), tmp.second));
            divided_vecs[tmp.second].pop();
        }
    }
    
}

void solution()
{
    size_t count, number_of_parts;
    std::vector<int> input_vec;

    std::cin >> count;

    for (size_t i = 0; i < count; i++)
    {
        int element;
        std::cin >> element;
        input_vec.push_back(element);
    }

    std::cin >> number_of_parts;

    improved_split_sort(input_vec, number_of_parts);

    for (size_t i = 0; i < count; i++)
        std::cout << input_vec.at(i) << " ";
}

int main()
{
    solution();
    return EXIT_SUCCESS;
}
