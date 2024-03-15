//
// Created by nudle on 2024/3/8.
//
#include "UI/UIScriptProcess.hpp"

bool UIScriptProcess::GetIfFinished(std::shared_ptr<Structure> structure) {
    if (std::dynamic_pointer_cast<Barracks>(structure)) {
        return b_Baracks;
    } else if (std::dynamic_pointer_cast<OreRefinery>(structure)) {
        return b_OreRefinery;
    } else if (std::dynamic_pointer_cast<PowerPlants>(structure)) {
        return b_PowerPlants;
    } else if (std::dynamic_pointer_cast<WarFactory>(structure)) {
        return b_WarFactory;
    } else if (std::dynamic_pointer_cast<ADVPowerPlants>(structure)) {
        return b_ADVPowerPlant;
    }
}

bool UIScriptProcess::GetIfFinished(unitType type) {
    if (type==unitType::BARRACKS) {
        return b_Baracks;
    } else if (type==unitType::ORE_REF) {
        return b_OreRefinery;
    } else if (type==unitType::POWER_PLANT) {
        return b_PowerPlants;
    } else if (type==unitType::WAR_FACT) {
        return b_WarFactory;
    } else if (type==unitType::ADV_POWER_PLANT) {
        return b_ADVPowerPlant;
    }
}
void UIScriptProcess::SetFinished(std::shared_ptr<Structure> structure) {
    if (std::dynamic_pointer_cast<Barracks>(structure)) {
        b_Baracks = true;
    } else if (std::dynamic_pointer_cast<OreRefinery>(structure)) {
        b_OreRefinery = true;
    } else if (std::dynamic_pointer_cast<PowerPlants>(structure)) {
        b_PowerPlants = true;
    } else if (std::dynamic_pointer_cast<WarFactory>(structure)) {
        b_WarFactory = true;
    } else if (std::dynamic_pointer_cast<ADVPowerPlants>(structure)) {
        b_ADVPowerPlant = true;
    }
}
void UIScriptProcess::CountDown() {
    auto current = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = current - m_StartTime;
    if (elapsed.count()>=TargetTime) {
        SetFinished(temp_PTR);
        b_STALL = false;
        return;
    }
    Counter++;
}
void UIScriptProcess::SetCoolDown(float time) {
    Counter = 0.F;
    TargetTime = time;
    m_StartTime = std::chrono::high_resolution_clock::now();
}

void UIScriptProcess::buttonEvent(std::shared_ptr<Structure> m_Structure) {
    if (GetIfFinished(m_Structure)) {
        return;
    }
    buildQueue.push(m_Structure);
    return;
}
void UIScriptProcess::Update() {
    if (!buildQueue.empty() && !b_STALL) {
        auto currentStructure = buildQueue.front();
        buildQueue.pop();
        temp_PTR = currentStructure;
        b_STALL = true;
        SetCoolDown(currentStructure->GetBuildingTime());
    }
    CountDown();
}

