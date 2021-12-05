#include "Tree.h"
#include "Game.h"

int main()
{
    Game game;
    game.AddGroup(1);
    for (int i = 1; i <= 5; i++)
    {
        game.AddPlayer(i,1,i);
    }
    return 0;
}