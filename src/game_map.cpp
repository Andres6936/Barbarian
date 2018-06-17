#include <iostream>
#include "../include/random.hpp"
#include "../include/game_map.hpp"

GameMap::GameMap(int w, int h, int roomSizeMax, int roomSizeMin, int numRoomsMax) : width_(w), height_(h), roomSizeMax_(roomSizeMax),
    roomSizeMin_(roomSizeMin), numRoomsMax_(numRoomsMax)
{
    initTiles_();
    makeMap_();
}

void GameMap::initTiles_()
{
    int wallFlags = (Tile::Flags::BLOCKS_MOVEMENT | Tile::Flags::BLOCKS_LIGHT);
    wsl::Glyph wallGlyph = wsl::Glyph('#', wsl::Color(0,0,50));
    Tile wallTile = Tile(wallFlags, wallGlyph);
    tiles.assign(width_ * height_, wallTile);
}

void GameMap::createRoom_(wsl::Rect room)
{
    for(int x = room.x1 + 1; x < room.x2; ++x)
    {
        for(int y = room.y1 + 1; y < room.y2; ++y)
        {
            tiles[index(x,y)] = Tile(Tile::Flags::NONE, wsl::Glyph(' ', wsl::Color(0,0,50)));
        }
    }
}

void GameMap::hTunnel_(int x1, int x2, int y)
{
    int min = (x1 < x2 ? x1 : x2);
    int max = (x1 > x2 ? x1 : x2);
    for(int i = min; i <= max; ++i)
    {
        tiles[index(i,y)] = Tile(Tile::Flags::NONE, wsl::Glyph(' ', wsl::Color(0,0,50)));
    }
}

void GameMap::vTunnel_(int y1, int y2, int x)
{
    int min = (y1 < y2 ? y1 : y2);
    int max = (y1 > y2 ? y1 : y2);
    for(int i = min; i <= max; ++i)
    {
        tiles[index(x,i)] = Tile(Tile::Flags::NONE, wsl::Glyph(' ', wsl::Color(0,0,50)));
    }
}

void GameMap::makeMap_()
{
/*
    // Basic Tutorial algorithm
    int numRooms = 0;
    while(numRooms < numRoomsMax_)
    {
        int w = wsl::randomInt(roomSizeMin_, roomSizeMax_);
        int h = wsl::randomInt(roomSizeMin_, roomSizeMax_);
        int x = wsl::randomInt(0, width_ - w - 1);
        int y = wsl::randomInt(0, height_ - h - 1);

        wsl::Rect newRoom = wsl::Rect(x,y,w,h);
        bool intersect = false;
        for(int j = 0; j < rooms.size(); ++j)
        {
            if(rooms[j].intersect(newRoom))
            {
                intersect = true;
            }
        }
        if(!intersect)
        {
            createRoom_(newRoom);
            if(rooms.size() > 0)
            {
                sf::Vector2i previous = rooms[rooms.size() - 1].center();
                sf::Vector2i current = newRoom.center();
                if(wsl::randomBool())
                {
                    hTunnel_(previous.x, current.x, previous.y);
                    vTunnel_(previous.y, current.y, current.x);
                }
                else // wsl::randomBool() == false
                {
                    vTunnel_(previous.y, current.y, previous.x);
                    hTunnel_(previous.x, current.x, current.y);
                }
            }
            rooms.push_back(newRoom);
            numRooms += 1;
        }
    }
*/
    
    // BSP dungeon generator
    Tree * bspTree = new Tree;
    bspTree->populate(wsl::Rect(0,0,width_ - 1,height_ - 1));
    for(int i = 0; i < bspTree->rooms().size(); ++i)
    {
        wsl::Rect newRoom = bspTree->rooms()[i];
        createRoom_(newRoom);
        rooms.push_back(newRoom);
    }
    delete bspTree;
}

bool GameMap::isBlocked(int x, int y)
{
    bool success = false;
    if(tiles[index(x,y)].blocksMovement())
    {
        success = true;
    }
    return success;
}
