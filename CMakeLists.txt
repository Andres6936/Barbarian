CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Barbarian)

SET(CMAKE_CXX_STANDARD 17)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(Include)

ADD_EXECUTABLE(Barbarian
        Source/color.cpp
        Source/console.cpp
        Source/engine.cpp
        Source/engine_draw.cpp
        Source/engine_draw_game.cpp
        Source/engine_draw_inventory.cpp
        Source/engine_draw_levelup.cpp
        Source/engine_draw_RIP.cpp
        Source/engine_draw_target.cpp
        Source/engine_draw_title.cpp
        Source/engine_events.cpp
        Source/engine_events_inventory.cpp
        Source/engine_events_levelup.cpp
        Source/engine_events_player.cpp
        Source/engine_events_target.cpp
        Source/engine_events_title.cpp
        Source/engine_fileIO.cpp
        Source/engine_update.cpp
        Source/entity.cpp
        Source/entity_actor.cpp
        Source/entity_equipment.cpp
        Source/entity_item.cpp
        Source/entity_level.cpp
        Source/fov.cpp
        Source/game_map.cpp
        Source/input_handlers.cpp
        Source/items.cpp
        Source/main.cpp
        Source/monsters.cpp
        Source/pathfinding.cpp
        Source/random.cpp
        Source/sprite.cpp
        Source/texture.cpp
        Source/tile.cpp)

TARGET_LINK_LIBRARIES(Barbarian ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})