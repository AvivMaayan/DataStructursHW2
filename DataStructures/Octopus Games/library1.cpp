#include "library1.h"
#include "Game.h"

void* Init() {
    Game *DS = new Game();
    return (void*)DS;
}

StatusType AddGroup(void *DS, int GroupID) {
    if(!DS || GroupID <= 0) {
        return INVALID_INPUT;
    }
    return (Game*)DS->AddGroup(GroupID);
}

