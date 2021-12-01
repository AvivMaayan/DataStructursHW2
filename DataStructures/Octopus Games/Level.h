#ifndef LEVEL_H_
#define LEVEL_H_

#include <iostream>

#include "../Tree/Tree.h"
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;

typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} Status;

class Player;
typedef int Id;
typedef shared_ptr<Player> Player_ptr;


class Level
{
public:
    Tree<Player_ptr> players; //players is a tree: key = id of players, data = pointer Players at this level from the group
    Level() : players(){}
    Level(const Level &level) = delete;
    ~Level() = default;
    bool isEmpty();
    bool isPlayerExist(Id id);
    Player_ptr getPlayerPtr(Id id);
    Status addPlayer(Id id, Player_ptr player); 
    Status removePlayer(Id id);
};

#endif //LEVEL_H_