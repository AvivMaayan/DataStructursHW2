#include <iostream>

#include <cassert>

#include "../Exeptions/exeptions.h"
#include "../Tree/Tree.h"
#include "../Stack/Stack.h"
#include "Group.h"
#include "library.h"

#define DOES_NOT_EXIST -1

using std::cout;
using std::endl;
using std::string;

class Game
{
private:
    Tree<Group> groups;
    Tree<int> players; // key-id, data-level (int)
    Stack<int> max_level_players; //not a good idea :(
    Id max_player; //player in the highest level


public:
    int getLevel(Id player) {return (players.isExist(player)) ? players.getData(player) : DOES_NOT_EXIST;}; 
};