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

#include "../Include/entity.hpp"
#include "../Include/game_map.hpp"
#include "../Include/engine.hpp"
#include "../Include/pathfinding.hpp"

Entity::Entity()
{
    game_ = nullptr;
    pos_ = wsl::Vector2i();
    glyph_ = wsl::Glyph();
    // name_ = std::make_shared<std::string>("");
    name_ = "foo";
    mask_ = Flags::NONE;
    actor_ = nullptr;
    item_ = nullptr;
    inventory_ = nullptr;
    level_ = nullptr;
    equipment_ = nullptr;
    weight_ = 0;
    minLvl_ = 0;
}

Entity::Entity(Engine * game, wsl::Vector2i pos, wsl::Glyph glyph, std::string name, int wt, int minLvl) : game_(game), pos_(pos), glyph_(glyph),
                                                                                                           weight_(wt), minLvl_(minLvl)
{
    // name_ = std::make_shared<std::string>(name);
    name_ = name;
    mask_ = Flags::POS | Flags::GLYPH;
    actor_ = nullptr;
    item_ = nullptr;
    inventory_ = nullptr;
    level_ = nullptr;
    equipment_ = nullptr;
} 

Entity::Entity(const Entity & other)
{
    game_ = other.game_;
    pos_ = other.pos_;
    glyph_ = other.glyph_;
    weight_ = other.weight_;
    minLvl_ = other.minLvl_;
    // name_ = std::make_shared<std::string>(*other.name_.get());
    name_ = (other.name_.size() <= 0 ? "foo" : other.name_);
    mask_ = other.mask_;
    actor_ = nullptr;
    item_ = nullptr;
    inventory_ = nullptr;
    level_ = nullptr;
    equipment_ = nullptr;
    
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
        for(wsl::PQNode<Entity, int> * node = other.inventory_->head(); node != NULL; node = node->next)
        {
            inventory_->push(node->data, node->priority);
        }
    }
    if(hasLevel())
    {
        makeLevel(*(other.level_.get()));
    }
    if(isEquipment())
    {
        makeEquipment(*(other.equipment_.get()));
    }
}


Entity & Entity::operator=(Entity other)
{
    swap(*this, other);
    return *this;
}

void Entity::move(wsl::Vector2i delta)
{
    pos_ += delta;
}

wsl::Vector2i & Entity::pos()
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

