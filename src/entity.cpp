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
    inventory_ = nullptr;
    level_ = nullptr;
} 

Entity::Entity(const Entity & other)
{
    game_ = other.game_;
    pos_ = other.pos_;
    glyph_ = other.glyph_;
    name_ = std::make_shared<std::string>(*other.name_.get());
    mask_ = other.mask_;
    actor_ = nullptr;
    item_ = nullptr;
    inventory_ = nullptr;
    level_ = nullptr;
    
    if(isActor())
    {
        makeActor(*(other.actor_.get()));
    }
    if(isItem())
    {
        makeItem(*(other.item_.get()));
    }
    if(hasInventory())
    {
        makeInventory();
    }
    if(hasLevel())
    {
        makeLevel(*(other.level_.get()));
    }
}

// Entity & operator=(const Entity & other)
// {
//     Entity result;
//     result.name_ = std::make_shared<std::string>(other.name());
//     result.mask_ = other.mask();
//     result.isActor() ? result.makeActor(other.actor()) : result.actor_ = nullptr;
//     result.isItem() ? result.makeItem(other.item()) : result.item_ = nullptr;
//     hasInventory() ? result.makeInventory(other.inventory()) : result.inventory_ = nullptr;
//     hasLevel() ? result.makeLevel(other.level()) : result.level_ = nullptr;
//     return result;
// }

void Entity::move(wsl::Vector2i delta)
{
    pos_ += delta;
}

const wsl::Vector2i & Entity::pos()
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

