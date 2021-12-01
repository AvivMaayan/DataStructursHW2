#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

using std::cout;
using std::endl;

class Group;

class Player
{
private:
    int level;
    Group *group;
public:
    Player(int level, Group *group) : level(level), group(group) {}
    Player(const Player &copy) = default;
    ~Player() = default;
    int getLevel() const;
    Group * getGroupPtr();
    void setGroup(Group* new_group);
    void setLevel(int new_level); 
    void printPlayer() const;
    bool operator==(const Player &compare) const;
    bool operator!=(const Player &compare) const;
};
////////////////////////IMPLEMENTATION///////////////////////
int Player::getLevel() const
{
    return level;
}

Group * Player::getGroupPtr()
{
    return group;
}

void Player::setLevel(int new_level)
{
    this->level = new_level;
}

void Player::setGroup(Group* new_group)
{
    this->group = new_group;
}

void Player::printPlayer() const
{
    cout << "PLAYER:" << endl;
    cout << "level = " << level << endl;
    cout << "group = ?" << endl;
}
#endif //PLAYER_H_
