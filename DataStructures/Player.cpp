#include "Player.h"

int Player::getLevel() const
{
    return level;
}

Group_ptr Player::getGroupPtr()
{
    return Group_ptr(group);
}

int Player::getId() const
{
    return id;
}

void Player::setLevel(int new_level)
{
    this->level = new_level;
}

void Player::setGroup(Group_ptr new_group)
{
    this->group = (W_Group_ptr)new_group;
}

void Player::printPlayer() const
{
    cout << "PLAYER:" << endl;
    cout << "level = " << level << endl;
    cout << "group = ?" << endl;
}
