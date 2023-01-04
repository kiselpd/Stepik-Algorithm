#include<iostream>

const size_t PUSH_FRONT = 1;
const size_t POP_FRONT = 2;

const size_t PUSH_BACK = 3;
const size_t POP_BACK = 4;

class MyDec
{
private:
    int *buffer_;
    int buffer_size_;
    int head_;
    int tail_;

public:
    MyDec(int size);
    ~MyDec();

    bool isEmpty() const;
    bool isFull() const;

    bool pushFront(int value);
    bool pushBack(int value);

    int popFront();
    int popBack();

    size_t count() const;
};

MyDec::MyDec(int size) : buffer_size_(size+1), head_(0), tail_(0) 
{
    this->buffer_ = new int[this->buffer_size_];
}

MyDec::~MyDec()
{
    delete[](this->buffer_);
}

bool MyDec::isEmpty() const
{
    return (this->head_ == this->tail_);
}

bool MyDec::isFull() const
{
    return (((this->tail_ + 1) % this->buffer_size_) == this->head_);
}

bool MyDec::pushFront(int value)
{
    if(this->isFull())
        return false;

    if(!this->head_)
        this->head_ = this->buffer_size_;

    this->buffer_[--(this->head_)] = value;

    return true;
}

bool MyDec::pushBack(int value)
{
    if(this->isFull())
        return false;

    if(this->tail_ == buffer_size_ - 1)
        this->tail_ = 0;

    this->buffer_[(this->tail_)++] = value;

    return true;
}

int MyDec::popFront()
{
    int value = this->buffer_[(this->head_)++];
    this->head_ %= this->buffer_size_;

    return value;
}

int MyDec::popBack()
{
    return (this->buffer_[this->tail_ ? --(this->tail_) : this->tail_ = this->buffer_size_ - 1]);
}

size_t MyDec::count() const
{
    if(this->tail_ >= this->head_)
        return this->tail_ - this->head_;
    else
        return this->tail_ + (this->buffer_size_ - this->head_);
}

void solution()
{
    size_t count;
    std::cin>>count;
    bool answer = true;
    MyDec dec(count);

    for (size_t i = 0; i < count; i++)
    {
        int operation, value;

        std::cin >> operation >> value;

        switch (operation)
        {
        case POP_BACK:
            if(!dec.isEmpty())
                answer = (value == dec.popBack());
            else
                answer = false;
            break;

        case POP_FRONT:
            if(value == -1)
                answer = dec.isEmpty();
            else if(!dec.isEmpty())
                answer = (value == dec.popFront());
            else
                answer = false;

            break;

        case PUSH_BACK:
            answer = dec.pushBack(value);
            break;

        case PUSH_FRONT:
            answer = dec.pushFront(value);
            break;
        
        default:
            break;
        }

    }

    if(count != dec.count())
        {
            if(answer)
                std::cout << "YES";
            else
                std::cout << "NO";
        }

    return;
}

int main()
{
    solution();
    return EXIT_SUCCESS;
}
 