#include <iostream>

#include <cassert>

#include "../Exeptions/exeptions.h"
#include "Tree.h"

using std::cout;
using std::endl;
using std::string;

#define TEST(num) cout << endl \
                       << "TEST " << (num) << endl;
#define THEWALL()                                                     \
    {                                                                 \
        tree.printTree();                                             \
        cout << endl                                                  \
             << "++++++++++++++++++++++++++++++++++++++++++" << endl; \
    }
#define THEWALL2()                                                     \
    {                                                                 \
        tree2.printTree();                                             \
        cout << endl                                                  \
             << "++++++++++++++++++++++++++++++++++++++++++" << endl; \
    }
int main()
{
    Tree<int> tree = Tree<int>();
    TEST(1.1)
    cout << "Testing insert and search" << endl;
    tree.insert(6, 6);
    tree.insert(7, 7);
    tree.insert(5, 5);
    tree.insert(8, 8);
    tree.insert(4, 4);
    THEWALL();
    Tree<int>::const_iterator it = tree.search(8); //leaf search
    cout << it.getData() << endl;
    it = tree.search(5); //root search
    cout << it.getData() << endl;
    try
    {
        it = tree.search(1); //doesn't exist
    }
    catch (Exception e)
    {
        cout << e.what() << endl;
    }

    TEST(1.2)
    cout << "Testing insert" << endl;
    THEWALL()
    tree.insert(1, 1);
    THEWALL()
    tree.insert(3, 3);
    THEWALL()
    tree.insert(0, 0);
    THEWALL()
    tree.insert(4, 4); //already there
    THEWALL()
    tree.getData(4) =5;
    THEWALL()

    TEST(1.3)
    cout << "Testing remove" << endl;
    tree.remove(1);
    THEWALL()
    tree.remove(6);
    THEWALL()
    tree.remove(5);
    THEWALL()
    tree.remove(-2); //doesn't exist

    TEST(1.4)
    cout << "Testing remove by it" << endl;
    cout << tree.isEmpty() << endl;
    it = tree.search(0);
    tree.removeByIt(it);
    THEWALL()

    TEST(1.5)
    cout << "Testing insert with rotations" << endl;
    tree.insert(10, 100);
    tree.insert(11, 101);
    tree.insert(12, 102);
    tree.insert(13, 103);
    THEWALL()

    TEST(1.6)
    cout << "Testing iterator ++" << endl;
    for (auto it = tree.begin(); it != tree.end(); ++it)
    {
        cout << it.getData() << endl;
    }
    cout << "Testing iterator --" << endl;
    for (auto it = tree.reverseBegin(); it != tree.end(); --it)
    {
        cout << it.getData() << endl;
    }
    cout << "--------------" << endl;
    it = tree.search(7);
    cout << it.getData() << endl;
    ++it;
    cout << it.getData() << endl;
    ++it;
    cout << it.getData() << endl;
    ++it;
    cout << it.getData() << endl;

    try
    {
        it = tree.search(13);
        ++it; //nowhere to go
        cout << it.getData() << endl;
    }
    catch (Exception e)
    {
        cout << "nowhere to go" << endl;
    }

    THEWALL()

    TEST(1.7)
    cout << "Testing iterator --" << endl;
    it = tree.reverseBegin();
    --it;
    cout << it.getData() << endl;
    --it;
    cout << it.getData() << endl;
    it = tree.search(3);
    --it;
    cout << it.getData() << endl;


    TEST(1.8)
    Tree<int> tree2 = Tree<int>();
    tree2.insert(5,5);
    tree2.insert(4,4);
    tree2.insert(6,6);
    tree2.insert(2,2);
    THEWALL2();
    tree2.insert(3,3);
    THEWALL2();

    return 0;
}
