//
// Created by nudle on 2024/3/8.
//
#include "UI/UIScriptProcess.h"

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
    if (true /*Counter>=TargetTime*/) {
        SetFinished(temp_PTR);
        b_STALL = false;
        return;
    }
    Counter++;
}
void UIScriptProcess::SetCoolDown(float time) {
    Counter = 0.F;
    TargetTime = time * 60;
}

void UIScriptProcess::buttonEvent(std::shared_ptr<Structure> m_Structure) {
    if (GetIfFinished(m_Structure)) {
        m_Structure->Start();
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
