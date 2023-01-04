#include <iostream>
#include <vector>
#include<stack>
#include <algorithm>
#include <stdexcept>
using namespace std;
 
// Структура данных для хранения узла максимальной кучи
struct PriorityQueue
{
private:
    // vector для хранения элементов кучи
    vector<int> A;
 
    // вернуть родителя `A[i]`
    // не вызывайте эту функцию, если `i` уже является корневым узлом
    int PARENT(int i) {
        return (i - 1) / 2;
    }
 
    // вернуть левого потомка `A[i]`
    int LEFT(int i) {
        return (2*i + 1);
    }
 
    // вернуть правого потомка `A[i]`
    int RIGHT(int i) {
        return (2*i + 2);
    }
 
    // Рекурсивный алгоритм heapify-down.
    // Узел с индексом `i` и два его прямых потомка
    // нарушает свойство кучи
    void heapify_down(int i)
    {
        // получить левый и правый потомки узла с индексом `i`
        int left = LEFT(i);
        int right = RIGHT(i);
 
        int largest = i;
 
        // сравниваем `A[i]` с его левым и правым дочерними элементами
        // и находим наибольшее значение
        if (left < size() && A[left] > A[i]) {
            largest = left;
        }
 
        if (right < size() && A[right] > A[largest]) {
            largest = right;
        }
 
        // поменяться местами с потомком, имеющим большее значение и
        // вызовите heapify-down для дочернего элемента
        if (largest != i)
        {
            swap(A[i], A[largest]);
            heapify_down(largest);
        }
    }
 
    // Рекурсивный алгоритм heapify-up
    void heapify_up(int i)
    {
        // проверяем, не нарушают ли узел с индексом `i` и его родитель свойство кучи
        if (i && A[PARENT(i)] < A[i])
        {
            // поменять их местами, если свойство кучи нарушено
            swap(A[i], A[PARENT(i)]);
 
            // вызываем heapify-up для родителя
            heapify_up(PARENT(i));
        }
    }
 
public:
    // возвращаем размер кучи
    unsigned int size() {
        return A.size();
    }
 
    // Функция для проверки, пуста ли куча или нет
    bool empty() {
        return size() == 0;
    }
 
    // вставляем ключ в кучу
    void push(int key)
    {
        // вставляем новый элемент в конец вектора
        A.push_back(key);
 
        // получаем индекс элемента и вызываем процедуру heapify-up
        int index = size() - 1;
        heapify_up(index);
    }
 
    // Функция для удаления элемента с наивысшим приоритетом (присутствует в корне)
    void pop()
    {
        try {
            // если в куче нет элементов, выбрасываем исключение
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");
            }
 
            // заменяем корень кучи последним элементом
            // вектора
            A[0] = A.back();
            A.pop_back();
 
            // вызовите heapify-down на корневом узле
            heapify_down(0);
        }
        // ловим и печатаем исключение
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
        }
    }
 
    // Функция для возврата элемента с наивысшим приоритетом (присутствует в корне)
    int top()
    {
        try {
            // если в куче нет элементов, выбрасываем исключение
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");
            }
 
            // иначе возвращаем верхний (первый) элемент
            return A.at(0);        // или return A[0];
        }
        // ловим и печатаем исключение
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
        }
    }
};

int main()
{
    size_t count, weight, answer = 0;
    std::cin >> count;

    PriorityQueue heap;

    for (size_t i = 0; i < count; i++)
    {
        size_t value;
        std::cin >> value;
        heap.push(value);
    }

    std::cin >> weight;
    std::stack<size_t> st;

    while (!heap.empty())
    {
        size_t tmp_weight = weight;

        while (!heap.empty())
        {   
            if(tmp_weight >= heap.top())
            {
                st.push(heap.top());
                tmp_weight -= heap.top();
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

    return EXIT_SUCCESS;
}