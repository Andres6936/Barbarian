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

#include "../include/tile.hpp"

const Tile Tile::Floor(Tile::Flags::NONE, wsl::Glyph('.', wsl::Color::LtGrey));
const Tile Tile::Wall(Tile::Flags::BLOCKS_MOVEMENT | Tile::Flags::BLOCKS_LIGHT, wsl::Glyph('#', wsl::Color::Grey, wsl::Color::DkGrey));
