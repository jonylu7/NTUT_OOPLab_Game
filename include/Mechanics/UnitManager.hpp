//
// Created by 盧威任 on 3/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
#include "Avatar/Infantry.hpp"
#include "AvatarNavigator.hpp"
#include "Cursor.hpp"
#include "GameObjectID.hpp"
#include "Mechanics/AvatarManager.hpp"
#include "Mechanics/BuiltStructure.hpp"
#include "Mechanics/CursorSelection.hpp"
#include "Mechanics/StructureManager.hpp"
#include "Structure/AdvancePowerPlants.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/WarFactory.hpp"
#include <chrono>

#include <utility>

class UnitManager {
public:
    UnitManager() {}
    ~UnitManager() {}
    void Start(std::shared_ptr<MapClass> map) {
        m_Map = map;
        m_StructureManager->Start(m_Map);

        m_AvatarManager->Start(m_Map);
        m_CursorSelection->Start(m_Map);
    }

    void Update();

public:
    std::shared_ptr<AvatarManager> getAvatarManager() {
        return m_AvatarManager;
    }
    std::shared_ptr<StructureManager> getStructureManager() {
        return m_StructureManager;
    }

    void spawnToWayPoint(UnitType unit, HouseType house);
    void spawn(UnitType unit, HouseType house, glm::vec2 cellPos);

    void addUnitConstructCount(UnitType type, int value) {
        unitCount[type] += value;
    }

    int getUnitConstructCount(UnitType type) { return unitCount[type]; }
    int getAvatarCount() { return m_AvatarManager->getAvatarSize(); }

private:
    std::unordered_map<UnitType, int> unitCount;
    std::shared_ptr<CursorSelection> m_CursorSelection =
        std::make_shared<CursorSelection>();
    std::shared_ptr<StructureManager> m_StructureManager =
        std::make_shared<StructureManager>();
    std::shared_ptr<AvatarManager> m_AvatarManager =
        std::make_shared<AvatarManager>();
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
