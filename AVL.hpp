template <typename T>
AVL<T>::AVL() : root(nullptr) {}

template <typename T>
AVL<T>::AVL(const std::initializer_list<T>& list) : root(nullptr)
{
    for (auto elem : list)
    {
        insert(elem);        
    }
}

template <typename T>
AVL<T>::~AVL()
{
    clear();
}

template <typename T>
void AVL<T>::clear()
{
    clearRec(root);
    root = nullptr;
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

    size_t leftH = getHeight(node->left);
    size_t rightH = getHeight(node->right);

    return std::max(leftH, rightH) + 1;
}

template <typename T>
long long AVL<T>::getBF(Node* node)
{
    return getHeight(node->left) - getHeight(node->right);
}

// template <typename T>
// bool AVL<T>::isBalanced(Node* node)
// {
//     return abs(bf(node)) <= 1;
// }

template <typename T>
typename AVL<T>::Node* AVL<T>::rotateL(Node* node)
{
    if (node == root)
    {
        root = node->right;
    }

    Node* tmp = node->right->left;
    node->right->left = node;

    Node* ret = node->right;
    node->right = tmp;

    return ret;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rotateR(Node* node)
{
    if (node == root)
    {
        root = node->left;
    }

    Node* tmp = node->left->right;
    node->left->right = node;

    Node* ret = node->left;
    node->left = tmp;

    return ret;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rotateLR(Node* node)
{
    node->left = rotateL(node->left);
    return rotateR(node);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rotateRL(Node* node)
{
    node->right = rotateR(node->right);
    return rotateL(node);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::insert(const T& val)
{
    if (!root)
    {
        root = insertRec(root, val);
        return root;
    }

    return insertRec(root, val);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::insertRec(Node* node, const T& val)
{
    if (!node)
    {
        return new Node(val);
    }

    if (node->val < val)
    {
        node->right = insertRec(node->right, val);
    }

    else if (node->val > val)
    {
        node->left = insertRec(node->left, val);
    }

    else
    {
        return node;
    }

    long long bf = getBF(node);
    if (bf > 1)
    {
        if (getBF(node->left) == 1)
        {
            return rotateR(node);
        }

        else
        {
            return rotateLR(node);
        }
    }

    if (bf < -1)
    {
        if (getBF(node->right) == -1)
        {
            return rotateL(node);
        }

        else
        {
            return rotateRL(node);
        }
    }
    
    return node;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::deleteNode(const T& val)
{
    if (root && root->val == val)
    {
        root = deleteRec(root, val);
        return root;
    }

    return deleteRec(root, val);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::deleteRec(Node* node, const T& val)
{
    if (!node)
    {
        return node;
    }

    if (node->val < val)
    {
        node->right = deleteRec(node->right, val);
    }

    else if (node->val > val)
    {
        node->left = deleteRec(node->left, val);
    }

    else
    {
        if (node->left)
        {
            Node* prev = nullptr;
            Node* tmp = node->left;
            
            if (!tmp->right)
            {
                tmp->right = node->right;
                delete node;

                return tmp;
            }
            
            while (tmp->right)
            {
                prev = tmp;
                tmp = tmp->right;
            }

            prev->right = nullptr;

            tmp->left = node->left;
            tmp->right = node->right;

            delete node;

            return tmp;
        }

        else 
        {
            Node* ret = node->right;

            delete node;

            return ret;
        }
    }

    //printTree();

    long long bf = getBF(node);
    if (bf > 1)
    {
        if (getBF(node->left) == 1)
        {
            return rotateR(node);
        }

        else
        {
            return rotateLR(node);
        }
    }

    if (bf < -1)
    {
        if (getBF(node->right) == -1)
        {
            return rotateL(node);
        }

        else
        {
            return rotateRL(node);
        }
    }

    return node;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::search(const T& val)
{
    Node* node = root;
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

template <typename T>
void AVL<T>::printTree() const // printing tree (levelOrder + endl + nullptr nodes)
{
	int count = 0; // current count of nodes
	int n = 1; // level nodes count
	bool check = false; // check for not nullptr nodes
	std::queue<Node*> roots; // same mean as in level order
	if (root) // if tree isn't empty, push m_root to roots and initialize count
	{
        std::cout << ":";
		roots.push(root);
		count = 1;
	}

	while (count) // cycle while there are valid nodes
	{
		Node* root = roots.front(); // root to roots first value
		if (root) // if root is valid
		{
			check |= (root->left || root->right); // for finding valid node
			roots.push(root->left); // pushing the nodes
			roots.push(root->right);
			std::cout << root->val << ':'; // printing nodes value
		}

		else // printing ' '
		{
			roots.push(nullptr); // for printing tree in appropriate way
			roots.push(nullptr);
			std::cout << " :";
		}

		--count; // decrease the count of nodes
		if (!count) // if count = 0, check if there are any valid nodes that wasn't printed
		{
			if (!check) // if there aren't break from cycle
			{
				break;
			}
				
			check = false; // refresh check value

			std::cout << std::endl << ':'; // for output clearity
				
			count = 2 * n; // nodes count in current level
			n *= 2; // for next count initialization
		}

		roots.pop(); // removing root from roots
	}

    std::cout << std::endl; // for output clearity
}
//corman 12 chapter