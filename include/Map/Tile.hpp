//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
#include "GameObjectID.hpp"
#include "SpriteSheet.hpp"

class TileClass {
public:
    TileClass(const unitType unittype, bool buildable, bool walkable,
              bool clickable, std::shared_ptr<Core::Drawable> tileimage)
        : m_Id(GameObjectID(unittype)),
          m_Buildable(buildable),
          m_Walkable(walkable),
          m_Clickable(clickable),
          m_TileImage(tileimage) {}

    TileClass(const unitType unittype, bool buildable, bool walkable,
              bool clickable)
        : m_Id(GameObjectID(unittype)),
          m_Buildable(buildable),
          m_Walkable(walkable),
          m_Clickable(clickable) {}
    TileClass()
        : m_Id(GameObjectID(unitType::null)),
          m_Buildable(false),
          m_Walkable(false),
          m_Clickable(true) {}
    ~TileClass() {}

    bool getWalkable() { return m_Walkable; };
    bool getBuildable() { return m_Buildable; };
    bool getClickable() { return m_Clickable; };
    std::shared_ptr<Core::Drawable> getTileImage() { return m_TileImage; };

    void setWalkable(bool value) { m_Walkable = value; };
    void setBuildable(bool value) { m_Buildable = value; };
    void setClickable(bool value) { m_Clickable = value; };

    void setTileImage(std::shared_ptr<Core::Drawable> tileimage) {
        m_TileImage = tileimage;
    };
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
        this->m_TileImage = tile.m_TileImage;
        this->m_Buildable = tile.m_Buildable;
        this->m_Id = tile.m_Id;
        return *this;
    }

private:
    bool m_Walkable;
    bool m_Buildable;
    bool m_Clickable;
    std::shared_ptr<Core::Drawable> m_TileImage;
    GameObjectID m_Id;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
