#include "Group.h"

Group::Group(Id id) : group_id(id), players() {}

int Group::getGroup() const
{
    return group_id;
}


/**
 * @e o(log(n))
 * @param .
 * n is players in group
 *  assuming that player is new in the game, and input is valid
 * @return SUCCESS only
// REMEMER TO CHECK AND ADD IF NEDEED
// BAD ALLOC CHECK
 * */
StatusType Group::addPlayer(Id player, int level)
{
    if (!players.isExist(level)) // this level doesn't exist
    {
        players.insert(level, Level());
    }
    // level_tree defintely exists by now
    Level players_tree = players.getData(level);
    players_tree.insert(player, player);
    return SUCCESS;
}


/**
 * @e o(log(n))
 * @param .
 * n is players in group
 *  assuming input is valid, player exists in the game -> we know his level (from the Stack)
// going over all of the groups in game and calling this func
 * */
StatusType Group::removePlayer(Id player, int level)
{
    Level players_tree = players.getData(level);
    players_tree.remove(player);
    return SUCCESS;
}

/**
 * @e o(log(n))
 * @param .
 * n is players in group
 * assuming valid input, player exists -> we know his level (from the Stack)
 * WHAT ABOUT BAD ALLOC CHECK?
 * */
StatusType Group::updateLevel(Id player, int level, int increasement)
{
    Level players_tree = players.getData(level);
    players_tree.remove(player);
    return addPlayer(player, level + increasement);
}
/**
 * @e o(1)
 * @param player pointer to the id of wanted player
 * the player is at the *highest* level in the group,
 * ,has the *lowest* id from those at the same level
 * @return SUCCESS *only* and id of player (as param) if was found, -1 otherwise
 * */
StatusType Group::getHighestLevel(Id *player)
{
    if (players.isEmpty()) //player is not in group
    {
        *player = -1; //trash
        return SUCCESS;
    }
    Level heighest = players.reverseBegin().getData(); //highest level
    *player = heighest.begin().getData(); //lowest player
    return SUCCESS;
}

/**
 * @e o(1)
 * @param players_array pointer to the array of players arranged by level
 * @param num_of_players in player's array
 * players are arranged like so:
 * from highest to lowest level
 * within each level - lowest to highest id
 * @return SUCCESS if null array or just an array, ALLOCATION_ERROR otherwise
 * */
StatusType Group::getAllPlayersByLevel(Id **players_array, int *num_of_players)
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
            *players_array[i] = players_it.getData();
        }
    }
    return SUCCESS;
}