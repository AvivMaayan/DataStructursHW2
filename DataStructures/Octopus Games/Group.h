#ifndef GROUP_H_
#define GROUP_H_

#include <iostream>

#include "../Exeptions/exeptions.h"
#include "../Tree/Tree.h"

using std::cout;
using std::endl;
using std::string;

typedef int id;
typedef Tree<id> level;

class Group
{
private:
    int group_id;
    Tree<level> players; //players is a tree: key = level of players, data = id of players at this level from the group

public:
    Group(id id);
    Group(const Group &group) = delete;
    ~Group() = default;
    int getGroup() const;
    StatusType addPlayer(int player);
    StatusType removePlayer(int player);




};

#endif //GROUP_H_