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
    Group levels;  // all of the players form a group = key-level (int), data-Level(tree of players (id) in this level)
    Level players; // all of the players are "in" an abstract level = key-Id (int), data-level of the player(int)

    /*
    --------------Not being used--------------
    Group getGroup(int group_id);
    int getLevel(Id PlayerID);
    Id GameHighestLevelPlayer();                     // returns player on the highest level. if there are a few, returns the lowest id
    Status GameAddNewPlayer(Id PlayerID, int level); // adding a *new* player to the players tree. assuming that the player really is new
    Status GameRemovePlayer(Id PlayerID);            // removing a player from the players tree
    */
    int getNumberOfLevels();
    void ArrayToGroup(Level_ptr *level_array, int size, Group_ptr result); // creates a Group from a given array of levels already arranged
    int MergeGroupArrays(Level_ptr *group1, Level_ptr *group2, int size1, int size2, Level_ptr *result);
    void MergeGroups(int origID, int replaceID); // merging groups into a new group (removing old ones)
    void MergeLevelsToSameGroup(Level_ptr level1, Level_ptr level2, Level_ptr result); // merging 2 Levels into a large arranged by id Level
    void MergePlayersOfSameLevel(Player_ptr *level1, Player_ptr *level2, int size1, int size2, Player_ptr *result); // merging arrays created in LevelToArray into a large arranged array
    void ArrayToLevel(Player_ptr *level_array, int size, Level_ptr result); // creates a Level from a given array of players already arranged
    void UpdateGroupPtr(Level_ptr *level_array, int size, Group_ptr new_group); 

public:
    Game();
    ~Game() = default;

    // functions from Library1:
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