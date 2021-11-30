#include <iostream>

#include <cassert>

#include "../Exeptions/exeptions.h"
#include "../Tree/Tree.h"
#include "../Stack/Stack.h"
#include "Group.h"
#include "library.h"

#define DOES_NOT_EXISTS -1

using std::cout;
using std::endl;
using std::string;

class Game
{
private:
    Tree<Group> groups;
    Tree<int> players; // key-id, T-level
    Stack<int> max_level_players;
public:
    int getLevel(Id player) {return (players.isExists(player)) ? players.getData(player) : DOES_NOT_EXISTS;}; 
};