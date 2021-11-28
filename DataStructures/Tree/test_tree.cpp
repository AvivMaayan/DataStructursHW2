#include <iostream>

#include <cassert>

#include "../Exeptions/exeptions.h"
#include "Tree.h"

using std::cout;
using std::endl;
using std::string;

#define TEST(num) cout << endl << "TEST " << (num) << endl;
#define THEWALL() { \
    tree.printTree(); \
    cout << endl << "++++++++++++++++++++++++++++++++++++++++++" << endl; }

int main()
{
    Tree<int> tree = Tree<int>(); 
    TEST(1.1)
    cout<< "Testing insert and search" <<endl;
    tree.insert(6,1);
    tree.insert(7,1);
    tree.insert(5,1);
    tree.insert(8,1);
    tree.insert(4,1);
    THEWALL();
    Tree<int>::const_iterator it = tree.search(8); //leaf search
    cout<< *it <<endl;
    it = tree.search(5); //root search
    cout<< *it <<endl;
    it = tree.search(1); //doesn't exist
    cout<< *it <<endl;

    TEST(1.2)
    cout<< "Testing insert" <<endl;
    THEWALL()
    tree.insert(1,1);
    THEWALL()
    tree.insert(3,2);
    THEWALL()
    tree.insert(0,3);
    THEWALL()
    tree.insert(4,2); //already there
    THEWALL()

    TEST(1.3)
    cout<< "Testing remove" <<endl;
    tree.remove(1);
    THEWALL()
    tree.remove(6);
    THEWALL()
    tree.remove(5);
    THEWALL()
    tree.remove(-2); //doesn't exist

    TEST(1.4)
    cout<< "Testing remove by it" <<endl;
    cout<<tree.isEmpty() <<endl;
    it = tree.search(0);
    tree.removeByIt(it);
    THEWALL()

    TEST(1.5)
    cout<< "Testing insert with rotations" <<endl;
    tree.insert(10,0);
    tree.insert(11,1);
    tree.insert(12,2);
    tree.insert(13,3);
    THEWALL()

    TEST(1.6)
    cout<< "Testing iterator ++" <<endl;
    it = tree.search(10);
    cout << *it << endl;
    it++;
    cout << *it << endl;
    it++;
    cout << *it << endl;
    it++;
    cout << *it << endl;
    it++; //nowhere to go
    cout << *it << endl;
    THEWALL()

    TEST(1.7)
    cout<< "Testing iterator --" <<endl;
    it--;
    cout << *it << endl;
    it--;
    cout << *it << endl;
    it = tree.search(3);
    it--;
    cout << *it << endl;








    
    return 0;
}
