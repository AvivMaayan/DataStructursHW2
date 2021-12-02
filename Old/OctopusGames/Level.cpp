#include "Level.h"
#include "Player.h"

Player_ptr Level::getPlayerPtr(Id id)
{
    return players.getData(id);
}

/**
 * @e o(log(n))
 * @param .
 * n is players in group
 *  assuming and input is valid
 * @return SUCCESS only
// REMEMER TO CHECK AND ADD IF NEDEED
// BAD ALLOC CHECK
 * */
Status Level::addPlayer(Id id, Player_ptr player)
{
    players.insert(id, player);
    return S_SUCCESS;
}

/**
 * @e o(log(n))
 * @param .
 * n is players in group
 *  assuming input is valid, player exists in the game -> we know his level (from the Stack)
// going over all of the groups in game and calling this func
 * */
Status Level::removePlayer(Id id)
{
    players.remove(id);
    return S_SUCCESS;
}

bool Level::isEmpty()
{
    return players.isEmpty();
}

bool Level::isPlayerExist(Id id)
{
    return players.isExist(id);
}