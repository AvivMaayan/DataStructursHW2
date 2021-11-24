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
    Node<T> *head;

public:
    Stack();
    Stack(const Stack<T> &copy);
    ~Stack();
    void insert(T t);
    T top() const;   
    T pop();
};
/**
 * implementation
 * **/
///////////////Node//////////////
template <class T>
Node<T>::Node()
{
    this->Next = nullptr;
}

template <class T>
Node<T>::Node(T value)
{
    value = T(value);
    this->Next = nullptr;
}

template <class T>
Node<T>::Node(const Node<T> &copy)
{
    value = T(copy.value);
    this->Next = nullptr;
}

template <class T>
const T &Node<T>::getData() const
{
    return value;
}

template <class T>
Node<T> *Node<T>::getNext() const
{
    return Next;
}

template <class T>
void Node<T>::setNext(Node<T> *node)
{
    this->Next = node;
}

///////////////STACK//////////////
template <class T>
Stack<T>::Stack()
{
    this->head = new Node<T>();
}

template <class T>
Stack<T>::Stack()
{
    this->head = new Node<T>();
}

template <class T>
Stack<T>::Stack(const Stack<T> &copy)
{
    this->head = new Node<T>(copy->head);
}

template <class T>
Stack<T>::~Stack()
{
    while(this->head->getNext() != nullptr)
    [
        this.pop();
    ]
    delete head; 
}

template <class T>
void Stack<T>::insert(T t)
{
    Node<T> temp = this->head->getNext();
    Node<T> curr = new Node<T>(t);
    this->head->setNext(curr);
    curr.setNext(temp);
}

template <class T>
T Stack<T>::top() const
{
    if(head->getNext() == nullptr)
        return NULL;
    return head->getNext()->value;
}

template <class T>
T Stack<T>::pop() 
{
    if(head->getNext() == nullptr)
        return NULL;
    Node<T>* to_delete = head->getNext();
    T to_return = to_delete->value;
    head->setNext(to_delete->getNext());
    delete to_delete;
    return to_return;
}

#endif //STACK_H