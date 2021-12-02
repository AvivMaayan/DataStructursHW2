#ifndef GROUP_H_
#define GROUP_H_

#include <iostream>

#include "Level.h"
class Player;
typedef shared_ptr<Level> Level_ptr;

class Group
{
private:
    Tree<Level_ptr> levels; // levels is a tree: key = level of players, data = pointer Players at this level from the group

public:
    Group() : levels() {}
    Group(const Group &group) = delete;
    ~Group() = default;
    bool isLevelExist(int level);
    bool isEmpty();
    Level_ptr getLevelPtr(int level);
    Status addPlayer(Id id, Player_ptr player);
    void addLevel(Level_ptr new_level); //dangerous func, only used once in the code!
    Status removePlayer(Id id, Player_ptr player);
    Status updateLevel(Id id, Player_ptr player, int increasement);
    Status getHighestLevel(Id *player);                                   // get the lowest id of a player in the heighest level
    Status getAllPlayersByLevel(Id **players_array, int *num_of_players); // ids sorted low->high, levels high->low
    int getNumberOfLevels();
    void GroupToArray(Level_ptr *level_array);                              // makes an arranged array (by level) of Level_ptr out of the tree "levels"
};

#endif // GROUP_H_