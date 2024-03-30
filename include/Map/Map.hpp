//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
#include "Grid.hpp"
#include "Map/Tile.hpp"
#include "Util/ImageArray.hpp"
#include "glm/vec2.hpp"
#include "pch.hpp"
#include <vector>

class MapClass : public Core::Drawable {
public:
    void Init(unsigned int width, unsigned int height) {
        m_MapWdith = width;
        m_MapHeight = height;
        for (int i = 0; i < m_MapHeight; i++) {
            std::vector<std::shared_ptr<TileClass>> row;
            for (int j = 0; j < m_MapWdith; j++) {
                row.push_back(std::make_shared<TileClass>());
            }
            MapClass::m_Map.push_back(row);
        }
        InitGrid();
    }
    void Init(std::vector<std::vector<std::shared_ptr<TileClass>>> map,
              unsigned int width, unsigned int height) {

        m_MapWdith = width;
        m_MapHeight = height;
        m_Map = map;

        // m_Map = map;

        // InitGrid();

        for (int i = 0; i < m_Map.size(); i++) {
            for (int j = 0; j < m_Map[i].size(); j++) {

                auto findResult = m_Tiles.find(m_Map[i][j]->getTileImagePath());
                if (findResult != m_Tiles.end()) {
                    m_Tiles[m_Map[i][j]->getTileImagePath()].push_back(
                        glm::vec2(i, m_MapHeight - j));
                } else {
                    m_Tiles[m_Map[i][j]->getTileImagePath()] =
                        std::vector<glm::vec2>({glm::vec2(i, m_MapHeight - j)});
                }
            }
        }

        for (auto pair : m_Tiles) {
            std::string motherPath = "../assets/sprites/temperate_sprite/";
            m_Images.push_back(std::make_shared<Util::ImageArray>(
                motherPath + pair.first, pair.second));
        }
    }

    void Draw(const Util::Transform &trans, const float zindex) override {

        Util::Transform mapTrans;
        mapTrans.translation = m_MapPosition;
        for (auto i : m_Images) {
            i->DrawUsingCamera(mapTrans, 3);
        }

        // m_Grid.DrawUsingCamera(mapTrans, 0.1);
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

    std::shared_ptr<TileClass> getTileByCellPosition(glm::vec2 position) {

        if (position.x > m_MapWdith - 1 || position.y > m_MapHeight - 1 ||
            position.x < 0 || position.y < 0) {
            LOG_DEBUG("False Position Getting");
            return std::make_shared<TileClass>(unitType::null, 0, 0, 0, "");
        }
        return m_Map[position.x][position.y];
    }
    bool getWalkable(glm::vec2 position) {
        return getTileByCellPosition(position)->getWalkable();
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
    std::vector<std::shared_ptr<Util::ImageArray>> m_Images;
    std::unordered_map<std::string, std::vector<glm::vec2>> m_Tiles;
    unsigned int m_MapWdith = 0;
    unsigned int m_MapHeight = 0;
    glm::vec2 m_MapPosition = {0, 0};
    std::vector<std::vector<std::shared_ptr<TileClass>>> m_Map;
    int m_ZIndex = 0;
    Grid m_Grid;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
