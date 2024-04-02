//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
#include "Selectable.hpp"
#include "SpriteSheet.hpp"
#include "Structure/Structure.hpp"
#include "Unit/PathfindingUnit.hpp"
#include <map>
class TileClass {
public:
    TileClass(const std::string name, bool buildable, bool walkable,
              bool clickable, int spritesheetindex)
        : m_Name(name),
          m_Buildable(buildable),
          m_Walkable(walkable),
          m_Clickable(clickable) {}
    TileClass()
        : m_Name(""),
          m_Buildable(true),
          m_Walkable(true),
          m_Clickable(true) {}
    ~TileClass() {}

    bool getWalkable() { return m_Walkable; };
    bool getBuildable() { return m_Buildable; };
    bool getClickable() { return m_Clickable; };
    std::vector<std::shared_ptr<Selectable>> getSelectableObjects() {
        return m_SelectableObjects;
    }

    void setWalkable(bool value) { m_Walkable = value; };
    void setBuildable(bool value) { m_Buildable = value; };
    void setClickable(bool value) { m_Clickable = value; };

    void pushSelectableObjects(std::shared_ptr<Selectable> object) {
        m_SelectableObjects.push_back(object);
    }

    void clearSelectableObjects() { m_SelectableObjects.clear(); }

    /*
    bool operator==(const TileClass &tile) const {
        if (tile.m_Name == m_Name && m_Walkable == tile.m_Walkable &&
            m_Buildable == tile.m_Walkable) {
            return true;
        } else {
            return false;
        }
    }

    bool operator<(const TileClass &tile) const {
        if (tile.m_Name < m_Name || m_Walkable < tile.m_Walkable ||
            m_Buildable == tile.m_Walkable) {
            return true;
        } else {
            return false;
        }
    }
     */
    TileClass &operator=(const TileClass &tile) {
        this->m_Walkable = tile.m_Walkable;
        this->m_Clickable = tile.m_Clickable;
        this->m_Buildable = tile.m_Buildable;
        this->m_Name = tile.m_Name;
        return *this;
    }

private:
    bool m_Walkable;
    bool m_Buildable;
    bool m_Clickable;
    std::string m_Name;
    std::vector<std::shared_ptr<Selectable>> m_SelectableObjects;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
