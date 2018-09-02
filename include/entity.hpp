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
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <memory>
#include <string>

#include "dllist.hpp"
#include "pqlist.hpp"
#include "vector.hpp"
#include "console.hpp"
#include "bitflag.hpp"

class Actor : public wsl::BitFlag
{
    public:
        Actor(int s = 50, int v = 4, int mH = 30, int d = 1, int p = 6, int x = 0);
        
        // enum Action
        // {
        //     None,
        //     Attack,
        //     Move,
        //     Rest
        // };
        
        enum Flags : uint16_t
        {
            NONE = 0,
            STATUS_CONFUSED =  0x002,
            EQUIP_MAIN_HAND = 0x004,
            EQUIP_OFF_HAND = 0x008,
            EQUIP_BODY = 0x010,
            EQUIP_BACK = 0x020,
            EQUIP_LRING = 0x040,
            EQUIP_RRING = 0x080,
            EQUIP_BOOTS = 0x100,
            EQUIP_RANGED = 0x200,
            EQUIP_AMMO = 0x400
        };

        int speed;
        int vision;
        int energy;
        int maxHP;
        int HP;
        int defense;
        int power;
        int xp;

        template<class Archive>
        void serialize(Archive & ar)
        {
            ar(mask_);
            ar(speed);
            ar(vision);
            ar(energy);
            ar(maxHP);
            ar(HP);
            ar(defense);
            ar(power);
            ar(xp);
        }
};

class Item : public wsl::BitFlag
{
    public:
        Item(int u = 0, int q = 0, bool s = false);
        enum Flags : uint8_t
        {
            NONE = 0,
            HEAL = 0x002,
            CAST_LIGHTNING = 0x004,
            POTION = 0x008,
            SCROLL = 0x010,
            CAST_FIREBALL = 0x020,
            CAST_FIREBOLT = 0x040,
            EQUIP = 0x080
        };
        bool carried;
        bool stackable;
        int quantity;
        // UseFunction useFunction;
        template<class Archive>
        void serialize(Archive & ar)
        {
            ar(mask_);
            ar(carried);
            ar(stackable);
            ar(quantity);
        }
};

class Equipment : public wsl::BitFlag
{
    public:
        Equipment(int s = 0, int p = 0, int d = 0, int h = 0);
        enum Flags: uint16_t
        {
            NONE = 0,
            EQUIPPED = 0x002,
            MAIN_HAND = 0x004,
            OFF_HAND = 0x008,
            BODY = 0x010,
            BACK = 0x020,
            LRING = 0x040,
            RRING = 0x080,
            BOOTS = 0x100,
            RANGED = 0x200,
            AMMO = 0x400
        };
        int powerBonus;
        int defenseBonus;
        int healthBonus;

        template<class Archive>
        void serialize(Archive & ar)
        {
            ar(mask_);
            ar(powerBonus);
            ar(defenseBonus);
            ar(healthBonus);
        }
};

class Level
{
    public:
        Level(int cLvl = 1, int cXP = 0, int lvlUB = 200, int lvlUF = 150);

        int currentLevel; // Current level of entity
        int currentXP; // Current experience of entity, resets on level up
        int levelUpBase; // Base xp needed, used in level up formula 'levelUpBase + (currentLevel * levelUpFactor)'
        int levelUpFactor; // see above

        template<class Archive>
        void serialize(Archive & ar)
        {
            ar(currentLevel);
            ar(currentXP);
            ar(levelUpBase);
            ar(levelUpFactor);
        }
};

// class Entity;
// class Inventory
// {
//     public:
//         Inventory();
//
//         uint8_t maxCapacity;
//         uint8_t capacity;
//         wsl::DLList<Entity> items;
// };

class Engine;
class Entity : public wsl::BitFlag
{
    public:
        Entity();
        Entity(Engine * game, wsl::Vector2i pos, wsl::Glyph glyph, std::string name, int wt = 0, int minLvl = 0);

        Entity(const Entity & other); // Copy constructor
        friend void swap(Entity & first, Entity & other) // Copy/Swap idiom?
        {
            using std::swap;
            swap(first.game_, other.game_);
            swap(first.pos_, other.pos_);
            swap(first.glyph_, other.glyph_);
            swap(first.weight_, other.weight_);
            swap(first.minLvl_, other.minLvl_);
            swap(first.name_, other.name_);
            swap(first.mask_, other.mask_);
            swap(first.actor_, other.actor_);
            swap(first.item_, other.item_);
            swap(first.inventory_, other.inventory_);
            swap(first.level_, other.level_);
            swap(first.equipment_, other.equipment_);
        }
        Entity & operator=(Entity other); // Copy assignment
        // Do I need a user defined destructor? memory is handled via unique/shared ptrs...

        // Component flags
        enum Flags : uint16_t
        {
            NONE = 0,
            POS = 0x0002,
            GLYPH = 0x0004,
            VISION = 0X0008,
            BLOCKS = 0x0010,
            ACTOR = 0x0020,
            AI = 0x0040,
            DEAD = 0x0080,
            ITEM = 0x0100,
            INVENTORY = 0x0200,
            LEVEL = 0x0400,
            EQUIPMENT = 0x0800
        };
        
        // Component checks
        bool hasPos() { return check(Flags::POS); }
        bool hasGlyph() { return check(Flags::GLYPH); }
        bool hasVision() { return check(Flags::VISION); }
        bool blocks() { return check(Flags::BLOCKS); }
        bool isActor() { return check(Flags::ACTOR); }
        bool isItem() { return check(Flags::ITEM); }
        bool hasInventory() { return check(Flags::INVENTORY); }
        bool hasLevel() { return check(Flags::LEVEL); }
        bool isEquipment() { return check(Flags::EQUIPMENT); }

        // Generic Entity functions
        void move(wsl::Vector2i delta);
        wsl::Vector2i & pos();
        void setPos(wsl::Vector2i pos);
        wsl::Glyph & glyph();
        // std::string name() { return (name_.size() == 0 ? "foo" : name_); }
        std::string & name() { return name_; }
        int & wt() { return weight_; }
        int & minLvl() { return minLvl_; }
        
        // Actor functions
        void makeActor(Actor actor);
        Actor actor() { return *(actor_.get()); }
        // void grantEnergy();
        // int & energy() { return energy_; }
        // int & speed() { return speed_; }
        // void setNextAction(Action action);
        int & hp() { return actor_->HP; }
        int & baseMaxHP() { return actor_->maxHP; }
        int & baseDefense() { return actor_->defense; }
        int & basePower() { return actor_->power; }
        int maxHP();
        int defense();
        int power();
        int vision() { return actor_->vision; }
        int xp() { return actor_->xp; }
        void takeDamage(int damage);
        void heal(int qty);
        void dealDamage(Entity * target, int damage);
        bool update();

        // Item Functions
        void makeItem(Item item);
        Item item() { return *(item_.get()); }
        bool carried() { return item_->carried; }
        void pickup(Entity * itemEntity);
        void drop(int index);
        void use(int index);
        int itemPriority();
        int & quantity() { return item_->quantity; }
        bool stackable() { return item_->stackable; }

        // Inventory functions
        void makeInventory();
        wsl::PQList<Entity, int> * inventory() { return inventory_.get(); }

        // Level functions
        void makeLevel(Level level);
        Level level() { return *(level_.get()); }
        int currentLevel() const { return level_->currentLevel; }
        int currentXP() const { return level_->currentXP; }
        bool addXP(int xp);
        int xpToNextLevel(); 

        // Equipment functions
        void makeEquipment(Equipment equipment);
        Equipment equipment() { return *(equipment_.get()); }
        int powerBonus() { return equipment_->powerBonus; }
        int defenseBonus() { return equipment_->defenseBonus; }
        int healthBonus() { return equipment_->healthBonus; }
        bool equipped() { return equipment_->check(Equipment::Flags::EQUIPPED); }
        void toggleEquip(Entity * item);
        void equip(Entity * item);
        void unequip(Entity * item);
        bool isMainHand() { return equipment_->check(Equipment::Flags::MAIN_HAND); }
        bool isOffHand() { return equipment_->check(Equipment::Flags::OFF_HAND); }
        Entity * itemInSlot(int slotFlag);
        int getSlot(Entity * item);
        bool hasEquippedInSlot(int equipmentSlot);
        int actorSlot(int equipmentSlot);

        Engine * game() { return game_; }
        void setGame(Engine * game) { game_ = game; }
    private:
        Engine * game_;

        // Components
        wsl::Vector2i pos_; 
        wsl::Glyph glyph_; 
        int weight_;
        int minLvl_;
        // std::shared_ptr<std::string> name_;
        std::string name_;
        std::shared_ptr<Actor> actor_;
        std::shared_ptr<Item> item_;
        // std::shared_ptr< wsl::DLList<Entity> > inventory_;
        std::shared_ptr< wsl::PQList<Entity, int> > inventory_;
        std::shared_ptr<Level> level_;
        std::shared_ptr<Equipment> equipment_;

        // Use Functions
        bool use_heal_();
        bool use_cast_lightning_();
        bool use_cast_firebolt_();
        bool use_cast_fireball_();
};

#endif //ENTITY_HPP
