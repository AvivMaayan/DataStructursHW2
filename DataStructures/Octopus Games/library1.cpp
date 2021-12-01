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
