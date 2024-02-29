//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP

#include "glm/vec2.hpp"
#include "pch.hpp"

typedef unsigned int CELL;

class MapClass {

    void Init() {
        // read tileset
        //
    }

    void Draw() {
        // draw tiles, calling the "draw by camera".
        // TODO: new feature, draw tiles only within given range
    }

    static glm::vec2 ScreenToMapCoord(glm::vec2 screenCoord) {
        // get camera location
        // caculate the "camera center location to map coord (which cell)"
        // caculate screen coord to map coord

        CELL x;
        CELL y;
        return glm::vec2(x, y);
    }

    // function: given map coord, return status of the dedicated tile, walkable?
    // buildable?

private:
    CELL MapWdith;
    CELL MapHeight;
    // vector data, map, at where to draw what tiles
    // tileset data: ID and given filepath/image/spritesheet/spritesheetindex??
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
