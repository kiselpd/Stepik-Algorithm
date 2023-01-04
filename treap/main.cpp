#include<iostream>

template<typename T>
struct Node
{
    T value;
    Node<T> *left;
    Node<T> *right;

    Node();
};

template<typename T>
Node<T>::Node() : left(nullptr), right(nullptr) {}

template<typename T>
class BinaryTree
{
private:
    Node<T> *root_;

    void deleteNode(Node<T> *ptr);
    size_t findDepth(Node<T> *ptr) const;

public:
    void add(T value);
    bool has(T value) const;
    size_t getDepth() const;

    BinaryTree();
    ~BinaryTree();
};

template<typename T>
void BinaryTree<T>::deleteNode(Node<T> *ptr)
{
    if(ptr->left)
        this->deleteNode(ptr->left);
    
    if(ptr->right)
        this->deleteNode(ptr->right);

    delete ptr;
}

template<typename T>
size_t BinaryTree<T>::findDepth(Node<T> *ptr) const
{
    return (ptr) ? (1 + std::max(this->findDepth(ptr->left), this->findDepth(ptr->right))) : (0);
}

template<typename T>
size_t BinaryTree<T>::getDepth() const
{
    return this->findDepth(root_);
}

template<typename T>
BinaryTree<T>::BinaryTree() : root_(nullptr){}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
    if(root_)
        this->deleteNode(root_);
}

template<typename T>
void BinaryTree<T>::add(T value)
{
    Node<T> *new_node = new Node<T>;
    new_node->value = value;

    if(!root_)
    {
        root_ = new_node;
        return;
    }

    auto tmp = root_;
    size_t tmp_depth = 1;

    while(true)
    {
        if (tmp->value > value)
        {
            if(tmp->left)
                tmp = tmp->left;
            else
            {
                tmp->left = new_node;
                break;
            }
        }
        else
        {
            if(tmp->right)
                tmp = tmp->right;
            else
            {
                tmp->right = new_node;
                break;
            }
        }
    }
}

template<typename T>
bool BinaryTree<T>::has(T value) const
{
    auto tmp = root_;

    while(tmp)
    {
        if(tmp->value > value)
            tmp = tmp->left;
        else if(tmp->value < value)
            tmp = tmp->left;
        else
            return true;
    }

    return false;
}

template<typename T>
struct NodeWithKey
{
    T value;
    NodeWithKey<T> *left;
    NodeWithKey<T> *right;
    size_t key;
    NodeWithKey(T value, size_t key);
};

template<typename T>
NodeWithKey<T>::NodeWithKey(T value, size_t key) : left(nullptr), right(nullptr), value(value), key(key) {}

template<typename T>
class Treap
{
private:
    NodeWithKey<T> *root_;

    void deleteNode(NodeWithKey<T> *ptr);
    size_t findDepth(NodeWithKey<T> *ptr) const;
    void split(NodeWithKey<T> *currentNode, T value, NodeWithKey<T> *&left, NodeWithKey<T> *&right);
    NodeWithKey<T> *merge(NodeWithKey<T> *left, NodeWithKey<T> *right);

public:
    Treap();
    ~Treap();
    size_t getDepth() const;
    void add(T value, size_t key);
};

template<typename T>
Treap<T>::Treap() : root_(nullptr) {}

template<typename T>
void Treap<T>::deleteNode(NodeWithKey<T> *ptr)
{
    if(ptr->left)
        this->deleteNode(ptr->left);
    
    if(ptr->right)
        this->deleteNode(ptr->right);

    delete ptr;
}

template<typename T>
Treap<T>::~Treap()
{
    if(root_)
        this->deleteNode(root_);
}

template<typename T>
size_t Treap<T>::findDepth(NodeWithKey<T> *ptr) const
{   
        return (ptr) ? (1 + std::max(this->findDepth(ptr->left), this->findDepth(ptr->right))) : (0);
}

template<typename T>
size_t Treap<T>::getDepth() const
{
    return this->findDepth(root_);
}

template<typename T>
void Treap<T>::split(NodeWithKey<T> *currentNode, T value, NodeWithKey<T> *&left, NodeWithKey<T> *&right)
{
    if(!currentNode)
        left = right = nullptr;
    else if(currentNode->value <= value)
    {
        this->split(currentNode->right, value, currentNode->right, right);
        left = currentNode;
    }
    else
    {
        this->split(currentNode->left, value, left, currentNode->left);
        right = currentNode;
    }
}

template<typename T>
NodeWithKey<T>* Treap<T>::merge(NodeWithKey<T> *left, NodeWithKey<T> *right)
{
    if((!left) || (!right))
        return (!left) ? (right) : (left);

    if(left->key > right->key)
    {
        left->right = this->merge(left->right, right);
        return left;
    }

    right->left = this->merge(left, right->left);
    return right;
}

template<typename T>
void Treap<T>::add(T value, size_t key) 
{
    NodeWithKey<T> *tmp = root_;
    NodeWithKey<T> *pred = nullptr;

    NodeWithKey<T> *new_node = new NodeWithKey<T>(value, key);

    if(!root_)
    {
        root_ = new_node;
        return;
    }

    while(tmp->key >= new_node->key)
    {
        pred = tmp;
        if (tmp->value > new_node->value)
        {
            if(tmp->left)
                tmp = tmp->left;
            else
            {
                tmp->left = new_node;
                return;
            }
        }
        else
        {
            if(tmp->right)
                tmp = tmp->right;
            else
            {
                tmp->right = new_node;
                return;
            }
        }
    }

    this->split(tmp, new_node->value, new_node->left, new_node->right);


    if(!pred)
        root_ = new_node;
    else if(value<=pred->value)
        pred->left = new_node;
    else 
        pred->right = new_node;
        
}

void solution()
{
    size_t count;

    std::cin >> count;

    BinaryTree<int> b_tree;
    Treap<int> t_tree;

    for (size_t i = 0; i < count; i++)
    {
        int value, key;
        std::cin >> value >> key;

        b_tree.add(value);
        t_tree.add(value, key);
    }

    std::cout << abs((int)b_tree.getDepth() - (int)t_tree.getDepth())<< std::endl;
}

int main()
{
    solution();
    return EXIT_SUCCESS;
}