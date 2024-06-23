#ifndef AVL_H
#define AVL_H

#include <utility>
#include <cmath>

template <typename T>
class AVL
{
private:
    class Node
    {
    public:
        Node (const T& val);
        ~Node() = defaut;

    private:
        Node* left;
        Node* right;
        T val;
    };

private:
    Node* root;

private:
    size_t getBF(Node* node);
    bool isBalanced(Node* node);

    Node* rotateL(Node* node);//
    Node* rotateR(Node* node);//
    Node* rotateRL(Node* node);//
    Node* rotateRR(Node* node);//

    void clearRec(Node* node);

    Node* insertRec(Node* node, const T& val);//
    Node* deleteRec(Node* node, const T& val);

public:
    AVL();
    AVL(const std::initializer_list<T>& list);
    
    size_t getHeight(Node* node);

    void clear() const;

    Node* insert(const T& val);
    Node* delete(const T& val);

    Node* search(const T& val);

    void printVal(Node* node) const;

    void printTree() const; // 
};

#include "AVL.hpp"
#endif