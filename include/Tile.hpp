//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
#include "SpriteSheet.hpp"
#include <map>
class TileClass {
public:
    TileClass(const std::string name, bool buildable, bool walkable)
        : m_Name(name),
          m_Buildable(buildable),
          m_Walkable(walkable) {}
    ~TileClass() {}

    bool getWalkable() { return m_Walkable; };
    bool getBuildable() { return m_Buildable; };

    bool setWalkable(bool value) { m_Walkable = value; };
    bool setBuildable(bool value) { m_Buildable = value; };

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
    TileClass operator=(const TileClass &tile) const { return tile; }

private:
    bool m_Walkable;
    bool m_Buildable;
    std::string m_Name;
};

class TileSet {
public:
    /**
     *@brief given an vector that declares all the tileclasses and the
     *spritesheet value
     *
     */
    TileSet(std::vector<TileClass> tileclasses,
            std::shared_ptr<SpriteSheet> spriteSheet)
        : m_tileSpriteSheet(spriteSheet) {
        for (int i = 0; i < tileclasses.size(); i++) {
            // wtf
            m_TileTexture[tileclasses[i]] = i;
        }
    };
    ~TileSet(){};

    void DrawTileSetByClass(TileClass tileclass, Util::Transform trans,
                            int zindex) {
        auto findResult = m_TileTexture.find(tileclass);
        m_tileSpriteSheet->DrawSpriteByIndex(findResult->second, trans, zindex);
    }

private:
    std::map<TileClass, int> m_TileTexture;
    std::shared_ptr<SpriteSheet> m_tileSpriteSheet;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
