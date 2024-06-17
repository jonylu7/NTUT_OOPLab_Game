//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP

#include "Avatar/Avatar.hpp"
#include "Mechanics/GameObjectID.hpp"
#include "Unit/Selectable.hpp"

#include "Display/SpriteSheet.hpp"
#include "Structure/Structure.hpp"
#include <unordered_map>
class TileClass {
public:
    TileClass(const UnitType unittype, bool buildable, bool walkable,
              bool clickable, std::string tileimagepath)
        : m_Id(GameObjectID(unittype, HouseType::NONE)),
          m_Clickable(clickable),
          m_TerrainBuildable(buildable),
          m_TerrainWalkable(walkable),
          m_TileImagePath(tileimagepath) {}

    TileClass(const UnitType unittype, bool buildable, bool walkable,
              bool clickable)
        : m_Id(GameObjectID(unittype, HouseType::NONE)),
          m_TerrainBuildable(buildable),
          m_TerrainWalkable(walkable),
          m_Clickable(clickable),
          m_TileImagePath("") {}
    TileClass()
        : m_Id(GameObjectID(UnitType::null, HouseType::NONE)),
          m_TerrainBuildable(true),
          m_TerrainWalkable(true),
          m_Clickable(true),
          m_TileImagePath(""){};
    ~TileClass() {}

    bool getWalkable() { return m_TerrainWalkable; };
    bool getBuildable() { return m_TerrainBuildable; };
    bool getClickable() { return m_Clickable; };
    std::string getTileImagePath() { return m_TileImagePath; }
    void setWalkable(bool value) { m_TerrainWalkable = value; };
    void setBuildable(bool value) { m_TerrainBuildable = value; };
    void setClickable(bool value) { m_Clickable = value; };
    void setTileImage(std::string path) { m_TileImagePath = path; };

    void setStructure(std::shared_ptr<Structure> structure) {
        m_Structure = structure;
    }
    void pushAvatars(std::shared_ptr<Avatar> avatar) {
        avatar->getMoving()->setStandingCorner(m_Avatars.size());
        m_Avatars.push_back(avatar);
        // if (m_Avatars.size() >= 5) {
        //    setWalkable(false);
        //}
    }

    std::vector<std::shared_ptr<Avatar>> getAvatars() { return m_Avatars; }
    std::shared_ptr<Structure> getStructure() { return m_Structure; }
    bool ifStructureExists() {
        if (*m_Structure->getHealth()->getLivingStatus() ==
            LivingStatus::NOT_BORN_YET) {
            return false;
        } else {
            return true;
        }
    }

    void removeAvatar(std::shared_ptr<Avatar> avatar) {
        for (int i = 0; i < m_Avatars.size(); i++) {
            if (m_Avatars[i] == avatar) {
                auto it = m_Avatars.begin() + i;
                m_Avatars.erase(it);
                i--;

                // if (m_Avatars.size() < 4 && m_TerrainBuildable) {
                //     setWalkable(true);
                // }
                if (m_Avatars.size() == 0) {
                    setBuildable(true);
                }
            }
        }
    }

    void removeStructure() {
        m_Structure = std::make_shared<Structure>();
        setWalkable(true);
        setBuildable(true);
    }
    void clearAvatars() {
        m_Avatars.clear();
        setWalkable(true);
        setBuildable(true);
    }

    TileClass &operator=(const TileClass &tile) {
        this->m_TerrainWalkable = tile.m_TerrainWalkable;
        this->m_Clickable = tile.m_Clickable;
        this->m_TileImagePath = tile.m_TileImagePath;

        this->m_TerrainBuildable = tile.m_TerrainBuildable;
        this->m_Id = tile.m_Id;
        return *this;
    }

    bool ifEnemyAtTile() {
        if (m_Structure->getID().getHouse() == HouseType::ENEMY) {
            return true;
        }
        for (auto a : m_Avatars) {
            if (a->getID().getHouse() == HouseType::ENEMY) {
                return true;
            }
        }
        return false;
    }

    bool ifEnemyAtTile(HouseType myHouse) {
        if (myHouse == HouseType::MY) {
            if (m_Structure->getID().getHouse() == HouseType::ENEMY) {
                return true;
            }
            for (auto a : m_Avatars) {
                if (a->getID().getHouse() == HouseType::ENEMY) {
                    return true;
                }
            }
            return false;
        } else if (myHouse == HouseType::ENEMY) {
            if (m_Structure->getID().getHouse() == HouseType::MY) {
                return true;
            }
            for (auto a : m_Avatars) {
                if (a->getID().getHouse() == HouseType::MY) {
                    return true;
                }
            }
            return false;
        }
    }

private:
    bool m_TerrainBuildable;
    bool m_TerrainWalkable;
    bool m_Clickable;
    std::shared_ptr<Structure> m_Structure = std::make_shared<Structure>();
    std::vector<std::shared_ptr<Avatar>> m_Avatars;

    std::string m_TileImagePath;
    GameObjectID m_Id;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
