#ifndef GROUP_H_
#define GROUP_H_

#include <iostream>

#include "../Tree/Tree.h"
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;

typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} Status;

class Player;

typedef int Id;
typedef shared_ptr<Player> Player_ptr;
typedef Tree<Player_ptr> Level;

class Group
{
private:
    //int group_id;
    Tree<Level> players; //players is a tree: key = level of players, data = pointer Players at this level from the group

public:
    //Group(Id id);
    Group() : players(){}
    Group(const Group &group) = delete;
    ~Group() = default;
    //int getGroup() const;
    Status addPlayer(Id id, Player_ptr player); 
    Status removePlayer(Id id, Player_ptr player);
    Status updateLevel(Id id, Player_ptr player, int increasement);
    Status getHighestLevel(Id* player); //get the lowest id of a player in the heighest level
    Status getAllPlayersByLevel(Id** players_array, int* num_of_players); //ids sorted low->high, levels high->low
};

#endif //GROUP_H_