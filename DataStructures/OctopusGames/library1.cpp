#include "library1.h"
#include "Game.h"

void *Init()
{
    Game *DS = new Game();
    return (void *)DS;
}

StatusType AddGroup(void *DS, int GroupID)
{
    if (!DS || GroupID <= 0)
    {
        return (StatusType)INVALID_INPUT;
    }
    return (StatusType)((Game *)DS)->AddGroup(GroupID);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level)
{
    if (!DS || GroupID <= 0 || PlayerID <= 0, Level<0)
    {
        return (StatusType)INVALID_INPUT;
    }
    return (StatusType)((Game *)DS)->AddPlayer(PlayerID, GroupID, Level);
}

StatusType RemovePlayer(void *DS, int PlayerID)
{
    if (!DS || PlayerID <= 0)
    {
        return (StatusType)INVALID_INPUT;
    }
    return (StatusType)((Game *)DS)->RemovePlayer(PlayerID);
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID)
{
    if (!DS || GroupID <= 0 || ReplacementID <= 0 || GroupID==ReplacementID)
    {
        return (StatusType)INVALID_INPUT;
    }
    return (StatusType)((Game *)DS)->ReplaceGroup(GroupID, ReplacementID);
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if (!DS || PlayerID <= 0 || LevelIncrease <= 0)
    {
        return (StatusType)INVALID_INPUT;
    }
    return (StatusType)((Game *)DS)->IncreaseLevel(PlayerID, LevelIncrease);
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID)
{
    if (!DS || GroupID == 0 || !PlayerID)
    {
        return (StatusType)INVALID_INPUT;
    }
    return (StatusType)((Game *)DS)->GetHighestLevel(GroupID, PlayerID);
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers)
{
    if (!DS || GroupID == 0 || !Players || !numOfPlayers)
    {
        return (StatusType)INVALID_INPUT;
    }

    *Players = (int*)malloc(sizeof(int) * *numOfPlayers); 
    if (!*Players)
    {
        return (StatusType)ALLOCATION_ERROR;
    }

    return (StatusType)((Game *)DS)->GetAllPlayersByLevel(GroupID, Players, numOfPlayers);
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players)
{
    if (!DS || numOfGroups < 1 || !Players)
    {
        return (StatusType)INVALID_INPUT;
    }
    
    *Players = (int*)malloc(sizeof(int) * numOfGroups);
    if (!*Players)
    {
        return (StatusType)ALLOCATION_ERROR;
    }

    return (StatusType)((Game *)DS)->GetGroupsHighestLevel(numOfGroups, Players);
}

void Quit(void** DS)
{
    delete (Game*)*DS;
    *DS = NULL;
}