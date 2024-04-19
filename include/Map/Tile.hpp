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
          m_Buildable(buildable),
          m_Walkable(walkable),
          m_TileImagePath(tileimagepath) {}

    TileClass(const unitType unittype, bool buildable, bool walkable,
              bool clickable)
        : m_Id(GameObjectID(unittype, HouseType::NONE)),
          m_Buildable(buildable),
          m_Walkable(walkable),
          m_Clickable(clickable),
          m_TileImagePath("") {}
    TileClass()
        : m_Id(GameObjectID(unitType::null, HouseType::NONE)),
          m_Buildable(true),
          m_Walkable(true),
          m_Clickable(true),
          m_TileImagePath(""){};
    ~TileClass() {}

    bool getWalkable() { return m_Walkable; };
    bool getBuildable() { return m_Buildable; };
    bool getClickable() { return m_Clickable; };
    std::string getTileImagePath() { return m_TileImagePath; }
    std::vector<std::shared_ptr<Selectable>> getSelectableObjects() {
        return m_SelectableObjects;
    }

    void setWalkable(bool value) { m_Walkable = value; };
    void setBuildable(bool value) { m_Buildable = value; };
    void setClickable(bool value) { m_Clickable = value; };
    void setTileImage(std::string path) { m_TileImagePath = path; };

    void pushSelectableObjects(std::shared_ptr<Selectable> object) {
        m_SelectableObjects.push_back(object);
    }

    void clearSelectableObjects() { m_SelectableObjects.clear(); }
    TileClass &operator=(const TileClass &tile) {
        this->m_Walkable = tile.m_Walkable;
        this->m_Clickable = tile.m_Clickable;
        this->m_TileImagePath = tile.m_TileImagePath;

        this->m_Buildable = tile.m_Buildable;
        this->m_Id = tile.m_Id;
        return *this;
    }

private:
    bool m_Walkable;
    bool m_Buildable;
    bool m_Clickable;
    std::vector<std::shared_ptr<Selectable>> m_SelectableObjects;

    std::string m_TileImagePath;
    GameObjectID m_Id;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
