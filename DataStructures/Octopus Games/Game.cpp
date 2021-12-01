#include "library1.h"
#include "Game.h"

using std::cout;
using std::endl;
using std::string;

Game::Game() 
{

}

Game::~Game()
{

}

void *Init()
{
    return new Game();
}

StatusType AddGroup(void *DS, int GroupID)
{
    if(GroupID <= 0 || !DS) {
        return INVALID_INPUT;
    }
    if()
}