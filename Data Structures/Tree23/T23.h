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
    friend class pre_iterator;
    friend class in_iterator;
    friend class post_iterator;

public:
    class pre_iterator;
    class in_iterator;
    class post_iterator;
    T23() : root(nullptr){};
    T23(const T23<T> &copy) = delete;
    ~T23();

    //iterators for different traversels (pre, in, post order)
    pre_iterator &begin() const; 
    pre_iterator &end() const;
    in_iterator &begin() const;
    in_iterator &end() const;
    post_iterator &begin() const;
    post_iterator &end() const;
    T23Node<T>* search(T t) const;

    void insert(T t);
    void remove(T t);
};

template <class T>
T23<T>::~T23()
{
    
}

#endif //TREE_H