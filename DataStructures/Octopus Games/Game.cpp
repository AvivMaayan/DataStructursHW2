#include "library1.h"
#include "Game.h"

using std::cout;
using std::endl;
using std::string;

Game::Game() 
{
    groups = Tree<Group>();
    players = Tree<Level>();
}

Status Game::AddGroup(int GroupID)
{
    
}

Status Game::AddPlayer(int PlayerID, int GroupID, int Level)
{

}

Status Game::RemovePlayer(int PlayerID) 
{

}

Status Game::ReplaceGroup(int GroupID, int ReplacementID)
{

}

Status Game::IncreaseLevel(int PlayerID, int LevelIncrease)
{

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



