#include "Group.h"
#include "Player.h"

/**
 * @e o(log(n))
 * @param .
 * n is players in group
 *  assuming that player is new in the game, and input is valid
 * @return SUCCESS only
// REMEMER TO CHECK AND ADD IF NEDEED
// BAD ALLOC CHECK
 * */
Status Group::addPlayer(Id id, Player_ptr player)
{
    int level = player->getLevel();
    if (!levels.isExist(level)) // this level doesn't exist
    {
        levels.insert(level, make_shared<Level>());
    }
    // level_tree defintely exists by now
    Level_ptr players_tree = levels.getData(level);
    players_tree->addPlayer(id, player);
    num_of_players++;
    return S_SUCCESS;
}

void Group::addLevel(Level_ptr new_level)
{
    levels.insert(new_level->getLevel(), new_level);
}

// creates a Group from a given array of levels already arranged
void Group::ArrayToGroup(Level_ptr *level_array, int size, int sum_of_players)
{
    //assuming allocation of Group already happend
    int keys[size];
    for(int i=0; i< size; i++)
    {
        keys[i] = level_array[i]->getLevel();
    }
    levels.ArrayToTree(level_array, keys, 0, size - 1);
    num_of_players = sum_of_players;
}


/**
 * @e o(log(n))
 * @param .
 * n is players in group
 *  assuming input is valid, player exists in the game -> we know his level (from the Stack)
// going over all of the groups in game and calling this func
 * */
Status Group::removePlayer(Id id, Player_ptr player)
{
    int level = player->getLevel();
    Level_ptr players_tree = levels.getData(level);
    players_tree->removePlayer(id);
    num_of_players--;
    // checking if the level is now empty
    if (players_tree->isEmpty())
    {
        levels.remove(level);
    }
    return S_SUCCESS;
}

bool Group::isLevelExist(int level)
{
    return levels.isExist(level);
}

Level_ptr Group::getLevelPtr(int level)
{
    return levels.getData(level);
}



/**
 * @e o(1)
 * @param player pointer to the id of wanted player
 * the player is at the *highest* level in the group,
 * ,has the *lowest* id from those at the same level
 * @return SUCCESS *only* and id of player (as param) if was found, -1 otherwise
 * */
Status Group::getHighestLevel(Id *player)
{
    if (levels.isEmpty()) // there are no players in the group
    {
        *player = -1; // trash
        return S_SUCCESS;
    }
    Level_ptr highest = levels.reverseBegin().getData(); // highest level
    *player = highest->players.begin().getKey();         // lowest player
    return S_SUCCESS;
}

bool Group::isEmpty()
{
    return levels.isEmpty();
}

/**
 * @e o(n)
 * @param players_array pointer to the array of players arranged by level
 * @param num_of_players in player's array
 * players are arranged like so:
 * from highest to lowest level
 * within each level - lowest to highest id
 * @return SUCCESS if null array or just an array, ALLOCATION_ERROR otherwise
 * */
Status Group::getAllPlayersByLevel(Id **players_array, int *num_of_players)
{
    *num_of_players = getNumOfPlayers();
    if (*num_of_players == 0)
    {
        *players_array = NULL;
        return S_SUCCESS;
    }
    *players_array = (Id*)malloc(sizeof(Id) * *num_of_players);
    if (!*players_array)
    {
        return S_ALLOCATION_ERROR;
    }
    
    int i = 0;
    for (Tree<Level_ptr>::const_iterator levels_it = levels.reverseBegin(); levels_it != levels.end(); --levels_it)
    {
        for (Tree<Player_ptr>::const_iterator players_it = levels_it.getData()->players.begin(); 
        players_it != levels_it.getData()->players.end(); 
        ++players_it)
        {
            players_array[0][i] = players_it.getKey();
            i++;
        }
    }
    return S_SUCCESS;
}

int Group::getNumberOfLevels()
{
    return levels.getSize();
}

//makes an arranged array (by level) of Level_ptr out of the tree "levels"
void Group::GroupToArray(Level_ptr* level_array) 
{
    int i=0;
    for(Tree<Level_ptr>::const_iterator it = levels.begin(); it != levels.end(); ++it)
    {
        level_array[i] = it.getData(); 
        i++;
    }
}

int Group::getNumOfPlayers()
{
    return num_of_players;
}
