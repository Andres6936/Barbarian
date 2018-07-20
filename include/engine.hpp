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
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <string>
#include <array>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "console.hpp"
#include "input_handlers.hpp"
#include "entity.hpp"
#include "game_map.hpp"
#include "fov.hpp"
#include "texture.hpp"
#include "sprite.hpp"
#include "dllist.hpp"

enum class GameState : uint8_t
{
    PLAYERS_TURN,
    ENEMY_TURN,
    GAME_OVER,
    MSG_WAIT
};

class Engine
{
    public:
        Engine();

        bool running() { return running_; }
        bool init();
        void cleanup();
        void handleEvents();
        void update();
        void draw();

        int windowWidth() { return windowWidth_; }
        int windowHeight() { return windowHeight_; }

        void playerDied() { gameState_ = GameState::GAME_OVER; }
        void addMessage(std::string msg);
        void newGame();

        GameMap * gameMap() { return gameMap_.get(); }
        wsl::DLList<Entity> * entityList() { return &entityList_; }
        Entity * player() { return player_; }
        std::vector<wsl::Vector2i> * visible() { return visible_.get(); }

    private:
        bool running_;

        // Console/Graphics
        int spriteSize_;
        int consoleWidth_;
        int consoleHeight_;
        int windowWidth_;
        int windowHeight_;
        std::string windowTitle_;

        std::unique_ptr<wsl::Console> console_;
        
        SDL_Window * window_;
        SDL_Renderer * renderer_;
        wsl::Texture * spriteSheet_;

        std::array<wsl::Rect, 256> spriteRects_;
        int spriteIndex_(int x, int y) { return (x + (y*consoleWidth_)); }

        // Game Map
        std::unique_ptr<GameMap> gameMap_;
        int maxRoomSize_; // Do these three variables need to be stored?
        int minRoomSize_;
        int maxRooms_;
        
        // FoV
        std::unique_ptr< std::vector<wsl::Vector2i> > visible_; 

        // Input Handling
        void handleKeys_(int key);
        
        // Entities
        int ACTION_COST;
        Entity * player_;
        wsl::DLList<Entity> entityList_;
        wsl::DLList<Entity *> schedule_;
        Entity * curActor_;

        // Game state
        GameState gameState_;

        // GUI
        wsl::DLList<std::string> msgList_;
        std::string currentMsg_;
};

#endif //ENGINE_HPP
