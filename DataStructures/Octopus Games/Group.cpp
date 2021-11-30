#include "Group.h"

Group::Group(Id id) : group_id(id), players() {}
int Group::getGroup() const
{
    return group_id;
}

// assuming that player is new in the game, and input is valid
// REMEMER TO CHECK AND ADD IF NEDEED
// BAD ALLOC CHECK
StatusType Group::addPlayer(Id player, int level)
{
    if (!players.isExists(level)) // this level doesn't exists
    {
        players.insert(level, Level());
    }
    // level_tree defintely exists by now
    Level players_tree = players.getData(level);
    players_tree.insert(player, player);
    return SUCCESS;
}

// assuming input is valid, player exists in the game -> we know his level (from the Stack)
// going over all of the groups in game and calling this func
StatusType Group::removePlayer(Id player, int level)
{
    Level players_tree = players.getData(level);
    players_tree.remove(player);
    return SUCCESS;
}

// assuming valid input, player exists -> we know his level (from the Stack)
StatusType Group::updateLevel(Id player, int level, int increasement)
{
    Level players_tree = players.getData(level);
    players_tree.remove(player);
    return addPlayer(player, level + increasement);
}

StatusType Group::getHeighestLevel(Id *player)
{
    if (players.isEmpty())
    {
        *player = -1;
        return SUCCESS;
    }
    Level heighest = players.reverseBegin().getData();
    *player = heighest.begin().getData();
    return SUCCESS;
}

StatusType Group::getAllPlayersByLevel(Id **players_array, int *num_of_players)
{
    *num_of_players = players.getSize();
    if (*num_of_players==0)
    {
        players_array=NULL;
        return SUCCESS;
    }
    *players_array = (Id*)malloc(sizeof(Id)**num_of_players);
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