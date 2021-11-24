#ifndef STACK_H
#define STACK_H

#include <iostream>

using std::cout;
using std::endl;

template <class T>
class Node
{
    T value;
    Node<T> *Next;
public:
    Node();
    Node(T value);
    Node(const Node<T> &copy);
    ~Node() = default;
    const T &getData() const;
    Node<T> *getNext() const;
    void setNext(Node<T> *node);
};

template <class T>
class Stack
{
private:
    Node<T>* head;
public:
    Stack();
    Stack(const Stack<T> &copy);
    ~Stack(); 
    void insert(T t);
    T top() const;
    void pop();
};

#endif //STACK_H