//
// Created by nudle on 2024/3/8.
//
#include "UI/UIScriptProcess.hpp"
#include <iomanip>
#include <sstream>
bool UIScriptProcess::GetIfFinishedBuilding(UnitType type) {
    switch (type) {
    case UnitType::BARRACKS:
        return b_Baracks;
    case UnitType::ORE_REF:
        return b_OreRefinery;
    case UnitType::POWER_PLANT:
        return b_PowerPlants;
    case UnitType::WAR_FACT:
        return b_WarFactory;
    case UnitType::ADV_POWER_PLANT:
        return b_ADVPowerPlant;
    }
}

float UIScriptProcess::GetCDLeft() {
    if (b_isBuildingInCoolDown) {
        std::chrono::duration<double> elapsed =
            m_currentCountDownTime - m_buildStartTime;
        return GetBuildCountDownTime() - elapsed.count();
    } else {
        return -1.F;
    }
}
std::string UIScriptProcess::GetFormattedCD() {
    float f = GetCDLeft();
    int min_part = int(f / 60);
    std::ostringstream min;
    min << std::setfill('0');
    min << std::setw(2);
    min << std::to_string(min_part);

    std::ostringstream sec;
    sec << std::setfill('0');
    sec << std::setw(2);
    sec << std::to_string(int(f - min_part * 60));

    if (f < 0) {
        return "Ready";
    } else {
        return min.str() + ":" + sec.str();
    }
}

void UIScriptProcess::CountDown() {
    double buildCoolDownTime = GetBuildCountDownTime();
    double spawnCoolDownTime = GetSpawnCountDownTime();
    m_currentCountDownTime = std::chrono::high_resolution_clock::now();

    // Structure Building
    std::chrono::duration<double> buildElapsed =
        m_currentCountDownTime - m_buildStartTime;
    if (m_gameObjectManager->getTotalCurrency() <= 0 &&
        b_isBuildingInCoolDown && buildElapsed.count() < buildCoolDownTime) {
        if (m_gameObjectManager->getTotalPower() <= 0) {
            SetBuildCountDown(buildCoolDownTime / 2 - buildElapsed.count());
        } else {
            SetBuildCountDown(buildCoolDownTime - buildElapsed.count());
        }
    } else {
        if ((b_isBuildingInCoolDown &&
             buildElapsed.count() - m_lastBuildElapsed >= 1) ||
            buildElapsed.count() == 0) { // update every second
            m_lastBuildElapsed = buildElapsed.count();
            int buildCost =
                GetObjCost(m_currentStructureType) / buildCoolDownTime;
            if (buildCost >= m_currentBuildRemainingCost) {
                buildCost = m_currentBuildRemainingCost;
            }
            if (m_currentBuildRemainingCost > 0) {
                m_currentBuildRemainingCost -= buildCost;
                m_gameObjectManager->addTotalCurrency(-1 * buildCost);
            }
        }
        // if finish building
        if (buildElapsed.count() >= buildCoolDownTime &&
            b_isBuildingInCoolDown) {
            // printf("(Button) Construction Finished\n");
            SetIfFinished(m_currentStructureType, true);
            b_isBuildingInCoolDown = false;
        }
    }

    // Avatar AvatarManager
    std::chrono::duration<double> spawnElapsed =
        m_currentCountDownTime - m_SpawnStartTime;
    if (m_gameObjectManager->getTotalCurrency() <= 0 &&
        b_isSpawningInCooldown && spawnElapsed.count() < spawnCoolDownTime) {
        if (m_gameObjectManager->getTotalPower() <= 0) {
            SetSpawnCountDown(spawnCoolDownTime / 2 - spawnElapsed.count());
        } else {
            SetSpawnCountDown(spawnCoolDownTime - spawnElapsed.count());
        }
    } else {
        if ((b_isSpawningInCooldown &&
             spawnElapsed.count() - m_lastSpawnElapsed >= 1) ||
            spawnElapsed.count() == 0) { // update every second
            m_lastSpawnElapsed = spawnElapsed.count();
            int spawnCost = GetObjCost(m_currentInfType) / spawnCoolDownTime;
            if (spawnCost >= m_currentSpawnRemainingCost) {
                spawnCost = m_currentSpawnRemainingCost;
            }
            if (m_currentSpawnRemainingCost > 0) {
                m_currentSpawnRemainingCost -= spawnCost;
                m_gameObjectManager->addTotalCurrency(-1 * spawnCost);
            }
        }
        // if finish spawning
        if (spawnElapsed.count() >= spawnCoolDownTime &&
            b_isSpawningInCooldown) {
            b_isReadyToSpawn = true;
            b_isSpawningInCooldown = false;
            printf("(UISC)Avatar Ready\n");
        }
    }

    if (b_isBuildingInCoolDown) {
        // printf("(Button) CD: %.2f,%s\n", m_buildCoolDownTime -
        // elapsed.count(), elapsed.count() >= m_buildCoolDownTime ? "True" :
        // "False");
    }
    if (b_isSpawningInCooldown) {
        printf("(UISC) CD: %.2f,%s\n", spawnElapsed.count(),
               spawnElapsed.count() >= spawnCoolDownTime ? "True" : "False");
    }
}
void UIScriptProcess::SetBuildCountDown(float time) {
    m_buildCoolDownTime = time;
    m_offPowerBuildCoolDownTime = time * 2;
    m_buildStartTime = std::chrono::high_resolution_clock::now();
}
void UIScriptProcess::SetSpawnCountDown(float time) {
    m_spawnCoolDownTime = time;
    m_offPowerSpawnCoolDownTime = time * 2;
    m_SpawnStartTime = std::chrono::high_resolution_clock::now();
}

void UIScriptProcess::AddToBuildQueue(UnitType type) {
    if (GetIfFinishedBuilding(type)) {
        return;
    }
    m_buildQueue.push_back(type);
    return;
}
void UIScriptProcess::Update(bool queueContinue) {
    //(m_buildQueue.size() > 1 && queueContinue && !b_isBuildingInCoolDown) for
    // waiting player to build strucutre, then continue operating
    if ((m_buildQueue.size() == 1 && !b_isBuildingInCoolDown) ||
        ((m_buildQueue.size() > 1 && queueContinue &&
          !b_isBuildingInCoolDown))) {
        m_currentStructureType = m_buildQueue.front();
        m_buildQueue.pop_front();
        b_isBuildingInCoolDown = true;
        SetBuildCountDown(GetStructureTime(m_currentStructureType));
        m_currentBuildRemainingCost = GetObjCost(m_currentStructureType);
    }
    if (m_spawnQueue.size() != 0 && !b_isSpawningInCooldown) {
        m_currentInfType = m_spawnQueue.front();
        m_spawnQueue.pop_front();
        b_isSpawningInCooldown = true;
        SetSpawnCountDown(GetSpawnTime(m_currentInfType));
        m_currentSpawnRemainingCost = GetObjCost(m_currentInfType);
    }
    CountDown();
}

float UIScriptProcess::GetStructureTime(UnitType type) {
    if (type == UnitType::POWER_PLANT) {
        return std::make_shared<PowerPlants>()->getBuildingTime();
    }
    if (type == UnitType::BARRACKS) {
        return std::make_shared<Barracks>()->getBuildingTime();
    }
    if (type == UnitType::ORE_REF) {
        return std::make_shared<OreRefinery>()->getBuildingTime();
    }
    if (type == UnitType::WAR_FACT) {
        return std::make_shared<WarFactory>()->getBuildingTime();
    }
    if (type == UnitType::ADV_POWER_PLANT) {
        return std::make_shared<ADVPowerPlants>()->getBuildingTime();
    }
}

void UIScriptProcess::SetIfFinished(UnitType type, bool value) {
    switch (type) {
    case UnitType::BARRACKS:
        b_Baracks = value;
        break;
    case UnitType::ORE_REF:
        b_OreRefinery = value;
        break;
    case UnitType::POWER_PLANT:
        b_PowerPlants = value;
        break;
    case UnitType::WAR_FACT:
        b_WarFactory = value;
        break;
    case UnitType::ADV_POWER_PLANT:
        b_ADVPowerPlant = value;
        break;
    default:
        // Handle the case when type doesn't match any of the options
        // For example, you might throw an exception or set a default value
        break;
    }
}

void UIScriptProcess::AddToSpawnQueue(UnitType type) {
    //    printf("(UISC)Add Spawn Queue\n");
    m_spawnQueue.push_back(type);
    return;
}
float UIScriptProcess::GetSpawnTime(UnitType type) {
    switch (type) {
    case UnitType::INFANTRY: {
        return 5.F;
    }
    }
}

std::shared_ptr<Avatar> UIScriptProcess::spawnAvatar() {
    //    printf("(UISC)spawnAvatar\n");
    switch (m_currentInfType) {
    case UnitType::INFANTRY: {
        return std::make_unique<Infantry>(HouseType::MY);
    }
    }
}

float UIScriptProcess::GetBuildCountDownTime() {
    if (m_gameObjectManager->getTotalPower() <= 0) {
        return m_offPowerBuildCoolDownTime;
    } else {
        return m_buildCoolDownTime;
    }
}
float UIScriptProcess::GetSpawnCountDownTime() {
    if (m_gameObjectManager->getTotalPower() <= 0) {
        return m_offPowerSpawnCoolDownTime;
    } else {
        return m_spawnCoolDownTime;
    }
}
int UIScriptProcess::GetObjCost(UnitType type) {
    switch (type) {
    case UnitType::BARRACKS:
        return std::make_shared<Barracks>()->getBuildingCost();
    case UnitType::ORE_REF:
        return std::make_shared<OreRefinery>()->getBuildingCost();
    case UnitType::POWER_PLANT:
        return std::make_shared<PowerPlants>()->getBuildingCost();
    case UnitType::WAR_FACT:
        return std::make_shared<WarFactory>()->getBuildingCost();
    case UnitType::ADV_POWER_PLANT:
        return std::make_shared<ADVPowerPlants>()->getBuildingCost();
    case UnitType::INFANTRY:
        return 100;
    default:
        // Handle the case when type doesn't match any of the options
        // For example, you might throw an exception or set a default value
        break;
    }
}
