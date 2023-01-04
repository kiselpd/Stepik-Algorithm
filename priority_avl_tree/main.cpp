#include <iostream>
#include <stack>

template <typename T, typename Comparator = std::less<T>>
class PriorityAvlTree
{
    public:

    struct Node
    {
        Node(const T &data)
        : data(data), height(1), count(1), left(nullptr), right(nullptr)
        {
        }
        
        T data;
        size_t height;
        size_t count;
        Node *left;
        Node *right;
    };
    
    PriorityAvlTree() : root(nullptr) {}
    
    ~PriorityAvlTree()
    {
        destroyTree(root);
    }
    
    void Add(const T &data)
    {
        root = addInternal(root, data);
    }

    size_t GoDown(Node *ptr) const
    {
        return (ptr) ? (1 + std::max(this->GoDown(ptr->left), this->GoDown(ptr->left))) : (0);
    }

    size_t GetHeight() const
    {
        return GoDown(root);
    }

    bool Has(const T &data)
    {
        Node *tmp = root;
        while (tmp)
        {
            if (tmp->data == data)
            {
                return true;
            }
            else if (lessComp(tmp->data, data))
            {
                tmp = tmp->right;
            }
            else
            {
                tmp = tmp->left;
            }
        }
        return false;
    }

    size_t getIndex(T &value)
    {
        auto tmp = root;
        size_t index = root->count;

        while(tmp->data != value)
        {
            if(tmp->data < value)
                tmp = tmp->right;
            else
            {
                index -= (tmp->right)->count + 1;
                tmp = tmp->left;
            }
        }

        if(tmp->right)
            index -=(tmp->right)->count;

        return index;
    }
    
    void Delete(const T &data)
    {
        root = deleteInternal(root, data);
    }

    T kStatistics(size_t statistic)
    {
        Node* newNode = getStatistics(this->root, statistic);
        return newNode->data;
    }

    void DeleteIndex(size_t index)
    {
        Node* delete_node = getStatistics(this->root, index);
        root = deleteInternal(root, delete_node->data);
    }

private:
    Node *root;
    Comparator lessComp;

    Node* getStatistics(Node* node, size_t statistic)
    {
        if((!node->left && !node->right) || (getCount(node->left) == statistic))
           return node;

        if(getCount(node->left) > statistic)
            return getStatistics(node->left, statistic);

        return getStatistics(node->right, statistic - getCount(node->left) - 1);

    }

    void destroyTree(Node *node)
    {
        if (node)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    Node* deleteInternal(Node *node, const T &data)
    {
        if (!node)
            return nullptr;
        if (lessComp(node->data, data))
        {
            node->right = deleteInternal(node->right, data);
        }
        else if (lessComp(data, node->data))
        {
            node->left = deleteInternal(node->left, data);
        }
        else
        {
            Node *left = node->left;
            Node *right = node->right;
            
            delete node;

            if (!left && !right) 
				return nullptr;

			if (!left || getHeight(left) <= getHeight(right))
            {
                Node* min = doBalance(findAndRemoveMin(right, left));
                fixCount(min);
                return min;
            }
			if (!right || getHeight(left) > getHeight(right)) 
            {
                Node* max = doBalance(findAndRemoveMax(left, right));
                fixCount(max);
                return max;
            }        
        }

        node = doBalance(node);
        fixCount(node);

        return node;
    }

    Node* findMax(Node *node)
    {
        while(node->right)
            node = node->right;
        return node;
    }

    Node* removeMax(Node* node)
    {
        Node* newNode = node;
        std::stack<Node*> nodeStack;

        while(newNode->right)
        {
            nodeStack.push(newNode);
            newNode = newNode->right;
        }

        if(nodeStack.empty())
            return node->left;
            
        Node* tmp = newNode->left;

        while(!nodeStack.empty())
        {
            if(tmp)
            {
                tmp = doBalance(tmp);
                fixCount(tmp);
                nodeStack.top()->right = tmp;
            }
            else
                nodeStack.top()->right = nullptr;
            
            tmp = nodeStack.top();
            nodeStack.pop();
        }

        tmp = doBalance(tmp);
        fixCount(tmp);

        return tmp;
    }
    
    Node* findAndRemoveMax(Node* left, Node* right)
    {
        Node *max = findMax(left);
        max->left = removeMax(left);
        max->right = right;
        return max;
    }

    Node* findMin(Node *node)
    {
        while (node->left)
            node = node->left;
        return node;
    }

    Node* removeMin(Node *node)
    {
        Node* newNode = node;
        std::stack<Node*> nodeStack;

        while(newNode->left)
        {
            nodeStack.push(newNode);
            newNode = newNode->left;
        }

        if (nodeStack.empty())
            return node->right;

        Node *tmp = newNode->right;

        while(!nodeStack.empty())
        {
            if(tmp)
            {
                tmp = doBalance(tmp);
                fixCount(tmp);
                nodeStack.top()->left = tmp;
            }
            else
                nodeStack.top()->left = nullptr;
            
            tmp = nodeStack.top();
            nodeStack.pop();
        }

        tmp = doBalance(tmp);
        fixCount(tmp);

        return tmp;
    }

    Node* findAndRemoveMin(Node* right, Node* left)
    {
        Node *min = findMin(right);
        min->right = removeMin(right);
        min->left = left;
        return min;
    }

    Node* addInternal(Node *node, const T &data)
    {
        if (!node)
            return new Node(data);
        if (!lessComp(data, node->data))
        {
            node->right = addInternal(node->right, data);
        }
        else
        {
            node->left = addInternal(node->left, data);
        }

        node = doBalance(node);
        fixCount(node);

        return node;
    }

    size_t getHeight(Node *node)
    {
        return node ? node->height : 0;
    }
    
    void fixHeight(Node *node)
    {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    size_t getCount(Node* node)
    {  
		return node ? node->count : 0;
	}

    void fixCount(Node* node)
    { 
		if (node)
			node->count = getCount(node->left) + getCount(node->right) + 1;
	}
    
    Node* rotateLeft(Node *node)
    {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fixCount(node);
        fixHeight(node);
        fixCount(tmp);
        fixHeight(tmp);

        return tmp;
    }
    
    Node* rotateRight(Node *node)
    {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixCount(node);
        fixHeight(node);
        fixCount(tmp);
        fixHeight(tmp);

        return tmp;
    }
    
    int getBalance(Node *node)
    {
        return getHeight(node->right) - getHeight(node->left);
    }
    
    Node* doBalance(Node *node)
    {
        fixCount(node);
        fixHeight(node);

        switch (getBalance(node))
        {
            case 2:
            {
                if (getBalance(node->right) < 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            case -2:
            {
                if (getBalance(node->left) > 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            default:
                return node;
        }
    }
    
};

void solution()
{
    size_t count, count_value = 0;
    std::cin>>count;

    PriorityAvlTree<int> avl_tree;

    for (size_t i = 0; i < count; i++)
    {
        size_t operation;
        int value;

        std::cin >> operation >> value;

        if(operation == 1)
            {
                avl_tree.Add(value);
                count_value++;
                std::cout << count_value - avl_tree.getIndex(value) << " ";
            }
        else
        {
            count_value--;
            avl_tree.DeleteIndex(count_value - value);
        }
    }
}

int main(int argc, const char * argv[]) {

    solution();
    return EXIT_SUCCESS;
}
