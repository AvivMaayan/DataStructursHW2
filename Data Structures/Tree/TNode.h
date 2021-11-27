#ifndef NODE_H_
#define NODE_H_

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
    explicit TNode(int key, T data, TNode<T> *parent = nullptr);
    TNode(const TNode<T> &copy) = delete;
    ~TNode() = default;
    const T &getData() const;
    const int getKey() const;
    const int getHeight() const;
    const int getBalance() const;
    void setData(T new_data);
    bool isLeaf() const;
    TNode<T> *getParent() const;
    TNode<T> *getLeft() const;
    TNode<T> *getRight() const;
    TNode<T> *getMin() const;
    void setParent(TNode<T> *node);
    void setLeft(TNode<T> *node);
    void setRight(TNode<T> *node);
    void updateBalance();
    void updateHeight();
};

template <class T>
TNode<T>::TNode(int key, T data, TNode<T> *parent)
    : height(0), balance(0), key(key), left(nullptr), right(nullptr), data(data), parent(parent)
{
}

template <class T>
void TNode<T>::updateBalance()
{
    int l_height = (left == nullptr) ? -1 : left->height;
    int r_height = (right == nullptr) ? -1 : right->height;
    balance = l_height - r_height;
}

template <class T>
void TNode<T>::updateHeight()
{
    int l_height = (left == nullptr) ? -1 : left->height;
    int r_height = (right == nullptr) ? -1 : right->height;
    height = std::max(l_height,r_height)+1;
}

template <class T>
const T &TNode<T>::getData() const
{
    return data;
}

template <class T>
const int TNode<T>::getKey() const
{
    return key;
}

template <class T>
const int TNode<T>::getHeight() const
{
    return height;
}

template <class T>
const int TNode<T>::getBalance() const
{
    return balance;
}

template <class T>
void TNode<T>::setData(T new_data)
{
    data = new_data;
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
TNode<T> *TNode<T>::getMin() const
{
    if (left == nullptr)
    {
        return this;
    }
    return left->getMin();
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

#endif // NODE_H_