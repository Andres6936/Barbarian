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

#pragma once
#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include <memory>
#include "tile.hpp"
#include "rect.hpp"
#include "random.hpp"
#include "entity.hpp"

namespace wsl
{
    class RNGState;
}
class Engine;
class GameMap
{
    public:
        GameMap(Engine * owner = NULL, int w = 80, int h = 40, int roomSizeMax = 10, int roomSizeMin = 6, int numRoomsMax = 30);

        GameMap(const GameMap & other); // copy constructor
        friend void swap(GameMap & first, GameMap & other)
        {
            using std::swap;
            swap(first.tiles, other.tiles);
            swap(first.rooms, other.rooms);
            swap(first.owner_, other.owner_);
            swap(first.rngState_, other.rngState_);
            swap(first.width_, other.width_);
            swap(first.height_, other.height_);
            swap(first.roomSizeMax_, other.roomSizeMax_);
            swap(first.roomSizeMin_, other.roomSizeMin_);
            swap(first.numRoomsMax_, other.numRoomsMax_);
            swap(first.currentLevel_, other.currentLevel_);
            swap(first.monsterWeights_, other.monsterWeights_);
        }
        GameMap & operator=(GameMap other); // Copy assignment

        // static std::array<wsl::Vector2i, 4> DIRS;
        static std::array<wsl::Vector2i, 8> DIRS;
        int width() { return width_; }
        int height() { return height_; }

        inline int index(int x, int y) { return (x + (y * width_)); }           
        bool isBlocked(int x, int y);
        bool isBlocked(wsl::Vector2i pos);

        Tile & tileAt(int x, int y);
        Tile & tileAt(wsl::Vector2i pos);
        Entity * entityAt(wsl::Vector2i pos);
        Entity * entityAt(int x, int y);
        Entity * itemAt(wsl::Vector2i pos);
        Entity * itemAt(int x, int y);
        Entity * actorAt(wsl::Vector2i pos);
        Entity * actorAt(int x, int y);

        Entity * closestEntityTo(wsl::Vector2i pos);
        Entity * closestEntityTo(int x, int y);
        Entity * closestActorTo(wsl::Vector2i pos);
        Entity * closestActorTo(int x, int y);
        
        void placeActors(int maxPerRoom);
        void placeItems(int max);
        
        std::vector<wsl::Vector2i> neighbors(wsl::Vector2i start);
        void setOwner(Engine * owner) { owner_ = owner; }

        void nextLevel();
        int currentLevel() const { return currentLevel_; }
        std::vector<Tile> tiles;
        std::vector<wsl::Rect> rooms;

        template<class Archive>
        void serialize(Archive & ar)
        {
            ar(width_);
            ar(height_);
            ar(roomSizeMax_);
            ar(roomSizeMin_);
            ar(numRoomsMax_);
            ar(tiles);
            ar(rooms);
            ar(currentLevel_);
            // ar(rngState_);
        }
        
    private:
        Engine * owner_;
        std::shared_ptr<wsl::RNGState> rngState_;
        // wsl::RNGState rngState_;
        int width_;
        int height_;
        int roomSizeMax_;
        int roomSizeMin_;
        int numRoomsMax_;
        int currentLevel_;
        wsl::WeightedList<Entity> monsterWeights_;

        void initTiles_();
        void initActorList_();
        void initItemList_();
        void makeMap_();
        void createRoom_(wsl::Rect room);
        void hTunnel_(int x1, int x2, int y);
        void vTunnel_(int y1, int y2, int x);

        bool inBounds_(wsl::Vector2i pos);
};

#endif //GAME_MAP_HPP
