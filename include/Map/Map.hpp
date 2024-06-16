//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
#include "Avatar/Avatar.hpp"
#include "Display/Grid.hpp"
#include "Display/ImageArray.hpp"
#include "Map/Tile.hpp"
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
    bool ifWalkable(glm::vec2 position) {
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

    void setAvatarByCellPosition(std::shared_ptr<Avatar> avatar,
                                 glm::vec2 position) {
        getTileByCellPosition(position)->setBuildable(false);
        getTileByCellPosition(position)->pushAvatars(avatar);
    }

    void removeAvatarByCellPosition(std::shared_ptr<Avatar> avatar,
                                    glm::vec2 position) {
        getTileByCellPosition(position)->removeAvatar(avatar);
    }

    void removeStrcutureByCellPosition(glm::vec2 position) {
        getTileByCellPosition(position)->removeStructure();
    }

    glm::vec2 findEnemyInRange(int attackRange, glm::vec2 myCell,
                               HouseType myHouse) {
        glm::vec2 NullPos = {-1, -1};
        int x, y = 1;
        int r = 1;
        for (r = 1; r < attackRange; r++) {
            y = r;
            for (x = -1 * r; x < r; x++) {
                if (getTileByCellPosition({myCell.x + x, myCell.y + y})
                        ->ifEnemyAtTile(myHouse)) {
                    return {myCell.x + x, myCell.y + y};
                }
            }
            for (y = r - 1; y >= -1 * r; y--) {
                if (getTileByCellPosition({myCell.x + x, myCell.y + y})
                        ->ifEnemyAtTile(myHouse)) {
                    return {myCell.x + x, myCell.y + y};
                }
            }
            for (x = r - 1; x > -1 * r; x--) {
                if (getTileByCellPosition({myCell.x + x, myCell.y + y})
                        ->ifEnemyAtTile(myHouse)) {
                    return {myCell.x + x, myCell.y + y};
                }
            }
            for (y = -1 * r + 1; y < r; y++) {
                if (getTileByCellPosition({myCell.x + x, myCell.y + y})
                        ->ifEnemyAtTile(myHouse)) {
                    return {myCell.x + x, myCell.y + y};
                }
            }
        }
        return NullPos;
    }

    int getWidth() { return m_MapWdith; }
    int getHeight() { return m_MapHeight; }

protected:
    void InitGrid();

private:
    const glm::vec2 m_MapTransShift = {10, -10};
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
