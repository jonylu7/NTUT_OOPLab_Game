//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
#include "SpriteSheet.hpp"
#include <map>
class TileClass {
public:
    TileClass(const std::string name, bool buildable, bool walkable,
              bool clickable, int spritesheetindex)
        : m_Name(name),
          m_Buildable(buildable),
          m_Walkable(walkable),
          m_Clickable(clickable),
          m_SpriteSheetIndex(spritesheetindex) {}
    TileClass()
        : m_Name(""),
          m_Buildable(false),
          m_Walkable(false),
          m_Clickable(true),
          m_SpriteSheetIndex(0) {}
    ~TileClass() {}

    bool getWalkable() { return m_Walkable; };
    bool getBuildable() { return m_Buildable; };
    bool getClickable() { return m_Clickable; };
    bool getSpriteSheetIndex() { return m_SpriteSheetIndex; };

    void setWalkable(bool value) { m_Walkable = value; };
    void setBuildable(bool value) { m_Buildable = value; };
    void setClickable(bool value) { m_Clickable = value; };

    void setSpriteSheetIndex(unsigned int spritesheetindex) {
        m_SpriteSheetIndex = spritesheetindex;
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
        this->m_SpriteSheetIndex = tile.m_SpriteSheetIndex;
        this->m_Buildable = tile.m_Buildable;
        this->m_Name = tile.m_Name;
        return *this;
    }

private:
    bool m_Walkable;
    bool m_Buildable;
    bool m_Clickable;
    unsigned int m_SpriteSheetIndex;
    std::string m_Name;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
