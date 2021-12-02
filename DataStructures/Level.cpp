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

//creates a Level from a given array of players already arranged
void Level::ArrayToLevel(Player_ptr *level_array, int size)
{
    //assuming allocation of Group already happend
    int keys[size];
    for(int i=0; i< size; i++)
    {
        keys[i] = level_array[i]->getId();
    }
    players.ArrayToTree(level_array, keys, 0, size);
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

int Level::getSizeOfLevel() // number of players in this level
{
    return players.getSize();
}
int Level::getLevel() // returns what level is this
{
    return players.begin().getData()->getLevel();
}

// makes an arranged array (by id) of Player_ptr out of the tree
void Level::LevelToArray(Player_ptr *level_array)
{
    // assuming arrays have enough place for everyone and already inisialized
    int i = 0;
    for (Tree<Player_ptr>::const_iterator it = players.begin(); it != players.end(); ++it)
    {
        level_array[i] = it.getData();
        i++;
    }
}
