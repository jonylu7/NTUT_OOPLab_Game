//
// Created by 盧威任 on 4/24/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_BUILTSTRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_BUILTSTRUCTURE_HPP
#include "Map/Map.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/Structure.hpp"
#include "pch.hpp"

class BuiltStructure {
public:
    BuiltStructure() {}
    virtual ~BuiltStructure() {}
    void Start(std::shared_ptr<MapClass> map) {
        m_Map = map;
        StartBuiltStructure();
    }
    void buildNewStructure(std::shared_ptr<Structure> newstruct,
                           bool force = false);

    bool ifCanBuildStructureAtTile(std::shared_ptr<Structure> newstruct);

    std::vector<std::shared_ptr<Structure>> getBuiltStructureArray() {
        return m_BuiltStructure;
    }

    void StartBuiltStructure() {
        for (auto structure : m_BuiltStructure) {
            structure->Start();
        }
    }

    void UpdateBuiltStructure();
    void add(std::shared_ptr<Structure> structure) {
        m_BuiltStructure.push_back(structure);
    }

public:
    // glm::vec2 getEnemyBarrackCell() { return m_EnemyBarrackCell; }
    // glm::vec2 getEnemyWayPointCell() { return m_EnemyWayPointCell; }
    glm::vec2 getPlayerBarrackSpawnCell() {
        for (auto i : m_BuiltStructure) {
            if (std::dynamic_pointer_cast<Barracks>(i)) {
                for (auto i : i->getNearbyArea()) {
                    if (m_Map->ifWalkable(i)) {
                        return i;
                    }
                }
            }
        }
    }
    glm::vec2 getPlayerBarrackWayPointCell() {
        for (auto i : m_BuiltStructure) {
            if (std::dynamic_pointer_cast<Barracks>(i)) {
                return MapUtil::GlobalCoordToCellCoord(
                    std::dynamic_pointer_cast<Barracks>(i)
                        ->getWaypointLocation());
            }
        }
    }
    void setBarrackWayPointByCell(glm::vec2 cell) {
        if (ifBarrackBuilt()) {
            for (auto i : m_BuiltStructure) {
                if (i->getID().getUnitType() == UnitType::BARRACKS) {
                    std::dynamic_pointer_cast<Barracks>(i)
                        ->setWaypointLocationByCellCoord(cell);
                }
            }
        }
    }

    bool ifBarrackBuilt() {
        for (auto i : m_BuiltStructure) {
            if (i->getID().getUnitType() == UnitType::BARRACKS) {
                return true;
            }
        }
        return false;
    }
    bool ifPowerPlantBuilt() {
        for (auto i : m_BuiltStructure) {
            if (i->getID().getUnitType() == UnitType::POWER_PLANT) {
                return true;
            }
        }
        return false;
    }
    bool ifWarFactoryBuilt() {
        for (auto i : m_BuiltStructure) {
            if (i->getID().getUnitType() == UnitType::WAR_FACT) {
                return true;
            }
        }
        return false;
    }

    bool ifOreRefinaryBuilt() {
        for (auto i : m_BuiltStructure) {
            if (i->getID().getUnitType() == UnitType::ORE_REF) {
                return true;
            }
        }
        return false;
    }

private:
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::vector<std::shared_ptr<Structure>> m_BuiltStructure;
    glm::vec2 m_PlayerBarrackCell = {-1, -1};
    glm::vec2 m_PlayerWayPointCell = {-1, -1};
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_BUILTSTRUCTURE_HPP
