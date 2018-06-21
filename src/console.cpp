/*
* Barbarian!
* Copyright (C) 2018
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


#include "../include/console.hpp"

namespace wsl
{

Console::Console(int width, int height) : width_(width), height_(height)
{
    screen_.assign(width_ * height_, Glyph(' '));
}

Glyph Console::get(int x, int y)
{
    return screen_[x + (y * width_)];
}

void Console::put(int x, int y, Glyph glyph)
{
    screen_[x + (y * width_)] = glyph;
}

void Console::clear(int x, int y)
{
    screen_[x + (y * width_)] = Glyph(' ');
}

void Console::flush()
{
    for(int i = 0; i < screen_.size(); ++i)
    {
        screen_[i] = Glyph(' ');
    }
}
} // namespace wsl
