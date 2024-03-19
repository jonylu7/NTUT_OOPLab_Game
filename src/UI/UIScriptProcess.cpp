//
// Created by nudle on 2024/3/8.
//
#include "UI/UIScriptProcess.hpp"

bool UIScriptProcess::GetIfFinished(unitType type) {
    if (type == unitType::BARRACKS) {
        return b_Baracks;
    } else if (type == unitType::ORE_REF) {
        return b_OreRefinery;
    } else if (type == unitType::POWER_PLANT) {
        return b_PowerPlants;
    } else if (type == unitType::WAR_FACT) {
        return b_WarFactory;
    } else if (type == unitType::ADV_POWER_PLANT) {
        return b_ADVPowerPlant;
    }
}
void UIScriptProcess::SetFinished(unitType type) {
    if (type == unitType::BARRACKS) {
        b_Baracks = true;
    } else if (type == unitType::ORE_REF) {
        b_OreRefinery = true;
    } else if (type == unitType::POWER_PLANT) {
        b_PowerPlants = true;
    } else if (type == unitType::WAR_FACT) {
        b_WarFactory = true;
    } else if (type == unitType::ADV_POWER_PLANT) {
        b_ADVPowerPlant = true;
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
    // TODO:TBD
    return "";
}

void UIScriptProcess::CountDown() {
    m_CountDownCurrentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed =
        m_CountDownCurrentTime - m_StartTime;
    if (b_STALL) {
        printf("(Button) CD: %.2f,%s\n", TargetTime - elapsed.count(),
               elapsed.count() >= TargetTime ? "True" : "False");
    }
    if (elapsed.count() >= TargetTime && b_STALL) {
        printf("(Button) Construction Finished\n");
        SetFinished(m_currentStructure);
        b_STALL = false;
        return;
    }
}
void UIScriptProcess::SetCoolDown(float time) {
    TargetTime = time;
    m_StartTime = std::chrono::high_resolution_clock::now();
}

void UIScriptProcess::buttonEvent(unitType type) {
    if (GetIfFinished(type)) {
        return;
    }
    buildQueue.push_back(type);
    return;
}
void UIScriptProcess::Update() {
    if (!buildQueue.empty() && !b_STALL) {
        m_currentStructure = buildQueue.front();
        buildQueue.pop_front();
        b_STALL = true;
        SetCoolDown(GetStructureTime(m_currentStructure));
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
void UIScriptProcess::SetUsed(unitType type) {
    if (type == unitType::BARRACKS) {
        b_Baracks = false;
    } else if (type == unitType::ORE_REF) {
        b_OreRefinery = false;
    } else if (type == unitType::POWER_PLANT) {
        b_PowerPlants = false;
    } else if (type == unitType::WAR_FACT) {
        b_WarFactory = false;
    } else if (type == unitType::ADV_POWER_PLANT) {
        b_ADVPowerPlant = false;
    }
}
