//
// Created by 盧威任 on 3/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MAPUTILITY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MAPUTILITY_HPP
#include "Camera.hpp"
#include "pch.hpp"
#include <vector>
class MapUtil {
public:
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
    static float findDistance(glm::vec2 cell1, glm::vec2 cell2) {
        float dx = cell2.x-cell1.x;
        float dy = cell2.y-cell1.y;
        return sqrt(dx * dx + dy * dy);
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAPUTILITY_HPP
