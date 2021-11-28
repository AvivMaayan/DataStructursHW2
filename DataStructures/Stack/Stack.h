#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "../Exeptions/exeptions.h"

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
    Stack(const Stack<T> &copy) = default;
    ~Stack();
    bool isEmpty() const;
    void push(T t);
    T top() const;   
    T pop();
    void printStack() const;
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
    this->value = T(value);
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
Stack<T>::~Stack()
{
    while(!isEmpty())
    {
        this->pop();
    }
    delete head; 
}

template <class T>
bool Stack<T>::isEmpty() const
{
    return head->getNext() == nullptr;
}

template <class T>
void Stack<T>::push(T t)
{
    Node<T>* temp = this->head->getNext();
    Node<T>* curr = new Node<T>(t);
    if(!curr)
    {
        throw Allocation_Error();
        return;
    }
    this->head->setNext(curr);
    curr->setNext(temp);
}

template <class T>
T Stack<T>::top() const
{
    if(isEmpty())
    {
        throw Empty_Structure();
        return NULL;
    }
    return head->getNext()->getData();
}

template <class T>
T Stack<T>::pop() 
{
    if(isEmpty())
    {
        throw Empty_Structure();
        return NULL;
    }
    Node<T>* to_delete = head->getNext();
    T to_return = to_delete->getData();
    head->setNext(to_delete->getNext());
    delete to_delete;
    return to_return;
}

template <class T>
void Stack<T>::printStack() const {
    Node<T>* iterator = this->head->getNext();
    while(iterator != nullptr){
        cout << iterator->getData() << " ";
        iterator = iterator->getNext();
    }
    cout << endl;
}

#endif //STACK_H