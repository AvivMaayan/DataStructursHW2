#include "library1.h"
#include "Game.h"

using std::cout;
using std::endl;
using std::string;

Game::Game() 
{
    groups = Tree<Group_ptr>();
    levels = Group();
    players = Level();
}

Status Game::AddGroup(int GroupID)
{
    if(groups.isExist(GroupID))
    {
        return FAILURE;
    }
    try
    {
        groups.insert(GroupID);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

/**
 * @brief returns the level of ID player. 
 * if doesn't exist, returns DOES_NOT_EXIST (-1)
* @e log(n)
 * @param player 
 * @return int level or -1
 *
int Game::getLevel(Id PlayerID) 
{
    if(!players.isExist(PlayerID))
    {
        return DOES_NOT_EXIST;
    }
    return players.getData(PlayerID)->getLevel();
}*/

Status Game::AddPlayer(int PlayerID, int GroupID, int Level)
{
    if(players.isPlayerExist(PlayerID) || !groups.isExist(GroupID)) //player exists already or group doesn't 
    {
        return FAILURE;
    }
    try
    {
        //we are using T& Tree<T>::(int key_to_find) 
        //only when we know that Tree<T>.isExist(key_to_find) is true!
        Group_ptr group_ptr = groups.getData(GroupID);
        Player_ptr player = make_shared<Player>(Level, group_ptr);

        //Adding to players tree
        players.addPlayer(PlayerID, player);

        //Adding to levels tree
        levels.addPlayer(PlayerID, player);
        
        //Adding to groups tree
        group_ptr->addPlayer(PlayerID, player);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

Status Game::RemovePlayer(int PlayerID) 
{
    if(!players.isPlayerExist(PlayerID)) //player does not exist 
    {
        return FAILURE;
    }

    Player_ptr player = players.getPlayerPtr(PlayerID);
    Group *group_ptr = player->getGroupPtr();

    //Removing from players tree
    players.removePlayer(PlayerID);

    //Removing from levels tree
    levels.removePlayer(PlayerID, player);
        
    //Removing from groups tree
    group_ptr->removePlayer(PlayerID, player); 

    return SUCCESS;
}

Status Game::ReplaceGroup(int GroupID, int ReplacementID)
{
    
}

Status Game::IncreaseLevel(int PlayerID, int LevelIncrease)
{
    if(!players.isPlayerExist(PlayerID)) //player does not exist 
    {
        return FAILURE;
    }

    Player_ptr player = players.getPlayerPtr(PlayerID);
    Group *group_ptr = player->getGroupPtr();
    int level = player->getLevel();

    //removing the player from 2 trees
    group_ptr->removePlayer(PlayerID, player);
    levels.removePlayer(PlayerID, player);

    //updating player's info
    player->setLevel(level + LevelIncrease);

    //re-inserting the player
    group_ptr->addPlayer(PlayerID, player);
    levels.addPlayer(PlayerID, player);
}

Status Game::GetHighestLevel(int GroupID, int *PlayerID)
{
    if (GroupID < 0)
    {
        return levels.getHighestLevel(PlayerID);
    }
    if (!groups.isExist(GroupID))
    {
        return FAILURE;
    }
    //we are using T& Tree<T>::(int key_to_find) 
    //only when we know that Tree<T>.isExist(key_to_find) is true!
    Group_ptr group_ptr = groups.getData(GroupID);
    return group_ptr->getHighestLevel(PlayerID);
}

Status Game::GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers)
{
    if (GroupID < 0)
    {
        return levels.getAllPlayersByLevel(Players, numOfPlayers);
    }
    if (!groups.isExist(GroupID))
    {
        return FAILURE;
    }
    //we are using T& Tree<T>::(int key_to_find) 
    //only when we know that Tree<T>.isExist(key_to_find) is true!
    Group_ptr group_ptr = groups.getData(GroupID);
    return group_ptr->getAllPlayersByLevel(Players, numOfPlayers);
}

Status Game::GetGroupsHighestLevel(int numOfGroups, int **Players)
{
    int i=0;
    for (Tree<Group_ptr>::const_iterator group_iterator = groups.begin() ; group_iterator != groups.end() && i< numOfGroups; ++group_iterator)
    {
        if(!group_iterator.getData()->isEmpty())
        {
            group_iterator.getData()->getHighestLevel(Players[i]);
            i++;
        }
    }
    if(i < numOfGroups) //more space in the array then num of not empty groups
    {
        return FAILURE;
    }
    return SUCCESS; 
}



