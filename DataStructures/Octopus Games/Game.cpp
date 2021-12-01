#include "library1.h"
#include "Game.h"

using std::cout;
using std::endl;
using std::string;

Game::Game() 
{
    groups = Tree<Group>();
    levels = Tree<Level>();
    players = Tree<Player_ptr>();
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
 */
int Game::getLevel(Id PlayerID) 
{
    if(!players.isExist(PlayerID))
    {
        return DOES_NOT_EXIST;
    }
    return players.getData(PlayerID)->getLevel();
}

Status Game::AddPlayer(int PlayerID, int GroupID, int Level)
{
    if(players.isExist(PlayerID) || !groups.isExist(GroupID)) //player exists already or group doesn't 
    {
        return FAILURE;
    }
    try
    {
        Group *group_ptr = &groups.getData(GroupID);
        Player_ptr player = make_shared<Player>(Level, group_ptr);

        //Adding to players tree
        players.insert(PlayerID, player);

        //Adding to levels tree
        Tree<Player_ptr> curr_level;
        if(!levels.isExist(Level))//this player is the only one in this Level 
        {
            curr_level = levels.insert(Level);
        }
        //Level exists in levels tree
        curr_level.insert(PlayerID);
        
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
    if(!players.isExist(PlayerID)) //player does not exist 
    {
        return FAILURE;
    }
    Player_ptr player = players.getData(PlayerID);
    Group *group_ptr = player->getGroupPtr();
    int level = player->getLevel();

    //Removing from players tree
    players.remove(PlayerID);

    //Removing from levels tree
    levels.getData(level).remove(PlayerID);
    //checking if the level is now empty
    if (levels.getData(level).isEmpty())
    {
        levels.remove(level);
    }
        
    //Removing from groups tree
    group_ptr->removePlayer(PlayerID, player); 

    return SUCCESS;
}

Status Game::ReplaceGroup(int GroupID, int ReplacementID)
{
    
}

Status Game::IncreaseLevel(int PlayerID, int LevelIncrease)
{
    if(!players.isExist(PlayerID)) //player does not exist 
    {
        return FAILURE;
    }
    Player_ptr player = players.getData(PlayerID);
    Group *group_ptr = player->getGroupPtr();
    int level = player->getLevel();

    //removing the player from 2 trees
    group_ptr->removePlayer(PlayerID, player);
    levels.getData(level).remove(PlayerID);

    //updating player's info
    player->setLevel(level + LevelIncrease);

    //re-inserting the player
    group_ptr->addPlayer(PlayerID, player);

    if (!levels.isExist(level + LevelIncrease)) // this level doesn't exist
    {
        levels.insert(level + LevelIncrease);
    }
    levels.getData(level + LevelIncrease).insert(PlayerID);
}

Status Game::GetHighestLevel(int GroupID, int *PlayerID)
{

}

Status Game::GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers)
{

}

Status GetGroupsHighestLevel(int numOfGroups, int **Players)
{

}



