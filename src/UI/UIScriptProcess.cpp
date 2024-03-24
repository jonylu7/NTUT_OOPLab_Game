//
// Created by nudle on 2024/3/8.
//
#include "UI/UIScriptProcess.hpp"
#include <iomanip>
#include <sstream>
bool UIScriptProcess::GetIfFinished(unitType type) {
    switch (type) {
    case unitType::BARRACKS:
        return b_Baracks;
    case unitType::ORE_REF:
        return b_OreRefinery;
    case unitType::POWER_PLANT:
        return b_PowerPlants;
    case unitType::WAR_FACT:
        return b_WarFactory;
    case unitType::ADV_POWER_PLANT:
        return b_ADVPowerPlant;
    }
}

float UIScriptProcess::GetCDLeft() {
    if (b_STALL) {
        std::chrono::duration<double> elapsed =
            m_CountDownCurrentTime - m_StartTime;
        return TargetTime - elapsed.count();
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
    m_CountDownCurrentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed =
        m_CountDownCurrentTime - m_StartTime;
    std::chrono::duration<double> unitElapsed =
        m_CountDownCurrentTime - m_SpawnStartTime;
    if (b_STALL) {
        // printf("(Button) CD: %.2f,%s\n", TargetTime - elapsed.count(),
        // elapsed.count() >= TargetTime ? "True" : "False");
    }
    if (b_spawnInCD) {
        printf("(UISC) CD: %.2f,%s\n", unitElapsed.count(),
        elapsed.count() >= m_SpawnTime ? "True" : "False");
    }
    if (elapsed.count() >= TargetTime && b_STALL) {
        // printf("(Button) Construction Finished\n");
        SetIfFinished(m_currentStructure, true);
        b_STALL = false;
        return;
    }
    if (unitElapsed.count() >= m_SpawnTime && b_spawnInCD) {
        b_readytoSpawn=true;
        b_spawnInCD = false;
        printf("(UISC)Unit Ready\n");
        return;
    }
}
void UIScriptProcess::SetCountDown(float time) {
    TargetTime = time;
    m_StartTime = std::chrono::high_resolution_clock::now();
}
void UIScriptProcess::SetSpawnCountDown(float time) {
    m_SpawnTime = time;
    m_SpawnStartTime = std::chrono::high_resolution_clock::now();
}

void UIScriptProcess::AddToBuildQueue(unitType type) {
    if (GetIfFinished(type)) {
        return;
    }
    buildQueue.push_back(type);
    return;
}
void UIScriptProcess::Update(bool queueContinue) {
    //(buildQueue.size() > 1 && queueContinue && !b_STALL) for waiting player to
    //build strucutre, then continue operating
    if ((buildQueue.size() == 1 && !b_STALL) ||
        ((buildQueue.size() > 1 && queueContinue && !b_STALL))) {
        m_currentStructure = buildQueue.front();
        buildQueue.pop_front();
        b_STALL = true;
        SetCountDown(GetStructureTime(m_currentStructure));
    }
    if (m_spawnQueue.size() !=0 && !b_spawnInCD) {
        m_currentAvatar = m_spawnQueue.front();
        m_spawnQueue.pop_front();
        b_spawnInCD = true;
        SetSpawnCountDown(GetSpawnTime(m_currentAvatar));
    }
    CountDown();
}

float UIScriptProcess::GetStructureTime(unitType type) {
    if (type == unitType::POWER_PLANT) {
        return powerPlant->GetBuildingTime();
    }
    if (type == unitType::BARRACKS) {
        return barracks->GetBuildingTime();
    }
    if (type == unitType::ORE_REF) {
        return oreRefinery->GetBuildingTime();
    }
    if (type == unitType::WAR_FACT) {
        return warFactory->GetBuildingTime();
    }
    if (type == unitType::ADV_POWER_PLANT) {
        return advPowerPlant->GetBuildingTime();
    }
}

void UIScriptProcess::SetIfFinished(unitType type, bool value) {
    switch (type) {
    case unitType::BARRACKS:
        b_Baracks = value;
        break;
    case unitType::ORE_REF:
        b_OreRefinery = value;
        break;
    case unitType::POWER_PLANT:
        b_PowerPlants = value;
        break;
    case unitType::WAR_FACT:
        b_WarFactory = value;
        break;
    case unitType::ADV_POWER_PLANT:
        b_ADVPowerPlant = value;
        break;
    default:
        // Handle the case when type doesn't match any of the options
        // For example, you might throw an exception or set a default value
        break;
    }
}

void UIScriptProcess::AddToSpawnQueue(unitType type){
    printf("(UISC)Add Spawn Queue\n");
    m_spawnQueue.push_back(type);
    return;

}
float UIScriptProcess::GetSpawnTime(unitType type){
    switch (type) {
    case unitType::INFANTRY:{
        return 5.F;
    }
    }
}

std::shared_ptr<Avatar> UIScriptProcess::spawnAvatar(){
    printf("(UISC)spawnAvatar\n");
    switch (m_currentAvatar) {
    case unitType::INFANTRY:{
        return std::make_unique<Infantry>();
    }
    }
}