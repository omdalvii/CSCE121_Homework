#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"
#include "helper.h"

using std::cout, std::endl, std::ifstream, std::string;

#define DEBUG_ON false
#define DEBUG(X) if(DEBUG_ON) {cout << "[DEBUG] (" << __FUNCTION__ << ":" << __LINE__ << ") " << X << endl;}

/**
 * LEVEL SOLUTIONS
 * 
 * EASY:
 *  Easy 1: a www d a ssss dddd
 *  Easy 2: s a s aaaaa s
 * 
 *  Easy skip to 2: awwwdassssdddd
 *  Easy full level: awwwdassssddddsasaaaaas
 * 
 * HARD:
 *  Hard 1: s d s d s d ss dd ww
 *  Hard 2: a ssss dd sss aa sss dd ssss a
 *  Hard 3:
 * 
 *  Hard skip to 2: sdsdsdssddw
 *  Hard skip to 3: sdsdsdssddwwassssddsssaasssddssssa
 *  Hard full level: 
 * 
*/

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char **loadLevel(const string &fileName, int &maxRow, int &maxCol, Player &player)
{
    // create input filestream for map file
    ifstream levelFile;
    levelFile.open(fileName);

    // check that level file is open
    if (!levelFile.is_open())
    {
        // if not, nullptr
        return nullptr;
    }

    // get header data from map file
    levelFile >> maxRow;
    if (levelFile.fail())
    {
        DEBUG("Could not read max row data!")
        levelFile.close();
        return nullptr;
    }
    levelFile >> maxCol;
    if (levelFile.fail())
    {
        DEBUG("Could not read max column data!")
        levelFile.close();
        return nullptr;
    }
    levelFile >> player.row;
    if (levelFile.fail())
    {
        DEBUG("Could not read player row data!")
        levelFile.close();
        return nullptr;
    }
    levelFile >> player.col;
    if (levelFile.fail())
    {
        DEBUG("Could not read player column data!")
        levelFile.close();
        return nullptr;
    }

    // check that player is in bounds and that size is valid
    if (player.row >= maxRow || player.col >= maxCol ||
        player.row < 0 || player.col < 0)
    {
        // if not, nullptr
        DEBUG("Player out of bounds!")
        levelFile.close();
        return nullptr;
    }
    if (maxRow > 999999 || maxCol > 999999 || 
        maxRow <= 0 || maxCol <= 0)
    {
        // if not, nullptr
        DEBUG("Map size invalid!!")
        levelFile.close();
        return nullptr;
    }

    // // initialize map
    char **map = createMap(maxRow, maxCol);

    // get level layout data from map file
    char currInput;
    for (int i = 0; i < maxRow; i++)
    {
        for (int j = 0; j < maxCol; j++)
        {
            // check that input exists
            levelFile >> currInput;
            if (levelFile.fail() == false)
            {
                // check that input is a valid tile
                if (TILES.find(currInput) != string::npos)
                {
                    // // if so, add to map
                    map[i][j] = currInput;
                }
                else
                {
                    // otherwise, nullptr
                    DEBUG("invalid tile found! (" << currInput << ")");
                    deleteMap(map, maxRow);
                    levelFile.close();
                    return nullptr;
                }
            }
            else
            {
                // otherwise, nullptr
                DEBUG("input file failed to read!");
                deleteMap(map, maxRow);
                levelFile.close();
                return nullptr;
            }
        }
    }

    // check to ensure there are no extraneous tiles
    char checker;
    if(levelFile >> checker)
    {
        // if not, nullptr
            DEBUG("too many tile values!");
            deleteMap(map, maxRow);
            levelFile.close();
            return nullptr;
    }

    // add the player to the map and return
    map[player.row][player.col] = TILE_PLAYER;
    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int &nextRow, int &nextCol)
{
    if (input == MOVE_RIGHT)
    {
        nextCol += 1;
    }
    else if (input == MOVE_LEFT)
    {
        nextCol -= 1;
    }
    else if (input == MOVE_UP)
    {
        nextRow -= 1;
    }
    else if (input == MOVE_DOWN)
    {
        nextRow += 1;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char **createMap(int maxRow, int maxCol)
{
    // create 2d map array
    char **map = new char*[maxRow];

    // initialize each tile to TILE_OPEN
    for (int i = 0; i < maxRow; i++)
    {
        map[i] = new char[maxCol];
        for (int j = 0; j < maxCol; j++)
        {
            map[i][j] = TILE_OPEN;
        }
    }

    // return the generated map
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char **&map, int &maxRow)
{
    for (int i = 0; i < maxRow; i++)
    {
        delete[] map[i];
    }
    delete[] map;
    maxRow = 0;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char **resizeMap(char **map, int &maxRow, int &maxCol)
{
    int rowMod = maxRow, colMod = maxCol;
    maxRow *= 2;
    maxCol *= 2;
    char** newMap = createMap(maxRow, maxCol);

   int playerCount = 0;
    for (int i = 0; i < maxRow; i++)
    {
        for (int j = 0; j < maxCol; j++)
        {
            char fillChar = map[i%rowMod][j%colMod];
            if (fillChar == TILE_PLAYER)
            {
                fillChar = (playerCount >=1) ? TILE_OPEN:TILE_PLAYER;
                playerCount++;
            }
            newMap[i][j] = fillChar;
        }
    }

    deleteMap(map, rowMod);
    return newMap;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure.
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char **map, int maxRow, int maxCol, Player &player, int nextRow, int nextCol)
{
    // set vectors for current and new player position
    int currPos[2] = {player.row, player.col}, newPos[2] = {nextRow, nextCol};
    DEBUG("Trying to move to ()" << newPos[0] << ", " << newPos[1] << ")")

    // check that new position is within bounds
    if (newPos[0] >= maxRow || newPos[0] < 0 ||
        newPos[1] >= maxCol || newPos[1] < 0)
    {
        // if not, return status of stay
        return STATUS_STAY;
    }

    // check which status should be returned
    char nextTile = map[newPos[0]][newPos[1]];
    int status = STATUS_STAY;
    switch (nextTile) {
        case TILE_AMULET:
            status = STATUS_AMULET;
            break;

        case TILE_DOOR:
            status = STATUS_LEAVE;
            break;

        case TILE_EXIT:
            if(player.treasure >= 1){status = STATUS_ESCAPE;}
            else{status = STATUS_STAY;}
            break;

        case TILE_TREASURE:
            status = STATUS_TREASURE;
            player.treasure += 1;
            break;

        case TILE_OPEN:
            status = STATUS_MOVE;
            break;

        
        case TILE_MONSTER:
        case TILE_PILLAR:
        case TILE_PLAYER:
            status = STATUS_STAY;
            break;

        default:
            break;
    }
    
    if(status != STATUS_STAY)
    {
        // update player position on map
        // make current player pos empty
        map[currPos[0]][currPos[1]] = TILE_OPEN;
        // put player on new position tile
        map[newPos[0]][newPos[1]] = TILE_PLAYER;

        // update player position parameters
        player.row = nextRow;
        player.col = nextCol;   
    }
    else{
        nextRow = player.row;
        nextRow = player.col;
    }

    // return the status 
    return status;
}
/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char **map, int maxRow, int maxCol, const Player &player)
{
    // boolean variable to keep track of if monster hits player
    bool doesHit = false;

    // Check up
    DEBUG("Checking above player...");
    for (int i = player.row-1; i >= 0; i--)
    {
        char checkTile = map[i][player.col];
        DEBUG("--row " << i << " = " << checkTile)
        if(checkTile == TILE_PILLAR) 
        {
            // break out of the loop if a pillar is found before a monster
            DEBUG("Pillar found! Moving to next check...")
            break;
        }
        else if (checkTile == TILE_MONSTER){
            // check if monster will hit player
            if (i+1 == player.row){doesHit = true;}

            // move monster towards player (down) by one tile
            DEBUG("Monster Found! Moving monster down one tile")
            map[i][player.col] = TILE_OPEN;
            map[i+1][player.col] = TILE_MONSTER;
        }
    }
    // Check down
    DEBUG("Checking above player...");
    for (int i = player.row+1; i < maxRow; i++)
    {
        char checkTile = map[i][player.col];
        DEBUG("--row " << i << " = " << checkTile)
        if(checkTile == TILE_PILLAR) 
        {
            // break out of the loop if a pillar is found before a monster
            DEBUG("Pillar found! Moving to next check...")
            break;
        }
        else if (checkTile == TILE_MONSTER){
            // check if monster will hit player
            if (i-1 == player.row){doesHit = true;}

            // move monster towards player (up) by one tile
            DEBUG("Monster Found! Moving monster up one tile")
            map[i][player.col] = TILE_OPEN;
            map[i-1][player.col] = TILE_MONSTER;
        }
    }

    // Check right
    DEBUG("Checking to right of player...");
    for (int i = player.col+1; i < maxCol; i++)
    {
        char checkTile = map[player.row][i];
        DEBUG("--col " << i << " = " << checkTile)
        if(checkTile == TILE_PILLAR) 
        {
            // break out of the loop if a pillar is found before a monster
            DEBUG("Pillar found! Moving to next check...")
            break;
        }
        else if (checkTile == TILE_MONSTER){
            // check if monster will hit player
            if (i-1 == player.col){doesHit = true;}

            // move monster towards player (left) by one tile
            DEBUG("Monster Found! Moving monster left one tile")
            map[player.row][i] = TILE_OPEN;
            map[player.row][i-1] = TILE_MONSTER;
        }
    }

    // Check left
    DEBUG("Checking to left of player...");
    for (int i = player.col-1; i >= 0; i--)
    {
        char checkTile = map[player.row][i];
        DEBUG("--col " << i << " = " << checkTile)
        if(checkTile == TILE_PILLAR) 
        {
            // break out of the loop if a pillar is found before a monster
            DEBUG("Pillar found! Moving to next check...")
            break;
        }
        else if (checkTile == TILE_MONSTER){
            // check if monster will hit player
            if (i+1 == player.col){doesHit = true;}

            // move monster towards player (right) by one tile
            DEBUG("Monster Found! Moving monster right one tile")
            map[player.row][i] = TILE_OPEN;
            map[player.row][i+1] = TILE_MONSTER;

        }
    }

    return doesHit;
}