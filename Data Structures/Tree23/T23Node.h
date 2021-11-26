#ifndef NODE_23_
#define NODE_23_

template <class T>
class T23Node
{
private:
    int key1, key2;
    int num_of_keys;
    T23Node<T> *parent;
    T23Node<T> *left;
    T23Node<T> *middle;
    T23Node<T> *right;
    T data;

public:
    T23Node() = delete;
    explicit T23Node(int key, T leaf_value);
    T23Node(const T23Node<T> &copy) = delete;
    ~T23Node() = default;
    const T &getData() const;
    bool isLeaf() const;
    void setKey1(int new_key);
    void setKey2(int new_key);
    T23Node<T> *getParent() const;
    T23Node<T> *getLeft() const;
    T23Node<T> *getMiddle() const;
    T23Node<T> *getRight() const;
    void setParent(T23Node<T> *node);
    void setLeft(T23Node<T> *node);
    void setMiddle(T23Node<T> *node);
    void setRight(T23Node<T> *node);
};

template <class T>
T23Node<T>::T23Node(int key, T leaf_value)
    : key1(key), num_of_keys(1), left(nullptr), middle(nullptr), right(nullptr), data(leaf_value)
{
}

template <class T>
const T &T23Node<T>::getData() const
{
    return data;
}

template <class T>
bool T23Node<T>::isLeaf() const
{
    return num_of_keys == 1;
}

template <class T>
void T23Node<T>::setKey1(int new_key)
{
    key1 = new_key;
}

template <class T>
void T23Node<T>::setKey2(int new_key)
{
    key2 = new_key;
}

template <class T>
T23Node<T> *T23Node<T>::getParent() const
{
    return parent;
}

template <class T>
T23Node<T> *T23Node<T>::getLeft() const
{
    return left;
}

template <class T>
T23Node<T> *T23Node<T>::getMiddle() const
{
    return middle;
}

template <class T>
T23Node<T> *T23Node<T>::getRight() const
{
    return right;
}

template <class T>
void T23Node<T>::setParent(T23Node<T> *node)
{
    parent = node;
}

template <class T>
void T23Node<T>::setLeft(T23Node<T> *node)
{
    left = node;
}

template <class T>
void T23Node<T>::setMiddle(T23Node<T> *node)
{
    middle = node;
}

template <class T>
void T23Node<T>::setRight(T23Node<T> *node)
{
    right = node;
}

#endif