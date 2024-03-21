//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP

#include "Grid.hpp"
#include "Tile.hpp"
#include "glm/vec2.hpp"
#include "pch.hpp"

typedef unsigned int CELL;

class MapClass : public Core::Drawable {
public:
    MapClass() {}
    void Init(CELL width, CELL height) {
        m_MapWdith = width;
        m_MapHeight = height;
        for (int i = 0; i < m_MapHeight; i++) {
            std::vector<std::shared_ptr<TileClass>> row;
            for (int j = 0; j < m_MapWdith; j++) {
                row.push_back(std::make_shared<TileClass>());
            }
            m_Map.push_back(row);
        }
        InitGrid();
    }
    void Init(std::vector<std::vector<std::shared_ptr<TileClass>>> map,
              CELL width, CELL height) {
        m_Map = map;
        m_MapWdith = width;
        m_MapHeight = height;
        InitGrid();
    }

    void Draw(const Util::Transform &trans, const float zindex) override {

        Util::Transform mapTrans;
        mapTrans.translation = m_MapPosition;
        m_Grid.DrawUsingCamera(mapTrans, 0.1);

        /*
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
         */
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

    static glm::vec2 CellCoordToGlobal(glm::vec2 cellCoord) {
        return glm::vec2(int(cellCoord[0] * CELL_SIZE.x) + 0.5 * CELL_SIZE.x,
                         int(cellCoord[1] * CELL_SIZE.y) + 0.5 * CELL_SIZE.y);
    }

    std::shared_ptr<TileClass> getTileByCellPosition(glm::vec2 position) {
        if (position.x > m_MapWdith - 1 || position.y > m_MapHeight - 1 ||
            position.x < 0 || position.y < 0) {
            LOG_DEBUG("False Position Getting");
            return std::make_shared<TileClass>(unitType::null, 0, 0, 0,
                                               std::shared_ptr<Util::Image>());
        }
        return m_Map[position.x][position.y];
    }

    void setTileByCellPosition(glm::vec2 position,
                               std::shared_ptr<TileClass> tile) {
        if (position.x > m_MapWdith - 1 || position.y > m_MapHeight - 1 ||
            position.x < 0 || position.y < 0) {
            LOG_DEBUG("False Position Setting");
            return;
        }
        m_Map[position.x][position.y] = tile;
    }

    void setGridActive(bool value) { m_Grid.SetActivate(value); }

protected:
    void InitGrid() {
        std::vector<Line> lineV;

        auto width = CELL_SIZE.x * m_MapWdith;
        auto height = CELL_SIZE.y * m_MapHeight;
        for (int i = 0; i < m_MapWdith + 1; i++) {
            // horz
            lineV.push_back(Line(glm::vec2(0, i * CELL_SIZE.y),
                                 glm::vec2(width, i * CELL_SIZE.y)));
        }
        for (int j = 0; j < m_MapHeight + 1; j++) {
            // height
            lineV.push_back(Line(glm::vec2(j * CELL_SIZE.x, 0),
                                 glm::vec2(j * CELL_SIZE.x, height)));
        }

        m_Grid.Start(lineV);
        m_Grid.SetActivate(true);
    }

private:
    CELL m_MapWdith;
    CELL m_MapHeight;
    glm::vec2 m_MapPosition = {0, 0};
    std::vector<std::vector<std::shared_ptr<TileClass>>> m_Map;
    int m_ZIndex = 0;
    Grid m_Grid;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
