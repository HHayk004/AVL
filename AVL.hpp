template <typename T>
AVL<T>::AVL() : root(nullptr) {}

template <typename T>
AVL<T>::AVL(const std::initializer_list<T>& list)
{
    head = new Node(list.begin());

    for (auto it = list.begin() + 1; it != list.end(); ++it)
    {
        insert(*it);        
    }
}

template <typename T>
AVL<T>::~AVL()
{
    clearRec(head);
}

template <typename T>
void AVL<T>::clear()
{
    clearRec(head);
}

template <typename T>
void AVL<T>::clearRec(Node* node)
{
    if(node)
    {
        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }
}

template <typename T>
AVL<T>::Node::Node(const T& val) : left(nullptr), right(nullptr), val(val){}


template <typename T>
size_t AVL<T>::getHeight(Node* node)
{
    if (!node)
    {
        return 0;
    }

    size_t left = getHeight(node->left);
    size_t right = getHeight(node->right);

    return std::max(left, right) + 1;
}

template <typename T>
size_t AVL<T>::getBF(Node* node)
{
    return getHeifht(node->left) - getHeight(node->right);
}

template <typename T>
bool AVL<T>::isBalanced(Node* node)
{
    return abs(bf(node)) <= 1;
}

template <typename T>
Node* AVL<T>::rotateL(Node* node)
{
    // return nullptr;
}

template <typename T>
Node* AVL<T>::rotateR(Node* node)
{
    if (node == head)
    {
        head = node->left;
    }

    Node* tmp = node->left->right;
    node->left->right = node;

    Node* ret = node->left;
    node->left = node->left->right;

    return ret;
}

template <typename T>
Node* AVL<T>::rotateLR(Node* node)
{
    return rotateR(rotateL(node));
}

template <typename T>
Node* AVL<T>::rotateRL(node* node)
{
    return rotateL(rotateR(node));
}

template <typename T>
Node* AVL<T>::insert(const T& val)
{
    return insertRec(head, val);
}

template <typename T>
Node* AVL<T>::insertRec(Node* node, const T& val)
{
    if (!node)
    {
        return new Node(val);
    }

    if (node->val < val)
    {
        node->right = insertRec(node->right, val);
    }

    else
    {
        node->left = insertRec(node->left, val);
    }

    size_t bf = getBF(node);
    if (bf > 1)
    {
        // rotatenery
    }

    if (bf < -1)
    {
        // rotatenery
    }
    //
}

template <typename T>
Node* delete(const T& val)
{
    return deleteRec(head, val);
}

template <typename T>
Node* deleteRec(Node* node, const T& val)
{
    //
}

template <typename T>
Node* search(const T& val)
{
    Node* node = head;
    while (node && node->val != val)
    {
        if (node->val < val)
        {
            node = node->right;
        }

        else
        {
            node = node->left;
        }
    }

    return node;
}

template <typename T>
void AVL<T>::printVal(Node* node) const
{
    std::cout << node->val << std::endl;
}
//corman 12 chapter