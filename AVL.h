#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <utility>
#include <cmath>
#include <queue>

template <typename T>
class AVL
{
private:
    class Node
    {
    public:
        Node(const T& val);
        ~Node() = default;

    private:
        Node* left;
        Node* right;
        T val;

        friend class AVL;
    };

private:
    Node* root;

private:
    long long getBF(Node* node);
    //bool isBalanced(Node* node);

    Node* rotateR(Node* node);
    Node* rotateL(Node* node);
    Node* rotateRL(Node* node);
    Node* rotateLR(Node* node);

    void clearRec(Node* node);

    Node* insertRec(Node* node, const T& val);
    Node* deleteRec(Node* node, const T& val);//

public:
    AVL();
    AVL(const std::initializer_list<T>& list);
    
    ~AVL();

    size_t getHeight(Node* node);

    void clear();

    Node* insert(const T& val);
    Node* deleteNode(const T& val);

    Node* search(const T& val);

    void printVal(Node* node) const;

    void printTree() const;
};

#include "AVL.hpp"
#endif