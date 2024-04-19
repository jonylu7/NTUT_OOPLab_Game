//
// Created by 盧威任 on 3/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MAPUTILITY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MAPUTILITY_HPP
#include "Tile.hpp"
#include <vector>
class MapUtil {
public:
    static std::vector<std::shared_ptr<TileClass>>
    readMapAndTileSet(std::vector<int> map,
                      std::unordered_map<int, TileClass> tileset) {
        std::vector<std::shared_ptr<TileClass>> maps;
        for (int i = 0; i < map.size(); i++) {
            maps.push_back(std::make_shared<TileClass>(tileset[map[i]]));
        }
        return maps;
    }

    static glm::vec2 ScreenToGlobalCoord(glm::vec2 screenCoord) {
        auto proj = CameraClass::getProjectionMatrix();
        auto view = CameraClass::getViewMatrix();
        glm::vec2 offset = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
        glm::vec4 vec4ScreenCoord(
            {screenCoord[0] + CameraClass::getPosition().x + offset.x,
             screenCoord[1] + CameraClass::getPosition().y + offset.y, 0.F,
             1.F});
        glm::vec4 global(vec4ScreenCoord);

        return glm::vec2(global[0], global[1]);
    }

    static glm::vec2 GlobalCoordToCellCoord(glm::vec2 globalCoord) {
        return glm::vec2(int(globalCoord[0] / CELL_SIZE.x),
                         int(globalCoord[1] / CELL_SIZE.y));
    }

    static glm::vec2 CellCoordToGlobal(const glm::vec2 cellCoord) {
        return glm::vec2(int(cellCoord[0] * CELL_SIZE.x) + 0.5 * CELL_SIZE.x,
                         int(cellCoord[1] * CELL_SIZE.y) + 0.5 * CELL_SIZE.y);
    }

    static glm::vec2 PositionStickToGrid(glm::vec2 location) {
        int _x = location.x / CELL_SIZE.x;
        int _y = location.y / CELL_SIZE.y;
        return {_x * CELL_SIZE.x, _y * CELL_SIZE.y};
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAPUTILITY_HPP
