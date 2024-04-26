//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP

#include "Selectable.hpp"

#include "Mechanics/GameObjectID.hpp"

#include "SpriteSheet.hpp"

#include "Structure/Structure.hpp"
#include <unordered_map>
class TileClass {
public:
    TileClass(const unitType unittype, bool buildable, bool walkable,
              bool clickable, std::string tileimagepath)
        : m_Id(GameObjectID(unittype, HouseType::NONE)),
          m_Clickable(clickable),
          m_TerrainBuildable(buildable),
          m_TerrainWalkable(walkable),
          m_TileImagePath(tileimagepath) {}

    TileClass(const unitType unittype, bool buildable, bool walkable,
              bool clickable)
        : m_Id(GameObjectID(unittype, HouseType::NONE)),
          m_TerrainBuildable(buildable),
          m_TerrainWalkable(walkable),
          m_Clickable(clickable),
          m_TileImagePath("") {}
    TileClass()
        : m_Id(GameObjectID(unitType::null, HouseType::NONE)),
          m_TerrainBuildable(true),
          m_TerrainWalkable(true),
          m_Clickable(true),
          m_TileImagePath(""){};
    ~TileClass() {}

    bool getWalkable() { return m_TerrainWalkable; };
    bool getBuildable() { return m_TerrainBuildable; };
    bool getClickable() { return m_Clickable; };
    std::string getTileImagePath() { return m_TileImagePath; }
    std::vector<std::shared_ptr<Selectable>> getSelectableObjects() {
        return m_SelectableObjects;
    }

    void setWalkable(bool value) { m_TerrainWalkable = value; };
    void setBuildable(bool value) { m_TerrainBuildable = value; };
    void setClickable(bool value) { m_Clickable = value; };
    void setTileImage(std::string path) { m_TileImagePath = path; };

    void pushSelectableObjects(std::shared_ptr<Selectable> object) {
        m_SelectableObjects.push_back(object);
    }

    void clearSelectableObjects() { m_SelectableObjects.clear(); }
    TileClass &operator=(const TileClass &tile) {
        this->m_TerrainWalkable = tile.m_TerrainWalkable;
        this->m_Clickable = tile.m_Clickable;
        this->m_TileImagePath = tile.m_TileImagePath;

        this->m_TerrainBuildable = tile.m_TerrainBuildable;
        this->m_Id = tile.m_Id;
        return *this;
    }

private:
    bool m_TerrainWalkable;
    bool m_TerrainBuildable;
    bool m_Clickable;
    std::vector<std::shared_ptr<Selectable>> m_SelectableObjects;

    std::string m_TileImagePath;
    GameObjectID m_Id;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
