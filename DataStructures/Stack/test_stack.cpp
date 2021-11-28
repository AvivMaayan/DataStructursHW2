#include <iostream>

#include <cassert>

#include "../Exeptions/exeptions.h"
#include "Stack.h"

using std::cout;
using std::endl;
using std::string;

#define TEST(num) cout << endl << "TEST " << (num) << endl;
#define THEWALL() { \
    stack.printStack(); \
    cout << endl << "++++++++++++++++++++++++++++++++++++++++++" << endl; }

int main()
{
    TEST("1.1")
    cout<< "Testing push:" <<endl;
    Stack<int> stack = Stack<int>();
    stack.push(1);
    THEWALL()
    stack.push(2);
    THEWALL()
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(6);
    stack.push(7);
    THEWALL()
    cout<< "expecting 7 6 5 4 3 2 1 ";

    TEST("1.2")
    cout<< "Testing pop:" <<endl;
    stack.pop();
    THEWALL()
    stack.pop();
    THEWALL()
    stack.pop();
    THEWALL()
    cout<< "expecting 4 3 2 1 ";

    TEST("1.3")
    cout << "Testing isEmpty" <<endl;
    cout<< stack.isEmpty() << endl;
    Stack<int> temp = Stack<int>();
    cout<< temp.isEmpty() << endl;

    TEST("1.4")
    cout<< "Testing Top:"<<endl;
    cout << stack.top() << endl;
    cout << "expecting 4"; 
    THEWALL()

    TEST("1.5")
    cout << "Testing pop & top again" <<endl;
    stack.pop();
    stack.pop();
    stack.pop();
    THEWALL()
    cout << "expecting 1" << endl;
    cout << stack.top() << endl;
    stack.pop();
    THEWALL()
    cout << "expect nothing" << endl;

    TEST("1.6")
    cout << "Testing on empty stack" <<endl;
    try{
        cout << stack.top() <<endl;
        cout << stack.pop() <<endl;
    }
    catch(Exception& e) {
        e.what();
    }
    
    return 0;
}
