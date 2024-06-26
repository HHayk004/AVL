#include "AVL.h"

int main()
{
    AVL<int> tree = {5, 1, 4, 2, 3, 6, 8, 7};

    tree.printTree();

    tree.printNode(tree.predecessor(tree.getRoot()));

    return 0;
}