#ifndef GAME_H_
#define GAME_H_
#include <iostream>

#include <cassert>

#include "Group.h"
#include "Player.h"

#define DOES_NOT_EXIST -1

using std::cout;
using std::endl;
using std::string;

/**
 * Level - is a tree of Player pointers. (usually, they are all in the same level) 
 * Group - is a tree of Levels, in which all of a Level's players are in the same level in the game.
 * 
 */

typedef shared_ptr<Group> Group_ptr;

class Game
{
private:
    Tree<Group_ptr> groups;
    Group levels; //all of the players form a group = key-level (int), data-Level(tree of players (id) in this level)
    Level players; //all of the players are "in" an abstract level = key-Id (int), data-level of the player(int)
    
    Group getGroup(int group_id); 
    int getLevel(Id PlayerID);
    Id GameHighestLevelPlayer(); //returns player on the highest level. if there are a few, returns the lowest id
    Status GameAddNewPlayer(Id PlayerID, int level); //adding a *new* player to the players tree. assuming that the player really is new
    Status GameRemovePlayer(Id PlayerID); //removing a player from the players tree
public:
    Game();
    ~Game() = default;
    
    //functions from Library1:
    Status AddGroup(int GroupID);
    Status AddPlayer(int PlayerID, int GroupID, int Level);
    Status RemovePlayer(int PlayerID);
    Status ReplaceGroup(int GroupID, int ReplacementID);
    Status IncreaseLevel(int PlayerID, int LevelIncrease);
    Status GetHighestLevel(int GroupID, int *PlayerID);
    Status GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers);
    Status GetGroupsHighestLevel(int numOfGroups, int **Players);
};
#endif 