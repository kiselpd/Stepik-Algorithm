#include <iostream>
#include <vector>

const size_t INITIAL_CAPACITY = 8;
const double MAX_ALPHA = 0.75;

enum typeCell
{
    NIL,
    DEL,
    KEY
};

template<typename T>
struct HTitem
{
    T item;
    typeCell type;

    HTitem() : type(NIL) {}
};

class GornerStringHasher
{
public:
    GornerStringHasher(unsigned int prime = 71) : prime(prime) {}
    
    size_t operator()(const std::string &str) const
    {
        size_t hash = 0;

        for (size_t i = 0; i < (size_t)str.size(); i++)
        {
            hash = hash * prime + str[i];
        }
        return hash;
    }
private:
    unsigned int prime;
};

template <typename T, typename Hasher>
class HashTable
{
private:
    std::vector<HTitem<T>> table;
    size_t size;
    Hasher hasher;

    void grow()
    {
        size_t new_size = table.size() * 2;
        std::vector<HTitem<T>> oldTable = std::move(table);
        std::vector<HTitem<T>> newTable(new_size);
        table = std::move(newTable);

        for (size_t i = 0; i < oldTable.size(); i++)
            if(oldTable[i].type == KEY)
                this->Add(oldTable[i].item);
    }

public:
    HashTable(size_t initial_capacity = INITIAL_CAPACITY) : table(initial_capacity), size(0){}

    bool Delete(const T& key)
    {
        size_t y = this->hasher(key);

        for (size_t i = 0; i < table.size(); i++)
        {
            size_t hash = y % this->table.size();

            if (this->table[hash].type == NIL)
                return false;

            if((this->table[hash].type == KEY) && (this->table[hash].item == key))
                {
                    this->table[hash].type = DEL;
                    this->size--;
                    return true;
                }

            y += i + 1;
        }

        return false;
    }

    bool Has(const T& key) const
    {
        size_t y = this->hasher(key);

        for (size_t i = 0; i < table.size(); i++)
        {
            size_t hash = y % this->table.size();

            if(this->table[hash].type==NIL)
                return false;

            if((this->table[hash].type==KEY) && (this->table[hash].item==key))
                return true;

            y += i + 1;
        }
        
        return false;
    }

    bool Add(const T& key)
    {
        if (size > table.size() * MAX_ALPHA)
        {
            grow();
        }

        size_t y = this->hasher(key);
        int first_del = -1;
        for (size_t i = 0; i < table.size(); i++)
        {
            size_t hash = y % this->table.size();

            if((this->table[hash].type == DEL) && (first_del == -1))
            {
                first_del = hash;
                y += i + 1;
                continue;
            }

            if(this->table[hash].type == NIL)
            {
                if(first_del == -1)
                {
                    this->table[hash].type = KEY;
                    this->table[hash].item = key;
                }
                else
                {
                    this->table[first_del].type = KEY;
                    this->table[first_del].item = key;
                }

                size++;
                return true;
            }

            if(this->table[hash].type == KEY)
            {
                if(this->table[hash].item == key)
                    return false;
                else
                {
                    y += i + 1;
                    continue;
                }
            }

            y += i + 1;
        }
        
        this->table[first_del].type = KEY;
        this->table[first_del].item = key;
        size++;
        return true;
    }
};

void solution()
{
    HashTable<std::string, GornerStringHasher> table;
    char op;
    std::string key;
    
        while (std::cin >> op >> key)
    {
        switch (op)
        {
            case '+':
            {
                std::cout << (table.Add(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '-':
            {
                std::cout << (table.Delete(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '?':
            {
                std::cout << (table.Has(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
        }
    }
}

int main()
{
    solution();

    return EXIT_SUCCESS;
}