#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

class Group;

typedef shared_ptr<Group> Group_ptr;

class Player
{
private:
    int id;
    int level;
    Group_ptr group;

public:
    Player():id(0), level(-1), group(nullptr){}
    Player(int id, int level, Group_ptr group) : id(id), level(level), group(group) {}
    Player(const Player &copy) = default;
    ~Player() = default;
    int getId() const;
    int getLevel() const;
    Group_ptr getGroupPtr();
    void setGroup(Group_ptr new_group);
    void setLevel(int new_level);
    void printPlayer() const;
    bool operator==(const Player &compare) const;
    bool operator!=(const Player &compare) const;
};
#endif // PLAYER_H_
