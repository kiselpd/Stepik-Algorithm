#include<iostream>
#include<stack>
#include<vector>

class MaxHeap
{
private:
    std::vector<int> arr_;

    void siftDown(size_t index);
    void siftUp(size_t index);

public:

    void pop();
    size_t peekMax() const;

    bool isEmpty() const;

    void push(size_t value);

    void print() const;
};

void MaxHeap::print() const
{
    for(auto tmp : this->arr_)
        std::cout << tmp << " ";

    std::cout << std::endl;
}

bool MaxHeap::isEmpty() const
{
    return this->arr_.empty();
}


void MaxHeap::siftDown(size_t index)
{
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    int largest = index;

    if((left < this->arr_.size()) && (this->arr_[index] < this->arr_[left]))
        largest = left;

    if((right < this->arr_.size()) && (this->arr_[largest] < this->arr_[right]))
        largest = right;

    if(largest != index)
    {
        std::swap(this->arr_[index], this->arr_[largest]);
        this->siftDown(largest);
    }
}

void MaxHeap::siftUp(size_t index)
{
    size_t index_parent = (index - 1) / 2;

    if (index && this->arr_[index_parent] < this->arr_[index])
    {
            std::swap(this->arr_[index], this->arr_[index_parent]);
            this->siftUp(index_parent);
    }

}

void MaxHeap::pop()
{
    if(!this->arr_.empty())
    {
        this->arr_[0] = this->arr_.back();
        this->arr_.pop_back();
        this->siftDown(0);
    }
}

void MaxHeap::push(size_t value)
{
    this->arr_.push_back(value);
    
    if(!this->arr_.empty())
        this->siftUp(this->arr_.size() - 1);
}

size_t MaxHeap::peekMax() const
{
    return this->arr_.at(0);
}

void solution()
{
    size_t count, weight, answer = 0;
    std::cin >> count;

    MaxHeap heap;

    for (size_t i = 0; i < count; i++)
    {
        size_t value;
        std::cin >> value;
        heap.push(value);
    }

    std::cin >> weight;
    std::stack<size_t> st;

    while (!heap.isEmpty())
    {
        size_t tmp_weight = weight;

        while (!heap.isEmpty())
        {   
            if(tmp_weight >= heap.peekMax())
            {
                st.push(heap.peekMax());
                tmp_weight -= heap.peekMax();
                heap.pop();
            }
            else
                break;
        }

        while (!st.empty())
        {
            if(st.top() > 1)
            {
                size_t value = st.top() / 2;
                heap.push(value);
            }
            st.pop();
        }
        answer++;
    }

    std::cout << answer << std::endl;
}

int main()
{
    solution();

    return EXIT_SUCCESS;
}