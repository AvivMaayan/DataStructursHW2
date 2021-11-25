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
        //nitai:
        void RR(const TNode<T>* not_balanced);
        void LL(const TNode<T>* not_balanced);
        void RL(const TNode<T>* not_balanced);
        void LR(const TNode<T>* not_balanced);

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
    const_iterator *search(const T t) const;
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
    //this->element = this->element->getNext();
    return *this;
}

template <class T>
typename Tree<T>::const_iterator &Tree<T>::const_iterator ::operator--()
{
    //this->element = this->element->getNext();
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
TNode<T> *Tree<T>::search(const T t) const
{
}

template <class T>
void Tree<T>::insert(const T t)
{
}

template <class T>
void Tree<T>::remove(T t)
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