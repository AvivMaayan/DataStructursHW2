#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include "TNode.h"
#include <cassert>

using std::cout;
using std::endl;

template <class T>
class Tree
{
private:
    TNode<T> *root;
    TNode<T> *left_most;
    TNode<T> *right_most;
    TNode<T> *rotate(TNode<T> *not_balanced);
    TNode<T> *RR(TNode<T> *not_balanced);
    TNode<T> *LL(TNode<T> *not_balanced);
    TNode<T> *RL(TNode<T> *not_balanced);
    TNode<T> *LR(TNode<T> *not_balanced);
    TNode<T> *next_bigger(TNode<T> *vertice) const;
    TNode<T> *next_smaller(TNode<T> *vertice) const;
    //need to implement?
    //TNode<T> *get_rightest();
    //TNode<T> *get_leftest();
    friend class const_iterator;
    TNode<T> *internalSearch(TNode<T> *node, int key_to_find) const;
    TNode<T> *internalInsert(TNode<T> *node, int key_to_insert, const T data);
    TNode<T> *internalRemove(TNode<T> *node, int key_to_remove);
    void internalClear(TNode<T> *root);

public:
    class const_iterator;
    Tree();
    Tree(const Tree<T> &copy);
    ~Tree();
    const_iterator begin() const;
    const_iterator reverseBegin() const;
    const_iterator end() const;
    bool isEmpty() const;
    const_iterator search(const int key) const;
    void insert(int key, const T data);
    void remove(int key);                            // remove a vertice by its key
    void removeByIt(const const_iterator &iterator); // remove a vertice pointed by an iterator
    //to be deleted at the end:
    void printTree() const;
    void printTree(const std::string &prefix, const TNode<T> *node, bool isLeft) const;

    class const_iterator
    {
    private:
        const Tree<T> &tree;
        TNode<T> *element;
        TNode<T> *getNode() const;
        friend class Tree<T>;
        // void setElement(TNode<T> *node);
    public:
        const_iterator(TNode<T> *node, const Tree<T> &tree) : element(node), tree(tree) {};
        const_iterator(const const_iterator &copy) = default;
        ~const_iterator() = default;
        Tree<T>::const_iterator &operator=(const const_iterator &it);
        // Aviv:
        Tree<T>::const_iterator &operator++();
        Tree<T>::const_iterator &operator--();
        bool operator==(const const_iterator &it) const;
        bool operator!=(const const_iterator &it) const;
        const T &operator*() const;
    };
};
////////////////////////IMPLEMENTATION///////////////////////

//////// const_iterator ////////


/**template <class T>
Tree<T>::const_iterator ::const_iterator(const const_iterator &copy) 
{
    this->element = copy.element;
    this->tree = copy.tree;
}*/

template <class T>
typename Tree<T>::const_iterator &Tree<T>::const_iterator ::operator=(const const_iterator &it)
{
    this->element = it.element;
    return *this;
}

template <class T>
typename Tree<T>::const_iterator &Tree<T>::const_iterator ::operator++()
{
    if(*this == tree.reverseBegin()) {
        this->element = nullptr;
    }
    else if (this->element->getRight() != nullptr)
    { //the next bigger one is in the right sub-tree
        this->element = this->element->getRight()->getMin();
    }
    else
    {
        this->element = tree.next_bigger(this->element);
    }
    return *this;
}

template <class T>
typename Tree<T>::const_iterator &Tree<T>::const_iterator ::operator--()
{
     if(*this == tree.begin()) {
        this->element = nullptr;
    }
    else if (this->element->getLeft() != nullptr)
    { //the next smaller one is the left son
        this->element = this->element->getLeft()->getMax();
    }
    else
    {
        this->element = tree.next_smaller(this->element);
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
    if (this->element == nullptr)
    {
        throw Invalid_Input();
    }

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
Tree<T>::Tree() : root(), left_most(), right_most() {}

template <class T>
void Tree<T>::internalClear(TNode<T> *root)
{
    if (root != nullptr)
    {
        internalClear(root->getRight());
        internalClear(root->getLeft());
        delete root;
        root = nullptr;
    }
}

template <class T>
Tree<T>::~Tree()
{
    internalClear(root);
}

template <class T>
bool Tree<T>::isEmpty() const
{
    return root == nullptr;
}

template <class T>
TNode<T> *Tree<T>::LL(TNode<T> *not_balanced)
{
    //helpful definitions:
    TNode<T> *parent = not_balanced->getParent();
    TNode<T> *A = not_balanced->getLeft();
    TNode<T> *temp = A->getRight();
    //rotation:
    not_balanced->setLeft(temp);
    if (temp != nullptr)
    {
        temp->setParent(not_balanced);
    }
    A->setRight(not_balanced);
    not_balanced->setParent(A);
    //resetting the original parent of not_balanced
    if (parent != nullptr)
    {
        if (parent->getLeft() == not_balanced)
        { //not_balanced is the left son
            parent->setLeft(A);
        }
        else
        { //not_balanced is the right son
            parent->setRight(A);
        }
    }

    A->setParent(parent);
    //changing to new heights:
    /**if(A_orig_balance == 0) {
        not_balanced->setHeight(not_balanced->getHeight()-1); //lowering not_balanced by 1
        A->setHeight(A->getHeight()++);
    }
    else { //for sure A_orig_balance == 1
        not_balanced->height-=2;
    }
    A->calculate_update_balance();
    not_balanced->calculate_update_balance();*/
    not_balanced->updateHeight();
    not_balanced->updateBalance();
    A->updateHeight();
    A->updateBalance();
    return A;
}

template <class T>
TNode<T> *Tree<T>::
RR(TNode<T> *not_balanced)
{
    //helpful definitions:
    TNode<T> *parent = not_balanced->getParent();
    TNode<T> *A = not_balanced->getRight();
    TNode<T> *temp = A->getLeft();
    //rotation:
    not_balanced->setRight(temp);
    if (temp != nullptr)
    {
        temp->setParent(not_balanced);
    }
    A->setLeft(not_balanced);
    not_balanced->setParent(A);
    //resetting the original parent of not_balanced
    if (parent != nullptr)
    {
        if (parent->getLeft() == not_balanced)
        { //not_balanced is the left son
            parent->setLeft(A);
        }
        else
        { //not_balanced is the right son
            parent->setRight(A);
        }
    }
    A->setParent(parent);
    //changing to new heights:
    /**if(A_orig_balance == 0) {
        not_balanced->height++;
        A->height++;
    }
    else { //for sure A_orig_balance == -1
        not_balanced->height+=2;
    }
    A->calculate_update_balance();
    not_balanced->calculate_update_balance();*/
    not_balanced->updateHeight();
    not_balanced->updateBalance();
    A->updateHeight();
    A->updateBalance();
    return A;
}

template <class T>
TNode<T> *Tree<T>::LR(TNode<T> *not_balanced)
{
    TNode<T> *left_son = not_balanced->getLeft();
    RR(left_son);
    return LL(not_balanced);
}

template <class T>
TNode<T> *Tree<T>::RL(TNode<T> *not_balanced)
{
    TNode<T> *right_son = not_balanced->getRight();
    LL(right_son);
    return RR(not_balanced);
}

template <class T>
TNode<T> *Tree<T>::next_smaller(TNode<T> *vertice) const
{
    assert(vertice->getParent() != nullptr); //vertice can't be the root when getting here
    assert(vertice != left_most);            //vertice can't be the biggest leaf when geting here
    TNode<T> *parent = vertice->getParent();
    if (parent->getRight() == vertice)
    { //vertice is bigger than his parent
        return parent;
    }
    return next_smaller(parent);
}

template <class T>
TNode<T> *Tree<T>::next_bigger(TNode<T> *vertice) const
{
    //assert(vertice->getParent() != nullptr); //vertice can't be the root when getting here
    //assert(vertice != left_most);            //vertice can't be the biggest leaf when geting here
    TNode<T> *parent = vertice->getParent();
    if (parent->getLeft() == vertice)
    { //vertice is smaller than his parent
        return parent;
    }
    return next_bigger(parent);
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
    return not_balanced;
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
        return internalSearch(node->getRight(), key_to_find);
    }
    else
    {
        return internalSearch(node->getLeft(), key_to_find);
    }
}

template <class T>
typename Tree<T>::const_iterator Tree<T>::search(const int key) const
{
    return Tree<T>::const_iterator(internalSearch(root, key), *this);
}

template <class T>
TNode<T> *Tree<T>::internalInsert(TNode<T> *node, int key_to_insert, const T data)
{
    if (node == nullptr)
    {
        return new TNode<T>(key_to_insert, data);
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
            TNode<T> *new_right = internalInsert(node->getRight(), key_to_insert, data);
            new_right->setParent(node);
            node->setRight(new_right);
        }
        else
        {
            TNode<T> *new_left = internalInsert(node->getLeft(), key_to_insert, data);
            new_left->setParent(node);
            node->setLeft(new_left);
        }
    }
    return rotate(node);
}

template <class T>
void Tree<T>::insert(int key, const T data)
{
    root = internalInsert(root, key, data);
    left_most = root->getMin();   
    right_most = root->getMax();   
}

template <class T>
TNode<T> *Tree<T>::internalRemove(TNode<T> *node, int key_to_remove)
{
    if (node == nullptr)
        return nullptr;
    int key = node->getKey();
    if (key_to_remove == key)
    {
        if (node->getRight() != nullptr && node->getLeft() != nullptr) //node has 2 sons
        {
            const TNode<T> *next_node = node->getRight()->getMin();
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
            else
            //if (node->getLeft() == nullptr)
            {
                node = node->getRight();
            }
            if (node != nullptr)
            {
                node->setParent(tmpNode->getParent());
            }
            delete tmpNode;
        }
    }
    else if (key_to_remove > key)
    {
        TNode<T> *new_right = internalRemove(node->getRight(), key_to_remove);
        if (new_right != nullptr)
        {
            new_right->setParent(node);
        }
        node->setRight(new_right);
    }
    else
    {
        TNode<T> *new_left = internalRemove(node->getLeft(), key_to_remove);
        if (new_left != nullptr)
        {
            new_left->setParent(node);
        }
        node->setLeft(new_left);
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
typename Tree<T>::const_iterator Tree<T>::begin() const
{
    return Tree<T>::const_iterator(left_most, *this);
}

template <class T>
typename Tree<T>::const_iterator Tree<T>::reverseBegin() const
{
    return Tree<T>::const_iterator(right_most, *this);
}

template <class T>
typename Tree<T>::const_iterator Tree<T>::end() const
{
    return Tree<T>::const_iterator(nullptr, *this);
}

template <class T>
void Tree<T>::printTree() const
{
    printTree("", root, false);
}

template <class T>
void Tree<T>::printTree(const std::string &prefix, const TNode<T> *node, bool isLeft) const
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "'--");

        // print the value of the node
        std::cout << node->getKey() << "," << node->getData() << std::endl;

        // enter the next tree level - left and right branch
        printTree(prefix + (isLeft ? "|   " : "    "), node->getLeft(), true);
        printTree(prefix + (isLeft ? "|   " : "    "), node->getRight(), false);
    }
}

#endif // TREE_H_