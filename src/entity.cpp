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

#include "../include/entity.hpp"
#include "../include/game_map.hpp"
#include "../include/engine.hpp"
#include "../include/pathfinding.hpp"

Entity::Entity()
{
    game_ = nullptr;
    pos_ = wsl::Vector2i();
    glyph_ = wsl::Glyph();
    name_ = std::make_shared<std::string>("");
    mask_ = Flags::NONE;
    actor_ = nullptr;
    item_ = nullptr;
    inventory_ = nullptr;
    level_ = nullptr;
}

Entity::Entity(Engine * game, wsl::Vector2i pos, wsl::Glyph glyph, std::string name) : game_(game), pos_(pos), glyph_(glyph)
{
    name_ = std::make_shared<std::string>(name);
    mask_ = Flags::POS | Flags::GLYPH;
    actor_ = nullptr;
    item_ = nullptr;
    level_ = nullptr;
} 

void Entity::move(wsl::Vector2i delta)
{
    pos_ += delta;
}

wsl::Vector2i Entity::pos()
{
    return pos_;
}

void Entity::setPos(wsl::Vector2i pos)
{
    pos_ = pos;
}

wsl::Glyph & Entity::glyph()
{
    return glyph_;
}

