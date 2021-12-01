#include "Group.h"
#include "Player.h"

//Group::Group(Id id) : group_id(id), players() {}

/*
int Group::getGroup() const
{
    return group_id;
}
*/

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
    if (!players.isExist(level)) // this level doesn't exist
    {
        players.insert(level);
    }
    // level_tree defintely exists by now
    Level players_tree = players.getData(level);
    players_tree.insert(id, player);
    return SUCCESS;
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
    Level players_tree = players.getData(level);
    players_tree.remove(id);
    //checking if the level is now empty
    if (players_tree.isEmpty())
    {
        players.remove(level);
    }
    return SUCCESS;
}

/**
 * @e o(log(n))
 * @param .
 * n is players in group
 * assuming valid input, player exists -> we know his level (from the Stack)
 * WHAT ABOUT BAD ALLOC CHECK?
 * */

/* 
Status Group::updateLevel(Id id, Player_ptr player, int increasement)
{
    int level = player->getLevel();
    Level players_tree = players.getData(level);
    players_tree.remove(id);
    return addPlayer(id, player, level + increasement);
}
*/

/**
 * @e o(1)
 * @param player pointer to the id of wanted player
 * the player is at the *highest* level in the group,
 * ,has the *lowest* id from those at the same level
 * @return SUCCESS *only* and id of player (as param) if was found, -1 otherwise
 * */
Status Group::getHighestLevel(Id *player)
{
    if (players.isEmpty()) //player is not in group
    {
        *player = -1; //trash
        return SUCCESS;
    }
    Level highest = players.reverseBegin().getData(); //highest level
    *player = highest.begin().getKey();//lowest player
    return SUCCESS;
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
    *num_of_players = players.getSize();
    if (*num_of_players==0)
    {
        players_array=NULL;
        return SUCCESS;
    }
    *players_array = (Id*)malloc(sizeof(Id) * *num_of_players); 
    if (!*players_array)
    {
        return ALLOCATION_ERROR;
    }
    int i = 0;
    for (Tree<Level>::const_iterator levels_it = players.reverseBegin(); levels_it != players.end(); --levels_it)
    {
        Level level_tree = levels_it.getData();
        for (Level::const_iterator players_it = level_tree.begin(); players_it != level_tree.end(); ++players_it)
        {
            *players_array[i] = players_it.getKey();
        }
    }
    return SUCCESS;
}