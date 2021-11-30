#include <iostream>

#include <cassert>

#include "../Exeptions/exeptions.h"
#include "../Tree/Tree.h"
#include "../Stack/Stack.h"
#include "Group.h"
#include "library.h"

using std::cout;
using std::endl;
using std::string;

class Game
{
private:
    Tree<Group> groups;
    Tree<Id> players;
    Stack<int> max_level_players;
};