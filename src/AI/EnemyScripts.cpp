//
// Created by nudle on 2024/5/23.
//
#include "AI/EnemyScripts.hpp"

#define MAX_TROOPS_SIZE 25
void EnemyScripts::Start(std::shared_ptr<UnitManager> GameObjectManager,std::shared_ptr<UnitManager> EnemyObjectManager,std::shared_ptr<MapClass> map,bool active){
    m_GameObjectManager=GameObjectManager;

    m_EnemyObjectManager = EnemyObjectManager;
    m_Map = map;
    m_active = active;
    m_AIGroupCommander = std::make_shared<AIGroupCommander>(GameObjectManager,EnemyObjectManager,map);
    m_AIGroupCommander->Start();
}

void EnemyScripts::Update() {
    if (!m_active) {
        return;
    }
    m_buildDeltaTime += m_Time.GetDeltaTime();
    m_avatarDeltaTime += m_Time.GetDeltaTime();
    m_mainDeltaTime += m_Time.GetDeltaTime();

    if (m_buildDeltaTime >= m_buildingCDTime) { // update when CD over
        m_buildDeltaTime = 0;
        UpdateSpawnScript(SpawnMode::BUILDINGS);
    }
    if (m_avatarDeltaTime >= m_AvatarCDTime) { // update when CD over
        m_avatarDeltaTime = 0;
        UpdateSpawnScript(SpawnMode::AVATAR);
    }

    if (m_mainDeltaTime >= 1) {
        m_mainDeltaTime = 0;
        if (m_buildingCDTime < 1.f) {
            m_EnemyObjectManager->addTotalCurrency(m_buildingCost / (-1.f));
        } else {
            m_EnemyObjectManager->addTotalCurrency(m_buildingCost /
                                                   m_buildingCDTime * (-1.f));
        }
        if (m_AvatarCDTime < 1.f) {
            m_EnemyObjectManager->addTotalCurrency(m_avatarCost / (-1.f));
        } else {
            m_EnemyObjectManager->addTotalCurrency(m_avatarCost /
                                                   m_AvatarCDTime * (-1.f));
        }
        modeUpdate();
        m_AIGroupCommander->Update();
    }
}

void EnemyScripts::modeUpdate() {
    if (!ifBuiltBasic()) {
        buildBasic();
    } else {
        float playerAvatarCount = m_GameObjectManager->getAvatarCount();
        float enemyAvatarCount = m_EnemyObjectManager->getAvatarCount();
        if (enemyAvatarCount == 0 ||
            (playerAvatarCount /
                     enemyAvatarCount >=
                 2 &&
             playerAvatarCount != 0)) {
            // Defense mode , spawn Troop only
            spawnUnit();
        }else{
            if(playerAvatarCount/enemyAvatarCount<=0.5){
                //Attack , set all troop to attack mode , set defensive Troop = 0
                //updateAllTroopStates();
                m_AIGroupCommander->setAllTroopToAttackMode();
                spawnUnit();
            }else{
                //Safe now , build adv or spawn troop
                if(m_AIGroupCommander->getDefensiveTroopSize()>25){
                    m_AIGroupCommander->setTroopToAttackMode(m_AIGroupCommander->getDefensiveTroopSize()-25);
                }
                if(!ifBuiltADV() && enemyAvatarCount<MAX_TROOPS_SIZE){
                    buildADV();
                    spawnUnit();
                }else if(enemyAvatarCount<MAX_TROOPS_SIZE){
                    spawnUnit();
                }else{

                }
            }
        }
    }
    offensiveUpdate();
}

void EnemyScripts::setCDTime(float time, SpawnMode spawnMode, bool cheat) {
    if (spawnMode == SpawnMode::AVATAR) {
        if (m_EnemyObjectManager->getTotalPower() <= 0) {
            m_AvatarCDTime = time * 2;
        } else {
            m_AvatarCDTime = time;
        }
    }
    if (spawnMode == SpawnMode::BUILDINGS) {
        if (m_EnemyObjectManager->getTotalPower() <= 0) {
            m_buildingCDTime = time * 2;
        } else {
            m_buildingCDTime = time;
        }
    }


    if (cheat) {
        m_AvatarCDTime *= CHEAT;
        m_buildingCDTime *= CHEAT;
    }
}

void EnemyScripts::setCost(float cost, SpawnMode spawnMode) {
    if (spawnMode == SpawnMode::AVATAR) {
        m_avatarCost = cost;
    }
    if (spawnMode == SpawnMode::BUILDINGS) {
        m_buildingCost = cost;
    }
}

void EnemyScripts::buildBasic() {
    if (m_selectedBuildingType != UnitType::NONE) {
        return;
    }
    if (m_EnemyObjectManager->getUnitConstructCount(UnitType::POWER_PLANT) <
            1 &&
        m_EnemyObjectManager->getTotalCurrency() > 300) {
        setCDTime(15.f, SpawnMode::BUILDINGS);
        setCost(300, SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::POWER_PLANT;
    } else if (m_EnemyObjectManager->getUnitConstructCount(UnitType::ORE_REF) <
                   1 &&
               m_EnemyObjectManager->getTotalCurrency() > 2000) {
        setCDTime(100.f, SpawnMode::BUILDINGS);
        setCost(2000, SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::ORE_REF;
    } else if (m_EnemyObjectManager->getUnitConstructCount(UnitType::BARRACKS) <
                   1 &&
               m_EnemyObjectManager->getTotalCurrency() > 300) {
        setCDTime(15.f, SpawnMode::BUILDINGS);
        setCost(300, SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::BARRACKS;
    }
}

void EnemyScripts::buildADV() {
    if (m_selectedBuildingType != UnitType::NONE) {
        return;
    }
    if (m_EnemyObjectManager->getUnitConstructCount(UnitType::WAR_FACT) < 1 &&
        m_EnemyObjectManager->getTotalCurrency() > 2000) {
        setCDTime(100.f, SpawnMode::BUILDINGS);
        setCost(2000, SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::WAR_FACT;
    } else if (m_EnemyObjectManager->getUnitConstructCount(
                   UnitType::ADV_POWER_PLANT) < 1 &&
               m_EnemyObjectManager->getTotalCurrency() > 500) {
        setCDTime(25.f, SpawnMode::BUILDINGS);
        setCost(500, SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::ADV_POWER_PLANT;
    }
}


void EnemyScripts::spawnUnit() {
    if (m_selectedAvatarType != UnitType::NONE ||
        m_EnemyObjectManager->getAvatarCount() > 16) {
        return;
    }
    if (m_EnemyObjectManager->getAvatarCount() <= 25 &&
        m_EnemyObjectManager->getTotalCurrency() > 100) {
        setCDTime(5.f, SpawnMode::AVATAR);
        setCost(100, SpawnMode::AVATAR);
        m_selectedAvatarType = UnitType::INFANTRY;
    }
}

void EnemyScripts::UpdateSpawnScript(SpawnMode spawnMode) {
    // issue , avatar spawn and structure spawn should be separated CD time , so
    // can spawn avatar and structure same time

    if (spawnMode == SpawnMode::BUILDINGS) {
        if (m_selectedBuildingType == UnitType::NONE) {
            return;
        }
        m_EnemyObjectManager->spawn(
            m_selectedBuildingType, HouseType::ENEMY,
            {m_baseCell.x + constructCountX, m_baseCell.y + constructCountY});
        m_EnemyObjectManager->addUnitConstructCount(m_selectedBuildingType, 1);
        setCost(0, SpawnMode::BUILDINGS);
        setCDTime(0.f, SpawnMode::BUILDINGS);
        m_selectedBuildingType = UnitType::NONE;

        if (constructCountX > 10) {
            constructCountY += 5;
            constructCountX = 0;
        } else {
            constructCountX += 5;
        }
    }
    if (spawnMode == SpawnMode::AVATAR) {
        if (m_selectedAvatarType == UnitType::NONE) {
            return;
        }
        if (m_selectedAvatarType == UnitType::INFANTRY) {
            m_EnemyObjectManager->spawnToWayPoint(m_selectedAvatarType,
                                                 HouseType::ENEMY);
            setCost(0, SpawnMode::AVATAR);
            setCDTime(0.f, SpawnMode::AVATAR);
            m_selectedAvatarType = UnitType::NONE;
        }
    }
}
