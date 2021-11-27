#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include "TNode.h"

using std::cout;
using std::endl;

template <class T>
class Tree
{
private:
    TNode<T> *root;
    // left_most and right_most needs to be on TNode
    // OR- Tree getMin()/Max() func
    TNode<T> *left_most;
    TNode<T> *right_most;
    /// I am assuming that Rotation functions will return the new root
    TNode<T> *rotate(TNode<T> *not_balanced);
    TNode<T>* RR(TNode<T>* not_balanced);
    TNode<T>* LL(TNode<T>* not_balanced);
    TNode<T>* RL(TNode<T>* not_balanced);
    TNode<T>* LR(TNode<T>* not_balanced);
    TNode<T> *next_bigger(TNode<T>* vertice);
    TNode<T> *next_smaller(TNode<T>* vertice);
    friend class const_iterator;
    TNode<T> *internalSearch(TNode<T> *node, int key_to_find) const;
    TNode<T> *internalInsert(TNode<T> *node, int key_to_insert, const T data);
    TNode<T> *internalRemove(TNode<T> *node, int key_to_remove);

public:
    class const_iterator
    {
    private:
        TNode<T> *element;
        const_iterator(TNode<T> *node);
        TNode<T> *getNode() const;
        friend class Tree<T>;
        // void setElement(TNode<T> *node);
    public:
        const_iterator(const const_iterator &copy);
        ~const_iterator() = default;
        Tree<T>::const_iterator &operator=(const const_iterator &it);
        // Aviv:
        Tree<T>::const_iterator &operator++();
        Tree<T>::const_iterator &operator--();
        bool operator==(const const_iterator &it) const;
        bool operator!=(const const_iterator &it) const;
        const T &operator*() const;
    };
    Tree() : root(nullptr){};
    Tree(const Tree<T> &copy) = delete;
    ~Tree();

    // iterators for different traversels
    const_iterator &begin() const;
    const_iterator &end() const;
    // Aviv:
    bool isEmpty() const;
    const_iterator &search(const int key) const;
    void insert(int key, const T data);
    void remove(int key);                            // remove a vertice by its key
    void removeByIt(const const_iterator &iterator); // remove a vertice pointed by an iterator
};
////////////////////////IMPLEMENTATION///////////////////////

//////// const_iterator ////////
template <class T>
Tree<T>::const_iterator ::const_iterator(TNode<T> *node)
{
    this->element = node;
}

template <class T>
Tree<T>::const_iterator ::const_iterator(const const_iterator &copy)
{
    this->element = copy.element;
}



template <class T>
typename Tree<T>::const_iterator &Tree<T>::const_iterator ::operator=(const const_iterator &it)
{
    this->element = it.element;
    return *this;
}

template <class T>
typename Tree<T>::const_iterator &Tree<T>::const_iterator ::operator++()
{
    if(this->element == right_most) { //biggest element, no where to continue
        return nullptr;
    }
    if(this->element->getRight() != nullptr) { //the next bigger one is the right son
        this->element = this->element->getRight();
    }
    else{
        this->element = next_bigger(this->element);
    }
    return *this;
}

template <class T>
typename Tree<T>::const_iterator &Tree<T>::const_iterator ::operator--()
{
    if(this->element == left_most) { //smallest element, no where to continue
        return nullptr;
    }
    if(this->element->getLeft() != nullptr) { //the next smaller one is the left son
        this->element = this->element->getLeft();
    }
    else{
        this->element = next_smaller(this->element);
    }
    return *this;
}
template <class T>

bool Tree<T>::const_iterator ::operator==(const const_iterator &it) const
{
    if (this->element == it.element)
    {
        return true;
    }
    return false;
}

template <class T>
bool Tree<T>::const_iterator ::operator!=(const const_iterator &it) const
{
    return !(*this == it);
}

template <class T>
const T &Tree<T>::const_iterator ::operator*() const
{
    return this->element->getData();
}

/**template <class T>
void Tree<T>::const_iterator ::setElement(TNode<T> *node)
{
    this->element = node;
}*/

template <class T>
TNode<T> *Tree<T>::const_iterator ::getNode() const
{
    return this->element;
}

//////// Tree ////////

template <class T>
Tree<T>::~Tree()
{
}

template <class T>
bool Tree<T>::isEmpty() const
{
    return root == nullptr;
}

template <class T>
TNode<T>* Tree<T>::LL(TNode<T>* not_balanced)
{
    //helpful definitions:
    TNode<T>* parent = not_balanced->getParent();
    TNode<T>* A = not_balanced->getLeft();
    TNode<T>* temp = A->getRight();
    //keeping A's original balance factor:
    int A_orig_balance = A->balance;
    //rotation:
    not_balanced->setLeft(temp);
    temp->setParent(not_balanced);
    A->setRight(not_balanced);
    not_balanced->setParent(A);
    //resetting the original parent of not_balanced
    if(parent->getLeft() == not_balanced){ //not_balanced is the left son
        parent->setLeft(A);
    }
    else { //not_balanced is the right son
        parent->setRight(A);
    }
    A->setParent(parent);
    //changing to new heights:
    if(A_orig_balance == 0) {
        not_balanced->height--;
        A->height++;
    }
    else { //for sure A_orig_balance == 1
        not_balanced->height-=2;
    }
    A->calculate_update_balance();
    not_balanced->calculate_update_balance();
    return A;
}

template <class T>
TNode<T>* Tree<T>::RR(TNode<T>* not_balanced)
{
    //helpful definitions:
    TNode<T>* parent = not_balanced->getParent();
    TNode<T>* A = not_balanced->getRight();
    TNode<T>* temp = A->getRight();
    //keeping A's original balance factor:
    int A_orig_balance = A->balance;
    //rotation:
    not_balanced->setRight(temp);
    temp->setParent(not_balanced);
    A->setLeft(not_balanced);
    not_balanced->setParent(A);
    //resetting the original parent of not_balanced
    if(parent->getLeft() == not_balanced){ //not_balanced is the left son
        parent->setLeft(A);
    }
    else { //not_balanced is the right son
        parent->setRight(A);
    }
    A->setParent(parent);
    //changing to new heights:
    if(A_orig_balance == 0) {
        not_balanced->height++;
        A->height++;
    }
    else { //for sure A_orig_balance == -1
        not_balanced->height+=2;
    }
    A->calculate_update_balance();
    not_balanced->calculate_update_balance();
    return A;
}

template <class T>
TNode<T>* Tree<T>::LR(TNode<T>* not_balanced)
{
    TNode<T>* left_son = not_balanced->getLeft();
    LL(left_son);
    return RR(not_balanced);
}

template <class T>
TNode<T>* Tree<T>::RL(TNode<T>* not_balanced)
{
    TNode<T>* right_son = not_balanced->getRight();
    RR(right_son);
    return LL(not_balanced);
}

template <class T>
TNode<T> *Tree<T>::rotate(TNode<T> *not_balanced)
{
    if (not_balanced == nullptr)
        return nullptr;
    not_balanced->updateHeight();
    not_balanced->updateBalance();
    if (not_balanced->getBalance() == 2)
    {
        if (not_balanced->getLeft()->getBalance() == -1)
        {
            return LR(not_balanced);
        }
        else
            return LL(not_balanced);
    }
    else if (not_balanced->getBalance() == -2)
    {
        if (not_balanced->getRight()->getBalance() == 1)
        {
            return RL(not_balanced);
        }
        else
            return RR(not_balanced);
    }
}

template <class T>
TNode<T> *Tree<T>::internalSearch(TNode<T> *node, int key_to_find) const
{
    if (node == nullptr)
        return nullptr;
    int key = node->getKey();
    if (key_to_find == key)
        return node;
    else if (key_to_find > key)
    {
        return internalSearch(node->right, key_to_find);
    }
    else
    {
        return internalSearch(node->left, key_to_find);
    }
}

template <class T>
Tree<T>::const_iterator &Tree<T>::search(const int key) const
{
    return Tree<T>::const_iterator(internalSearch(root, key));
}

template <class T>
TNode<T> *Tree<T>::internalInsert(TNode<T> *node, int key_to_insert, const T data)
{
    if (node == nullptr)
    {
        return new TNode(key_to_insert, data);
    }
    else
    {
        int key = node->getKey();
        if (key_to_insert == key)
        {
            // Do we want to enable information updating?//
            node->setData(data);
        }
        else if (key_to_insert > key)
        {
            node->setRight(internalInsert(node->getRight(), key_to_insert, data));
        }
        else
        {
            node->setLeft(internalInsert(node->getLeft(), key_to_insert, data));
        }
    }
    return rotate(node);
}

template <class T>
void Tree<T>::insert(int key, const T data)
{
    root = internalInsert(root, key, data);
}

template <class T>
TNode<T> *Tree<T>::internalRemove(TNode<T> *node, int key_to_remove)
{
    if (node == nullptr)
        return nullptr;
    int key = node->getKey();
    if (key_to_remove == key)
    {
        if (node->getRight() != nullptr && node->getLeft() != nullptr)
        {
            TNode<T> *next_node = node->getRight()->getMin();
            node->setKey(next_node->getKey());
            node->setData(next_node->getData());
            node->setRight(internalRemove(node->getRight(), next_node->getKey()));
            // rotate?
        }
        else
        {
            TNode<T> *tmpNode = node;
            if (node->getRight() == nullptr)
            {
                node = node->getLeft();
            }
            else if (node->getLeft() == nullptr)
            {
                node = node->getRight();
            }
            delete tmpNode;
        }
    }
    else if (key_to_remove > key)
    {
        node->setRight(internalRemove(node->getRight(), key_to_remove));
    }
    else
    {
        node->setLeft(internalRemove(node->getLeft(), key_to_remove));
    }
    return rotate(node);
}

template <class T>
void Tree<T>::remove(int key)
{
    root = internalRemove(root, key);
}

template <class T>
void Tree<T>::removeByIt(const Tree<T>::const_iterator &iterator)
{
    //Leaving this out for now
}

template <class T>
Tree<T>::const_iterator &Tree<T>::begin() const
{
    return const_iterator(left_most);
}

template <class T>
Tree<T>::const_iterator &Tree<T>::end() const
{
    return const_iterator(right_most);
}

#endif // TREE_H_