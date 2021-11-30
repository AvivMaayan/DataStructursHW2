#ifndef GROUP_H_
#define GROUP_H_

#include <iostream>

#include "../Exeptions/exeptions.h"
#include "../Tree/Tree.h"
#include "Player.h"

using std::cout;
using std::endl;
using std::string;

class Group
{
private:
    int group_id;
    Tree< Tree<Player> > players; //players is a tree: key = level of the player, data = a tree of players at this level from the grou

public:
    Group(int id);
    Group(const Group &group) = delete;
    ~Group() = default;
    
};

#endif //GROUP_H_