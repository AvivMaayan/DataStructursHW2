#ifndef GROUP_H_
#define GROUP_H_

#include <iostream>

#include "../Tree/Tree.h"
#include "library1.h"

using std::cout;
using std::endl;
using std::string;

typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} Status;

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
    Status addPlayer(Id player, int level); 
    Status removePlayer(Id player, int level);
    Status updateLevel(Id player, int level, int increasement);
    Status getHighestLevel(Id* player); //get the lowest id of a player in the heighest level
    Status getAllPlayersByLevel(Id** players_array, int* num_of_players); //ids sorted low->high, levels high->low
};

#endif //GROUP_H_