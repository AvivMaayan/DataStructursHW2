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

int Game::getNumberOfLevels()
{
    return levels.getNumberOfLevels();
}


// merging 2 groups to a new group. removing the old 2 from the tree.
Status Game::MergeGroups(int origID, int replaceID)
{
    // finding the groups - o(logk)
    Group_ptr original = groups.getData(origID);
    Group_ptr replacement = groups.getData(replaceID);
    if(!replacement || !original)
    {
        return S_FAILURE;
    }
    Group_ptr new_group = make_shared<Group>();
    int size_of_first_group = original->getNumberOfLevels();
    int size_of_second_group = replacement->getNumberOfLevels();
    int result_size = size_of_first_group + size_of_second_group; // the real result size might be smaller!
    //as we know - each player could be in only one group ->
    int sum_of_players = original->getNumOfPlayers() + replacement->getNumOfPlayers();

    // creating arrays of Level_ptr o(n + m)
    Level_ptr* array1 = new Level_ptr[size_of_first_group];
    if(!array1)
    {
        throw Allocation_Error();
    }
    for(int i=0; i< size_of_first_group; i++)
    {
        array1[i] = make_shared<Level>();
    }
    Level_ptr* array2 = new Level_ptr[size_of_second_group];
    if(!array2)
    {
        delete[] array1;
        throw Allocation_Error();
    }
    for(int i=0; i< size_of_second_group; i++)
    {
        array2[i] = make_shared<Level>();
    }
    Level_ptr* result_array = new Level_ptr[result_size];
    if(!result_array)
    {
        delete[] array1;
        delete[] array2;
        throw Allocation_Error();
    }
    for(int i=0; i< result_size; i++)
    {
        result_array[i] = make_shared<Level>();
    }
    original->GroupToArray(array1);
    replacement->GroupToArray(array2);

    // merging the group arrays we created o(n + m)
    result_size = MergeGroupArrays(array1, array2, size_of_first_group, size_of_second_group, result_array);

    //updateGroupPtr
    UpdateGroupPtr(result_array, result_size, new_group);

    // making it a group o(n + m)
    new_group->ArrayToGroup(result_array, result_size, sum_of_players);

    // rempving old groups o(logk)
    this->groups.getData(replaceID) = new_group;
    this->groups.remove(origID);


    // adding the new group o(logk)

    delete[] array1;
    delete[] array2;
    delete[] result_array;
    return S_SUCCESS;
}

//return is the size of the new group array
int Game::MergeGroupArrays(Level_ptr *group1, Level_ptr *group2, int size1, int size2, Level_ptr *result)
{
    // merge sorting
    int i1 = 0, i2 = 0;
    int res = 0;
    while (i1 < size1 && i2 < size2)
    {
        int curr_level1 = group1[i1]->getLevel();
        int curr_level2 = group2[i2]->getLevel();
        if (curr_level1 < curr_level2)
        {
            result[res] = group1[i1];
            i1++;
        }

        else if (curr_level1 > curr_level2)
        {
            result[res] = group2[i2];
            i2++;
        }

        // the levels are equal. need to merge between them
        else
        {
            result[res] = make_shared<Level>();

            MergeLevelsToSameGroup(group1[i1], group2[i2], result[res]);
            i1++;
            i2++;
        }
        res++;
    }
    // one of these while is not entered during runtime
    while (i1 < size1)
    {
        result[res] = group1[i1];
        i1++;
        res++;
    }

    while (i2 < size2)
    {
        result[res] = group2[i2];
        i2++;
        res++;
    }
    return res;
}

void Game::MergePlayersOfSameLevel(Player_ptr *level1, Player_ptr *level2, int size1, int size2, Player_ptr *result) // merging arrays created in LevelToArray into a large arranged array
{
    // merge sorting the sh*t out of these arrayyyyssssss
    int i1 = 0, i2 = 0;
    int res = 0;
    while (i1 < size1 && i2 < size2)
    {
        if (level1[i1]->getId() < level2[i2]->getId())
        {
            result[res] = level1[i1];
            i1++;
        }
        else
        {
            result[res] = level2[i2];
            i2++;
        }
        res++;
    }
    // one of these while is not entered during runtime
    while (i1 < size1)
    {
        result[res] = level1[i1];
        i1++;
        res++;
    }

    while (i2 < size2)
    {
        result[res] = level2[i2];
        i2++;
        res++;
    }
    
}

/**
 * merging 2 levels to one big level (tree of players from both levels)
 * all of the players will have a new group pointer - the "this" one 
 * */
void Game::MergeLevelsToSameGroup(Level_ptr level1, Level_ptr level2, Level_ptr result)
{
    int size_of_first_level = level1->getSizeOfLevel();
    int size_of_second_level = level2->getSizeOfLevel();
    int result_size = size_of_first_level + size_of_second_level;
    //creating arrays of Player_ptr
    Player_ptr* array1 = new Player_ptr[size_of_first_level];
    if(!array1)
    {
        throw Allocation_Error();
    }
    for(int i=0; i< size_of_first_level; i++)
    {
        array1[i] = make_shared<Player>();
    }
    Player_ptr* array2 = new Player_ptr[size_of_second_level];   
    if(!array2)
    {
        delete[] array1;
        throw Allocation_Error();
    }
    for(int i=0; i< size_of_second_level; i++)
    {
        array2[i] = make_shared<Player>();
    }
    Player_ptr* result_array = new Player_ptr[result_size];   
    if(!result_array)
    {
        delete[] array1;
        delete[] array2;
        throw Allocation_Error();
    }
    for(int i=0; i< result_size; i++)
    {
        result_array[i] = make_shared<Player>();
    }

    level1->LevelToArray(array1);
    level2->LevelToArray(array2);
    MergePlayersOfSameLevel(array1, array2, size_of_first_level, size_of_second_level, result_array);
    result->ArrayToLevel(result_array, result_size);
    delete[] array1;
    delete[] array2;
    delete[] result_array;
}

void Game::UpdateGroupPtr(Level_ptr *level_array, int size, Group_ptr new_group)
{
    /*
    for(int i=0; i < size; i++)
    {
        //Tree<Player_ptr> level_tree = level_array[i]->players;
        for(Tree<Player_ptr>::const_iterator it = level_array[i]->players.begin() ; it != level_array[i]->players.end(); ++it)
        {
            it.getData()->setGroup(new_group);
        }
    }
    */
   for (int i = 0; i < size; i++)
   {
       for (auto it = level_array[i]->players.begin(); it != level_array[i]->players.end(); ++it)
       {
           it.getData()->setGroup(new_group);
       }
   }
}


////////////////////////////////////////////////////////////////////////////////
Status Game::AddGroup(int GroupID)
{
    if (groups.isExist(GroupID))
    {
        return S_FAILURE;
    }
    try
    {
        groups.insert(GroupID, make_shared<Group>());
        // Player_ptr player = make_shared<Player>(Level, group_ptr);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return S_ALLOCATION_ERROR;
    }
    return S_SUCCESS;
}

Status Game::AddPlayer(int PlayerID, int GroupID, int Level)
{
    if (players.isPlayerExist(PlayerID) || !groups.isExist(GroupID)) // player exists already or group doesn't
    {
        return S_FAILURE;
    }
    try
    {
        // we are using T& Tree<T>::(int key_to_find)
        // only when we know that Tree<T>.isExist(key_to_find) is true!
        Group_ptr group_ptr = groups.getData(GroupID);
        Player_ptr player = make_shared<Player>(PlayerID, Level, group_ptr);

        // Adding to players tree
        players.addPlayer(PlayerID, player);

        // Adding to levels tree
        levels.addPlayer(PlayerID, player);

        // Adding to groups tree
        group_ptr->addPlayer(PlayerID, player);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return S_ALLOCATION_ERROR;
    }
    return S_SUCCESS;
}

Status Game::RemovePlayer(int PlayerID)
{
    if (!players.isPlayerExist(PlayerID)) // player does not exist
    {
        return S_FAILURE;
    }

    Player_ptr player = players.getPlayerPtr(PlayerID);
    Group_ptr group_ptr = player->getGroupPtr();

    // Removing from players tree
    players.removePlayer(PlayerID);

    // Removing from levels tree
    levels.removePlayer(PlayerID, player);

    // Removing from groups tree
    group_ptr->removePlayer(PlayerID, player);

    return S_SUCCESS;
}

Status Game::ReplaceGroup(int GroupID, int ReplacementID)
{
    if (!groups.isExist(GroupID) || !groups.isExist(ReplacementID))
    {
        return S_FAILURE;
    }
    Status res;
    try
    {
        res = MergeGroups(GroupID, ReplacementID);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return S_ALLOCATION_ERROR;
    }
    return res;
}

Status Game::IncreaseLevel(int PlayerID, int LevelIncrease)
{
    if (!players.isPlayerExist(PlayerID)) // player does not exist
    {
        return S_FAILURE;
    }
    try
    {
        Player_ptr player = players.getPlayerPtr(PlayerID);
        Group_ptr group_ptr = player->getGroupPtr();
        int level = player->getLevel();

        // removing the player from 2 trees
        group_ptr->removePlayer(PlayerID, player);
        levels.removePlayer(PlayerID, player);

        // updating player's info
        player->setLevel(level + LevelIncrease);

        // re-inserting the player
        group_ptr->addPlayer(PlayerID, player);
        levels.addPlayer(PlayerID, player);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return S_ALLOCATION_ERROR;
    }
    return S_SUCCESS;
}

Status Game::GetHighestLevel(int GroupID, int *PlayerID)
{
    if (GroupID < 0)
    {
        return levels.getHighestLevel(PlayerID);
    }
    if (!groups.isExist(GroupID))
    {
        return S_FAILURE;
    }
    // we are using T& Tree<T>::(int key_to_find)
    // only when we know that Tree<T>.isExist(key_to_find) is true!
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
        //not sure if this is really the right way!
        (*Players) = NULL;
        return S_FAILURE;
    }
    // we are using T& Tree<T>::(int key_to_find)
    // only when we know that Tree<T>.isExist(key_to_find) is true!
    Group_ptr group_ptr = groups.getData(GroupID);
    Status res = group_ptr->getAllPlayersByLevel(Players, numOfPlayers);
    return res;
}

Status Game::GetGroupsHighestLevel(int numOfGroups, int **Players)
{
    int i = 0;
    for (Tree<Group_ptr>::const_iterator group_iterator = groups.begin(); group_iterator != groups.end() && i < numOfGroups; ++group_iterator)
    {
        if (!group_iterator.getData()->isEmpty())
        {
            group_iterator.getData()->getHighestLevel(&((*Players)[i]));
            i++;
        }
    }
    if (i < numOfGroups) // more space in the array then num of not empty groups
    {
        return S_FAILURE;
    }
    return S_SUCCESS;
}
