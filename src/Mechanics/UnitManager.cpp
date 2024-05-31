//
// Created by 盧威任 on 4/19/24.
//
#include "Mechanics/UnitManager.hpp"

void UnitManager::spawnToWayPoint(UnitType unit, HouseType house) {

    switch (unit) {
    case UnitType::INFANTRY: {
        auto avatar = std::make_shared<Infantry>(house);
        if (m_StructureManager->getStructureArray()
                ->getPlayerBarrackSpawnCell()
                .x == -1) {
            return;
        }

        avatar->Start(m_StructureManager->getStructureArray()
                          ->getPlayerBarrackSpawnCell());

        m_AvatarManager->assignMoveOrderToAvatar(
            avatar, {m_StructureManager->getStructureArray()
                         ->getPlayerBarrackWayPointCell()});
        // assign order
        m_AvatarManager->assignMoveOrderToAvatar(
            avatar, m_StructureManager->getStructureArray()
                        ->getPlayerBarrackWayPointCell());
        m_AvatarManager->AppendAvatar(avatar);
        m_troopSize += 1;
    }

    default: {
        printf("(GOM)error! try to spawn unknown type\n");
        break;
    }
    }
}

void UnitManager::spawn(UnitType unit, HouseType house, glm::vec2 cellPos) {
    // 缺檢查敵方擁有建築的位置，並重生在該處
    switch (unit) {
    case UnitType::BARRACKS: {
        auto structure = std::make_shared<Barracks>(house);
        auto globalPos = MapUtil::CellCoordToGlobal(cellPos);
        structure->Start(globalPos);
        structure->setWaypointLocationByCellCoord(
            {cellPos.x + 2, cellPos.y - 2});
        m_StructureManager->getStructureArray()->buildNewStructure(structure,
                                                                   true);
        break;
    }
    case UnitType::ORE_REF: {
        auto structure = std::make_shared<OreRefinery>(house);
        auto globalPos = MapUtil::CellCoordToGlobal(cellPos);
        structure->Start(globalPos);
        m_StructureManager->getStructureArray()->buildNewStructure(structure,
                                                                   true);
        break;
    }
    case UnitType::POWER_PLANT: {
        auto structure = std::make_shared<PowerPlants>(house);
        auto globalPos = MapUtil::CellCoordToGlobal(cellPos);
        structure->Start(globalPos);
        m_StructureManager->getStructureArray()->buildNewStructure(structure,
                                                                   true);
        break;
    }
    case UnitType::WAR_FACT: {
        auto structure = std::make_shared<WarFactory>(house);
        auto globalPos = MapUtil::CellCoordToGlobal(cellPos);
        structure->Start(globalPos);
        structure->setWaypointLocationByCellCoord(
            {cellPos.x + 2, cellPos.y - 2});
        m_StructureManager->getStructureArray()->buildNewStructure(structure,
                                                                   true);
        break;
    }
    case UnitType::ADV_POWER_PLANT: {
        auto structure = std::make_shared<ADVPowerPlants>(house);
        auto globalPos = MapUtil::CellCoordToGlobal(cellPos);
        structure->Start(globalPos);
        m_StructureManager->getStructureArray()->buildNewStructure(structure,
                                                                   true);
        break;
    }
    case UnitType::INFANTRY: {
        auto avatar = std::make_shared<Infantry>(house);
        avatar->Start(cellPos);
        //            avatar ->setNewDestination(cellPos);
        m_AvatarManager->assignMoveOrderToAvatar(
            avatar, {cellPos.x + 1, cellPos.y + 1});
        m_AvatarManager->AppendAvatar(avatar);
        m_troopSize += 1;
        break;
    }
    case UnitType::NONE: {
        printf("(GOM)error! try to build when type == NONE\n");
        break;
    }
    default: {
        printf("(GOM)error! try to spawn unknown type\n");
        break;
    }
    }
}

void UnitManager::Update() {
    m_StructureManager->Update();
    m_AvatarManager->Update();
    m_CursorSelection->Update();

    // currency update
    std::chrono::high_resolution_clock::time_point m_currentTime =
        std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = m_currentTime - m_StartTime;
    if (elapsed.count() - m_lastElapsed >= 1) { // update every second
        m_lastElapsed = elapsed.count();
    }

    m_StructureManager->SelectingBuildSite();
}
