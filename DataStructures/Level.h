#ifndef LEVEL_H_
#define LEVEL_H_

#include <iostream>
#include "Tree.h"

using std::cout;
using std::endl;
using std::string;

typedef enum
{
    S_SUCCESS = 0,
    S_FAILURE = -1,
    S_ALLOCATION_ERROR = -2,
    S_INVALID_INPUT = -3
} Status;

class Player;
typedef int Id;
typedef shared_ptr<Player> Player_ptr;

class Level
{
public:
    Tree<Player_ptr> players; // players is a tree: key = id of players, data = pointer Players at this level from the group
    Level() : players() {}
    Level(const Level &level) = delete;
    ~Level() = default;
    bool isEmpty();
    bool isPlayerExist(Id id);
    Player_ptr getPlayerPtr(Id id);
    Status addPlayer(Id id, Player_ptr player);
    Status removePlayer(Id id);
};

#endif // LEVEL_H_