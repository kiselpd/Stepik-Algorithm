#include<iostream>
#include<vector>

template<typename T>
class MaxHeap
{
private:
    std::vector<T> vec_;

    size_t size() const;
    bool isEmpty() const;
    void siftUp(size_t index);
    void siftDown(size_t index);


public:
    T getMax();
    void heapSort(std::vector<T> &sort_vec);
    void push(T push_element);
};

template<typename T>
size_t MaxHeap<T>::size() const
{
    return this->vec_.size();
}

template<typename T>
bool MaxHeap<T>::isEmpty() const
{
    return this->vec_.empty();
}

template<typename T>
void MaxHeap<T>::siftUp(size_t index) 
{
    size_t index_parent = (index - 1) / 2;

    if(index && this->vec_[index] > this->vec_[index_parent])
    {
        std::swap(this->vec_[index], this->vec_[index_parent]);
        this->siftUp(index_parent);
    }
}

template<typename T>
void MaxHeap<T>::siftDown(size_t index) 
{
    size_t left = index * 2 + 1;
    size_t right = index * 2 + 2;
    int largest = index;

    if ((left < this->size()) && this->vec_[left] > this->vec_[index])
        largest = left;

    if ((right < this->size()) && this->vec_[right] > this->vec_[largest])
        largest = right;

    if(largest != index)
    {
        std::swap(this->vec_[index], this->vec_[largest]);
        this->siftDown(largest);
    }
}

template<typename T>
T MaxHeap<T>::getMax() 
{
    T get_element = this->vec_[0];

    this->vec_[0] = this->vec_.back();
    this->vec_.pop_back();

    this->siftDown(0);

    return get_element;
}

template<typename T>
void MaxHeap<T>::push(T push_element) 
{
    this->vec_.push_back(push_element);
    this->siftUp(this->size() - 1);
}

template<typename T>
void MaxHeap<T>::heapSort(std::vector<T> &sort_vec)
{
    for(auto tmp : sort_vec)
        this->push(tmp);

    for (int i = sort_vec.size(); i > 0; i--)
        sort_vec[i - 1] = this->getMax();
}

struct Pozition
{
    int x;
    int y;

    Pozition(int x, int y);
    friend bool operator>(const Pozition &poz1, const Pozition &poz2);
};

Pozition::Pozition(int x, int y) : x(x), y(y){};

bool operator>(const Pozition &poz1, const Pozition &poz2)
{
    if(poz1.x == poz2.x)
        return poz1.y > poz2.y;
    else
        return poz1.x > poz2.x;
}

void print(const Pozition &poz)
{
    std::cout << poz.x << " " << poz.y << std::endl;
}

void solution()
{
    size_t count;
    std::vector<Pozition> polyline;
    MaxHeap<Pozition> polyline_heap;

    std::cin >> count;

    for (size_t i = 0; i < count; i++)
    {
        int x, y;
        std::cin >> x >> y;

        Pozition poz(x, y);
        polyline.push_back(poz);
    }

    polyline_heap.heapSort(polyline);

    for(auto tmp : polyline)
        print(tmp);
}

int main()
{
    solution();

    return EXIT_SUCCESS;
}