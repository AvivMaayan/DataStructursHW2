#ifndef GROUP_H_
#define GROUP_H_

#include <iostream>

#include "library.h"
#include "../Tree/Tree.h"

using std::cout;
using std::endl;
using std::string;

typedef int Id;
typedef Tree<Id> Level;

class Group
{
private:
    int group_id;
    Tree<Level> players; //players is a tree: key = level of players, data = id of players at this level from the group

public:
    Group(Id id);
    Group(const Group &group) = delete;
    ~Group() = default;
    int getGroup() const;
    StatusType addPlayer(Id player, int level); 
    StatusType removePlayer(Id player, int level);
    StatusType updateLevel(Id player, int level, int increasement);
    StatusType getHighestLevel(Id* player); //get the lowest id of a player in the heighest level
    StatusType getAllPlayersByLevel(Id** players_array, int* num_of_players); //ids sorted low->high, levels high->low
};

#endif //GROUP_H_