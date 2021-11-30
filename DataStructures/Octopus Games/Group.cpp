#include "Group.h"

Group::Group(Id id) : group_id(id), players(){}
int Group::getGroup() const
{
    return group_id;
}

//assuming that player is new in the game, and input is valid
//REMEMER TO CHECK AND ADD IF NEDEED
//BAD ALLOC CHECK
StatusType Group::addPlayer(Id player, int level)
{
    if (!players.isExists(level))//this level doesn't exists
    {
        players.insert(level,Level());
    }
    //level_tree defintely exists by now
    Level level_tree = players.getData(level);
    level_tree.insert(player,player);
    return SUCCESS;
}

//assuming input is valid, player exists in the game
//going over all of the groups in game and calling this func
StatusType Group::removePlayer(Id player)
{
    for (Tree<Level>::const_iterator level_it = players.begin() ; level_it != players.end(); ++level_it)
    {
       level_it.getData().remove(player);
    }
    return SUCCESS;
}

//assuming valid input, player exists
StatusType Group::updateLevel(Id player, int increasement)
{
    for (Tree<Level>::const_iterator level_it = players.begin() ; level_it != players.end(); ++level_it)
    {
        
        level_it.getData().remove(player);

    }
}

StatusType Group::getHeighestLevel(Id* player)
{

}
StatusType Group::getAllPlayersById(Id** players, int* numOfPlayers)
{

}