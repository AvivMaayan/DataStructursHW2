#ifndef GAME_H_
#define GAME_H_
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
    Tree<Level> players; // key-level (int), data-Level(tree of players (id) in this level)
public:
    Game();
    ~Game();
    Group getGroup(int group_id); 
    //int getLevel(Id player) {return (players.isExist(player)) ? players.getData(player) : DOES_NOT_EXIST;};
    Id GameHighestLevelPlayer(); //returns player on the highest level. if there are a few, returns the lowest id
    StatusType GameAddNewPlayer(Id player, int level); //adding a *new* player to the players tree. assuming that the player really is new
    StatusType GameRemovePlayer(Id player); //removing a player from the players tree
    

    
};
#endif 