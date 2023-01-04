#include<iostream>
#include<vector>

enum bypass_type
{
    BFS,
    DFS
};

template<typename T>
struct Node
{
    T value;
    Node *right;
    Node *left;

    Node();
};

template <typename T>
Node<T>::Node() : right(nullptr), left(nullptr){};

template<typename T>
class BinaryTree
{
private:
    Node<T> *root;
    void delete_node(Node<T> *node);
    void BFS() const;
    void DFS(Node<T> *node) const;

public:
    BinaryTree();
    ~BinaryTree();

    void add(T value);
    void print(bypass_type t) const;
};

template<typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template<typename T>
void BinaryTree<T>::delete_node(Node<T> *node)
{
    if(node->right)
        this->delete_node(node->right);

    if(node->left)
        this->delete_node(node->left);

    delete node;
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
    if(root->right)
        this->delete_node(root->right);

    if(root->left)
        this->delete_node(root->left);

    delete root;
}

template<typename T>
void BinaryTree<T>::BFS() const
{
    if(!root)
        return;

    std::vector<Node<T>*> bfs_vec;
    size_t i = 0;

    bfs_vec.push_back(root);

    while (i < bfs_vec.size())
    {
        if(bfs_vec.at(i)->right)
            bfs_vec.push_back(bfs_vec.at(i)->right);

        if(bfs_vec.at(i)->left)
            bfs_vec.push_back(bfs_vec.at(i)->left);

        i++;
    }

    while(!bfs_vec.empty())
    {
        std::cout << (bfs_vec.back())->value << " ";
        bfs_vec.pop_back();
    }
}

template<typename T>
void BinaryTree<T>::DFS(Node<T> *node) const
{
    if(!node)
        return;

    if(node->left)
        this->DFS(node->left);

    if(node->right)
        this->DFS(node->right);

    std::cout << node->value << " ";
}

template<typename T>
void BinaryTree<T>::print(bypass_type t) const
{
    switch (t)
    {
    case bypass_type::BFS:
        if(root)
            this->BFS();

        std::cout << std::endl;
        break;

    case bypass_type::DFS:
        if(root)
            this->DFS(root);

        std::cout << std::endl;
        break;

    default:
        break;
    }
}

template<typename T>
void BinaryTree<T>::add(T value)
{
    Node<T> *new_node = new Node<T>;
    new_node->value = value;

    if(!root)
    {
        root = new_node;
        return;
    }

    auto tmp = root;

    while (true)
    {   
        if((tmp->value) > value)
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

void solution()
{
    size_t count;

    std::cin>>count;

    BinaryTree<int> tree;

    for (size_t i = 0; i < count; i++)
    {
        int value;
        std::cin>>value;

        tree.add(value);
    }

    tree.print(BFS);
}

int main()
{
    solution();

    return EXIT_SUCCESS;
}
