#ifndef TREE_H
#define TREE_H

#include <iostream>

using std::cout;
using std::endl;

template <class T>
class T23Node
{
    int index1, index2;
    int num_of_index;
    T23Node<T> *left;
    T23Node<T> *middle;
    T23Node<T> *right;
    T value;
public:
    T23Node();
    T23Node(T leaf_value);
    T23Node(const T23Node<T> &copy);
    ~T23Node() = default;
    const T &getData() const;
    bool isLeaf() const;
    void setIndex1(int new_index);
    void setIndex2(int new_index);
    T23Node<T> *getLeft() const;
    T23Node<T> *getMiddle() const;
    T23Node<T> *getRight() const;
    void setLeft(T23Node<T> *node);
    void setMiddle(T23Node<T> *node);
    void setRight(T23Node<T> *node);
};

template <class T>
class Tree23
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
    Tree23();
    Tree23(const Tree23<T> &copy);
    ~Tree23();
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

#endif //TREE_H