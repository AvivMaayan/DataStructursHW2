#ifndef TREE_23_H
#define TREE_23_H

#include <iostream>
#include "T23Node.h">

using std::cout;
using std::endl;

template <class T>
class T23
{
private:
    T23Node<T> *root;
    T23Node<T> *left_most;
    T23Node<T> *right_most;
    friend class const_iterator;

public:
    class const_iterator;
    T23() : root(nullptr){};
    T23(const T23<T> &copy) = delete;
    ~T23();

    //iterators for different traversels
    const_iterator &begin() const; 
    const_iterator &end() const;

    T23Node<T>* search(T t) const;
    void insert(T t) const;
    void remove(T t);
};

template <class T>
T23<T>::~T23()
{

}

template <class T>
T23Node<T>* T23<T>::search(T t) const
{
    
}

template <class T>
void T23<T>::insert(T t) const
{
    
}

template <class T>
void T23<T>::remove(T t)
{
    
}

#endif //TREE_23_H