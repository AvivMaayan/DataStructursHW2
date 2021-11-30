#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

using std::cout;
using std::endl;

class Player
{
private:
    int id;
    int level;
public:
    Player(int id);
    Player(int id, int level);
    Player(const Player &copy);
    ~Player() = default;
    int getId() const;
    int getLevel() const;
    void setLevel(int new_level); 
    void printPlayer() const;
    bool operator==(const Player &compare) const;
    bool operator!=(const Player &compare) const;
};
////////////////////////IMPLEMENTATION///////////////////////

Player::Player(int id): id(id), level(1) {}

Player::Player(int id, int level): id(id), level(level) {}

Player::Player(const Player &copy) 
{
    id = copy.id;
    level = copy.level;
}

int Player::getId() const
{
    return id;
}

int Player::getLevel() const
{
    return level;
}

void Player::setLevel(int new_level)
{
    this->level = new_level;
}

void Player::printPlayer() const
{
    cout << "PLAYER:" << endl;
    cout << "id = " << id << endl;
    cout << "level = " << level << endl;
}

bool Player::operator==(const Player &compare) const
{
    return id == compare.id;
}

bool Player::operator!=(const Player &compare) const
{
    return !(*this == compare);
}



#endif //PLAYER_H_
