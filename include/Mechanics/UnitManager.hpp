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
#include "Mechanics/Player.hpp"
#include "Mechanics/StructureManager.hpp"
#include "Structure/AdvencePowerPlants.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/WarFactory.hpp"
#include <chrono>

#include <utility>

class UnitManager : public Player {
public:
    UnitManager() {}
    ~UnitManager() {}
    void Start(std::shared_ptr<MapClass> map) {
        m_Map = map;
        m_StructureManager->Start(m_Map);

        m_AvatarManager->Start(m_Map);
        m_CursorSelection->Start(m_Map);
        m_StartTime = std::chrono::high_resolution_clock::now();
    }

    void Update() {
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

public:
    int getTotalPower() {
        return Player::getTotalPower(
            *m_StructureManager->getStructureArray()->getBuiltStructureArray());
    }
    std::shared_ptr<AvatarManager> getAvatarManager() {
        return m_AvatarManager;
    }
    std::shared_ptr<StructureManager> getStructureManager() {
        return m_StructureManager;
    }

    int UpdateCurrency() {
        for (auto i : *m_StructureManager->getStructureArray()
                           ->getBuiltStructureArray()) {
            if (std::dynamic_pointer_cast<OreRefinery>(i)) {
                addTotalCurrency(150);
            }
        }
    }

    void spawnToWayPoint(std::shared_ptr<MapClass> m_Map, UnitType unit,
                         HouseType house) {

        switch (unit) {
        case UnitType::INFANTRY: {
            auto avatar = std::make_shared<Infantry>(house);

            if (m_StructureManager->getStructureArray()
                    ->getPlayerBarrackCell()
                    .x == -1) {
                return;
            }

            avatar->Start(m_StructureManager->getStructureArray()
                              ->getPlayerBarrackCell());

            // assign order
            m_AvatarManager->assignMoveOrderToAvatar(
                avatar, m_StructureManager->getStructureArray()
                            ->getPlayerWayPointCell());
            m_AvatarManager->AppendAvatar(avatar);
        }

        default: {
            printf("(GOM)error! try to spawn unknown type\n");
            break;
        }
        }
    }
    void spawn(std::shared_ptr<MapClass> m_Map, UnitType unit, HouseType house,
               glm::vec2 cellPos) {
        // 缺檢查敵方擁有建築的位置，並重生在該處
        switch (unit) {
        case UnitType::BARRACKS: {
            auto structure = std::make_shared<Barracks>(house);
            auto globalPos = MapUtil::CellCoordToGlobal(cellPos);
            structure->Start(globalPos);
            m_StructureManager->getStructureArray()->buildNewStructure(
                structure, true);
            break;
        }
        case UnitType::ORE_REF: {
            auto structure = std::make_shared<OreRefinery>(house);
            auto globalPos = MapUtil::CellCoordToGlobal(cellPos);
            structure->Start(globalPos);
            m_StructureManager->getStructureArray()->buildNewStructure(
                structure, true);
            break;
        }
        case UnitType::POWER_PLANT: {
            auto structure = std::make_shared<PowerPlants>(house);
            auto globalPos = MapUtil::CellCoordToGlobal(cellPos);
            structure->Start(globalPos);
            m_StructureManager->getStructureArray()->buildNewStructure(
                structure, true);
            break;
        }
        case UnitType::WAR_FACT: {
            auto structure = std::make_shared<WarFactory>(house);
            auto globalPos = MapUtil::CellCoordToGlobal(cellPos);
            structure->Start(globalPos);
            m_StructureManager->getStructureArray()->buildNewStructure(
                structure, true);
            break;
        }
        case UnitType::ADV_POWER_PLANT: {
            auto structure = std::make_shared<ADVPowerPlants>(house);
            auto globalPos = MapUtil::CellCoordToGlobal(cellPos);
            structure->Start(globalPos);
            m_StructureManager->getStructureArray()->buildNewStructure(
                structure, true);
            break;
        }
        case UnitType::INFANTRY: {
            auto avatar = std::make_shared<Infantry>(house);
            avatar->Start(cellPos);
            //            avatar ->setNewDestination(cellPos);
            m_AvatarManager->AppendAvatar(avatar);
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

    //    bool ifClosestEnemyInRange(glm::vec2 cell,HouseType myHouse,int
    //    range){
    //        float closestDistance=500.f;
    //        if(myHouse==HouseType::MY){
    //            for(auto i:m_EnemyUnitArray){
    //                if(MapUtil::findDistance(cell,i->getCurrentCell())<closestDistance){
    //                    closestDistance=MapUtil::findDistance(cell,i->getCurrentCell());
    //                }
    //            }
    //        }else{
    //            for(auto i:m_PlayerUnitArray){
    //                if(MapUtil::findDistance(cell,i->getCurrentCell())<closestDistance){
    //                    closestDistance=MapUtil::findDistance(cell,i->getCurrentCell());
    //                }
    //            }
    //        }
    //        return closestDistance<=range;
    //    }
    //
    //    std::shared_ptr<AttackAndDamage> findInRangeEnemy(glm::vec2
    //    cell,HouseType myHouse,int range){
    //        float closestDistance=500.f;
    //        std::shared_ptr<AttackAndDamage> ansUnit;
    //        if(myHouse==HouseType::MY){
    //            for(auto i:m_EnemyUnitArray){
    //                if(MapUtil::findDistance(cell,i->getCurrentCell())<closestDistance){
    //                    closestDistance=MapUtil::findDistance(cell,i->getCurrentCell());
    //                    ansUnit = i;
    //                }
    //            }
    //        }else{
    //            for(auto i:m_PlayerUnitArray){
    //                if(MapUtil::findDistance(cell,i->getCurrentCell())<closestDistance){
    //                    closestDistance=MapUtil::findDistance(cell,i->getCurrentCell());
    //                    ansUnit = i;
    //                }
    //            }
    //        }
    //        return ansUnit;
    //    }
private:
    std::shared_ptr<CursorSelection> m_CursorSelection =
        std::make_shared<CursorSelection>();
    std::shared_ptr<StructureManager> m_StructureManager =
        std::make_shared<StructureManager>();
    std::shared_ptr<AvatarManager> m_AvatarManager =
        std::make_shared<AvatarManager>();
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::chrono::high_resolution_clock::time_point m_StartTime;
    double m_lastElapsed = 0.F;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UNITMANAGER_HPP
