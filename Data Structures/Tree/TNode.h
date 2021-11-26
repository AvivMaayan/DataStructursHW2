#ifndef NODE_23_
#define NODE_23_

template <class T>
class TNode
{
private:
    int key;
    int height;
    int balance; 
    TNode<T> *parent;
    TNode<T> *left;
    TNode<T> *right;
    T data;

public:
    TNode() = delete;
    explicit TNode(int key, T data, TNode<T>* parent = nullptr);
    TNode(const TNode<T> &copy) = delete;
    ~TNode() = default;
    const T &getData() const;
    const T &getKey() const;
    bool isLeaf() const;
    TNode<T> *getParent() const;
    TNode<T> *getLeft() const;
    TNode<T> *getRight() const;
    void setParent(TNode<T> *node);
    void setLeft(TNode<T> *node);
    void setRight(TNode<T> *node);
    int calculate_update_balance();
};

template <class T>
TNode<T>::TNode(int key, T data, TNode<T>* parent)
    :height(0), balance(0), key(key), left(nullptr), right(nullptr), data(data), parent(parent)
{
}

template <class T>
const T &TNode<T>::getData() const
{
    return data;
}

template <class T>
const T &TNode<T>::getKey() const
{
    return key;
}

template <class T>
bool TNode<T>::isLeaf() const
{
    return left == nullptr && right == nullptr;
}

template <class T>
TNode<T> *TNode<T>::getParent() const
{
    return parent;
}

template <class T>
TNode<T> *TNode<T>::getLeft() const
{
    return left;
}


template <class T>
TNode<T> *TNode<T>::getRight() const
{
    return right;
}

template <class T>
void TNode<T>::setParent(TNode<T> *node)
{
    parent = node;
}

template <class T>
void TNode<T>::setLeft(TNode<T> *node)
{
    left = node;
}

template <class T>
void TNode<T>::setRight(TNode<T> *node)
{
    right = node;
}

template <class T>
int TNode<T>::calculate_update_balance()
{
    balance = left->height - right->height
    return balance;
}

#endif