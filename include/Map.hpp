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
public:
    MapClass() {}

    void Init(std::vector<std::shared_ptr<TileClass>> map,
              std::shared_ptr<SpriteSheet> spritesheet, CELL width,
              CELL height) {
        m_Map = map;
        m_SpriteSheet = spritesheet;
        m_MapWdith = width;
        m_MapHeight = height;
    }

    void Draw() {
        // TODO: new feature, draw tiles only within given range
        Util::Transform drawLocation = {glm::vec2(0, 0)};
        for (int i = 0; i < m_Map.size(); i++) {
            int row = int((i + 1) / m_MapWdith);
            int col = i - row * m_MapWdith;
            drawLocation.translation.x = m_SpriteSheet->getSpriteSize().x * col;
            drawLocation.translation.y = m_SpriteSheet->getSpriteSize().y * row;

            m_SpriteSheet->DrawSpriteByIndex(m_Map[i]->getSpriteSheetIndex(),
                                             drawLocation, m_ZIndex);
        }
    }

    static glm::vec2 ScreenToGlobalCoord(glm::vec2 screenCoord) {
        glm::vec2 cameraPost=CameraClass::getPosition();
        float x=cameraPost.x+screenCoord.x;
        float y=cameraPost.y+screenCoord.y;
        return glm::vec2(x, y);
    }

    // weird
    static std::vector<std::shared_ptr<TileClass>>
    readMapAndTileSet(std::vector<int> map, std::map<int, TileClass> tileset) {
        std::vector<std::shared_ptr<TileClass>> maps;
        for (int i = 0; i < map.size(); i++) {
            maps.push_back(std::make_shared<TileClass>(tileset[map[i]]));
        }
        return maps;
    }

private:
    CELL m_MapWdith;
    CELL m_MapHeight;
    glm::vec2 m_MapPosition={0,0};
    std::vector<std::shared_ptr<TileClass>> m_Map;
    std::shared_ptr<SpriteSheet> m_SpriteSheet;
    int m_ZIndex = 0;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
