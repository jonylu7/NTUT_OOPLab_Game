//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP

#include "Tile.hpp"
#include "glm/vec2.hpp"
#include "pch.hpp"

typedef unsigned int CELL;

class MapClass {
    MapClass(std::vector<TileClass> tileclasses,
             std::shared_ptr<SpriteSheet> spriteSheet,
             std::vector<std::shared_ptr<TileClass>>)
        : m_TileSet(std::make_shared<TileSet>(tileclasses, spriteSheet)) {}

    void Draw() {
        // TODO: new feature, draw tiles only within given range
        Util::Transform trans;
        int zIndex = 0;
        for (int i = 0; i < m_MapHeight; i++) {
            for (int j = 0; j < m_MapWdith; j++) {
                m_TileSet->DrawTileSetByClass(*m_Map[i][j], trans, zIndex);
            }
        }
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
    CELL m_MapWdith;
    CELL m_MapHeight;
    std::vector<std::vector<std::shared_ptr<TileClass>>> m_Map;
    std::shared_ptr<TileSet> m_TileSet;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
