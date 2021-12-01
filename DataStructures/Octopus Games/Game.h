#ifndef GAME_H_
#define GAME_H_
#include <iostream>

#include <cassert>

#include "Group.h"

#define DOES_NOT_EXIST -1

using std::cout;
using std::endl;
using std::string;

class Game
{
private:
    Tree<Group> groups;
    Tree<Level> players; // key-level (int), data-Level(tree of players (id) in this level)
Group getGroup(int group_id); 
    //int getLevel(Id player) {return (players.isExist(player)) ? players.getData(player) : DOES_NOT_EXIST;};
    Id GameHighestLevelPlayer(); //returns player on the highest level. if there are a few, returns the lowest id
    Status GameAddNewPlayer(Id player, int level); //adding a *new* player to the players tree. assuming that the player really is new
    Status GameRemovePlayer(Id player); //removing a player from the players tree  
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