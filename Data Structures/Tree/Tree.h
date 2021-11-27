#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "TNode.h">

using std::cout;
using std::endl;

template <class T>
class Tree
{
private:
    TNode<T> *root;
    TNode<T> *left_most;
    TNode<T> *right_most;
    TNode<T>* RR(TNode<T>* not_balanced);
    TNode<T>* LL(TNode<T>* not_balanced);
    TNode<T>* RL(TNode<T>* not_balanced);
    TNode<T>* LR(TNode<T>* not_balanced);
    TNode<T> *next_bigger(TNode<T>* vertice);
    TNode<T> *next_smaller(TNode<T>* vertice);
    friend class const_iterator;

public:
    class const_iterator
    {
    private:
        TNode<T> *element;
        const_iterator(TNode<T> *node);
        TNode<T> *getNode() const;
        friend class Tree<T>;
        //void setElement(TNode<T> *node);
    public:
        const_iterator(const const_iterator &copy);
        ~const_iterator() = default;
        Tree<T>::const_iterator &operator=(const const_iterator &it);
        //Aviv:
        Tree<T>::const_iterator &operator++();
        Tree<T>::const_iterator &operator--();
        bool operator==(const const_iterator &it) const;
        bool operator!=(const const_iterator &it) const;
        const T &operator*() const;
    };
    Tree() : root(nullptr){};
    Tree(const Tree<T> &copy) = delete;
    ~Tree();

    //iterators for different traversels
    const_iterator &begin() const;
    const_iterator &end() const;
    //Aviv:
    const_iterator search(const T t) const;
    void insert(int key, const T t);
    void remove(int key); //remove a vertice by its key
    void remove(const const_iterator& iterator); //remove a vertice pointed by an iterator
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
TNode<T>* Tree<T>::next_bigger(TNode<T>* vertice)
{
    assert(vertice->getParent() != nullptr); //vertice can't be the root when getting here
    assert(vertice != right_most); //vertice can't be the biggest leaf when geting here
    TNode<T>* parent = vertice->getParent();
    if(parent->getLeft() == vertice) { //vertice is smaller than his parent
        return parent;
    }
    next_bigger(parent);
}

template <class T>
TNode<T>* Tree<T>::next_smaller(TNode<T>* vertice)
{
    assert(vertice->getParent() != nullptr); //vertice can't be the root when getting here
    assert(vertice != left_most); //vertice can't be the biggest leaf when geting here
    TNode<T>* parent = vertice->getParent();
    if(parent->getRight() == vertice) { //vertice is bigger than his parent
        return parent;
    }
    next_bigger(parent);
}

template <class T>
Tree<T>::const_iterator Tree<T>::search(const T t) const
{
}

template <class T>
void Tree<T>::insert(int key, const T t)
{
}

template <class T>
void Tree<T>::remove(int key)
{
}

template <class T>
void Tree<T>::remove(const const_iterator& iterator)
{
}
template <class T>
Tree<T>::const_iterator& Tree<T>::begin() const
{
    return const_iterator(left_most);
}

template <class T>
Tree<T>::const_iterator& Tree<T>::end() const
{
    return const_iterator(right_most);
}

#endif //TREE_H