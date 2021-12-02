#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;

class Group;

typedef shared_ptr<Group> Group_ptr;

class Player
{
private:
    int level;
    Group_ptr group;
public:
    Player(int level, Group_ptr group) : level(level), group(group) {}
    Player(const Player &copy) = default;
    ~Player() = default;
    int getLevel() const;
    Group_ptr getGroupPtr();
    void setGroup(Group_ptr new_group);
    void setLevel(int new_level); 
    void printPlayer() const;
    bool operator==(const Player &compare) const;
    bool operator!=(const Player &compare) const;
};
#endif //PLAYER_H_
