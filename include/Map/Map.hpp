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
    MapClass() {}
    ~MapClass() {}
    void Init(unsigned int width, unsigned int height);
    void Init(std::vector<std::vector<std::shared_ptr<TileClass>>> map,
              unsigned int width, unsigned int height);
    void Draw(const Util::Transform &trans, const float zindex) override;

    std::shared_ptr<TileClass> getTileByCellPosition(glm::vec2 position);
    bool getWalkable(glm::vec2 position) {
        return getTileByCellPosition(position)->getWalkable();
    }

    void setTileByCellPosition(glm::vec2 position,
                               std::shared_ptr<TileClass> tile);

    void setGridActive(bool value) { m_Grid.SetActivate(value); }

    void builtStructureByCellPosition(std::shared_ptr<Structure> structure,
                                      std::vector<glm::vec2> coords) {
        for (auto i : coords) {
            getTileByCellPosition(i)->setBuildable(false);
            getTileByCellPosition(i)->setWalkable(false);
            getTileByCellPosition(i)->setStructure(structure);
        }
    }

    void setUnitsByCellPosition(std::shared_ptr<Avatar> avatar,
                                glm::vec2 position) {
        getTileByCellPosition(position)->setBuildable(false);
        getTileByCellPosition(position)->pushAvatars(avatar);
    }

protected:
    void InitGrid();

private:
    std::vector<std::shared_ptr<Util::ImageArray>> m_Images;
    std::unordered_map<std::string, std::vector<glm::vec2>> m_Tiles;
    unsigned int m_MapWdith = 0;
    unsigned int m_MapHeight = 0;
    glm::vec2 m_MapPosition = {0, 0};
    std::vector<std::vector<std::shared_ptr<TileClass>>> m_Map;
    int m_ZIndex = 0;
    Grid m_Grid;
    std::string m_spriteFolder = "../assets/sprites/temperate_sprite/";
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
