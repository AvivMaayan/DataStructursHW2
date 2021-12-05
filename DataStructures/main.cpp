#include "Tree.h"

int main()
{
    Tree<int> test_tree;
    for (int i = 0; i < 5; i++)
    {
        test_tree.insert(i,i);
    }
    test_tree.clearAll();
    return 0;
}