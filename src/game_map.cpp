/*
* Barbarian!
* Copyright (C) Zach Wilder 2018
* 
* This file is a part of Barbarian!
*
* Barbarian! is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* Barbarian! is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with Barbarian!.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "../include/random.hpp"
#include "../include/game_map.hpp"

GameMap::GameMap(int w, int h, int roomSizeMax, int roomSizeMin, int numRoomsMax) : width_(w), height_(h), roomSizeMax_(roomSizeMax),
    roomSizeMin_(roomSizeMin), numRoomsMax_(numRoomsMax)
{
    initTiles_();
    makeMap_();
}

Tile & GameMap::tileAt(int x, int y)
{
    return (tiles[index(x,y)]);
}

void GameMap::initTiles_()
{
    Tile wallTile = Tile::Wall;
    tiles.assign(width_ * height_, wallTile);
}

void GameMap::createRoom_(wsl::Rect room)
{
    for(int x = room.x1 + 1; x < room.x2; ++x)
    {
        for(int y = room.y1 + 1; y < room.y2; ++y)
        {
            tiles[index(x,y)] = Tile::Floor;
        }
    }
}

void GameMap::hTunnel_(int x1, int x2, int y)
{
    int min = (x1 < x2 ? x1 : x2);
    int max = (x1 > x2 ? x1 : x2);
    for(int i = min; i <= max; ++i)
    {
        tiles[index(i,y)] = Tile::Floor;
        if(tileAt(i + 1,y) == Tile::Floor)
        {
            // break;
        }
    }
}

void GameMap::vTunnel_(int y1, int y2, int x)
{
    int min = (y1 < y2 ? y1 : y2);
    int max = (y1 > y2 ? y1 : y2);
    for(int i = min; i <= max; ++i)
    {
        tiles[index(x,i)] = Tile::Floor;
        if(tileAt(x,i+1) == Tile::Floor)
        {
            // break;
        }
    }
}

void GameMap::makeMap_()
{
    // Basic Tutorial algorithm
    int numRooms = 0;
    while(numRooms < numRoomsMax_)
    {
        int w = wsl::randomInt(roomSizeMin_, roomSizeMax_);
        int h = wsl::randomInt(roomSizeMin_, roomSizeMax_);
        int x = wsl::randomInt(0, width_ - w - 1);
        while(x % 2 != 0)
        {
            x = wsl::randomInt(0, width_ - w - 1);
        }
        int y = wsl::randomInt(0, height_ - h - 1);
        while(y % 2 != 0)
        {
            y = wsl::randomInt(0, height_ - h - 1);
        }

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
                wsl::Vector2i previous(rooms[rooms.size() - 1].center());
                wsl::Vector2i current(newRoom.center());
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
    /*
    std::unique_ptr<bsp::Tree> bspTree = std::make_unique<bsp::Tree>(wsl::Rect(0,0,width_,height_));
    bsp::Dungeon dungeon(bspTree.get(), 8, false); // Access to tiles_

    rooms.clear();
    rooms = dungeon.rooms;
    tiles = dungeon.dungeonMap;
    */
   
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

void GameMap::placeEntities(std::vector<Entity> * entityList, int maxPerRoom)
{
    entityList->clear();
    for(int i = 1; i < rooms.size(); ++i)
    {
        wsl::Rect & room = rooms[i];
        int numEntities = wsl::randomInt(0, maxPerRoom);

        for(int j = 0; j <= numEntities; ++j)
        {
            int x = wsl::randomInt(room.x1 + 1,room.x2 - 1);
            int y = wsl::randomInt(room.y1 + 1, room.y2 - 1);
            if(tileAt(x,y).blocksMovement())
            {
                continue;
            }
            wsl::Vector2i newPos(x,y);
            bool entityBlocked = false;
            for(int k = 0; k < entityList->size(); ++k)
            {
                if(entityList->at(k).pos() == newPos)
                {
                    entityBlocked = true;
                    break;
                }
            }
            if(!entityBlocked)
            {
                if(wsl::randomBool(0.8))
                {
                    Entity monster(newPos, wsl::Glyph('S',wsl::Color::LtGrey, wsl::Color::Black), 6);
                    entityList->push_back(monster);
                }
                else
                {
                    Entity monster(newPos, wsl::Glyph('Z', wsl::Color::Red, wsl::Color::Black), 6);
                    entityList->push_back(monster);
                }
            }
        }
    }
}
