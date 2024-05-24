//
// Created by 盧威任 on 3/3/24.
//

#include "UI/UI.hpp"
#include "Map/Map.hpp"

std::unordered_map<UnitType, unsigned int> UIClass::s_unitConstructCount;

void UIClass::Start(std::shared_ptr<MapClass> map,
                    std::shared_ptr<UnitManager> gameobjectmanager) {
    InitUnitQueue();
    // start
    this->m_Map = map;
    m_gameObjectManager = gameobjectmanager;
    m_UIScriptProcess->Start(gameobjectmanager);

    m_StructureIconSpriteSheet->Start(
        "../assets/sprites/ICON_Allied_Structure.png", 64, 48, 24, 0);
    m_InfantryIconSpriteSheet->Start(
        "../assets/sprites/ICON_Allied_Infantry.png", 64, 48, 8, 0);
    m_VehiclesIconSpriteSheet->Start(
        "../assets/sprites/ICON_Allied_Vehicles.png", 64, 48, 12, 0);
}

void UIClass::Update() {
    ShowPlayerConstructionMenu();
    m_UIScriptProcess->Update(getIfAnyBuildingReadyToBuild());
}

void UIClass::ShowPlayerStatus() {
    glm::vec2 CursorGlobalPosition = MapUtil::ScreenToGlobalCoord(
        glm::vec2(Util::Input::GetCursorPosition()));
    ImGui::Text(std::string("X: " + std::to_string(CursorGlobalPosition.x) +
                            "  Y: " + std::to_string(CursorGlobalPosition.y))
                    .c_str());
    auto cellLocation = MapUtil::GlobalCoordToCellCoord(CursorGlobalPosition);
    ImGui::Text(std::string("Cell X: " + std::to_string(int(cellLocation.x)) +
                            "  Cell Y: " + std::to_string(int(cellLocation.y)))
                    .c_str());
    // ImGui::Text(fmt::format("Zoom: {}",
    // m_SceneCamera.getCameraZoom()).c_str());
    ImGui::Text(
        fmt::format("$ {}", m_gameObjectManager->getTotalCurrency()).c_str());
    ImGui::Text(
        fmt::format("Power {}", m_gameObjectManager->getTotalPower()).c_str());
    ImGui::PushFont(sacker_med);
}

void UIClass::ShowHeaderSection() {

    if (ImGui::Button("Grid on")) {
        m_Map->setGridActive(true);
    }
    if (ImGui::Button("Grid off")) {
        m_Map->setGridActive(false);
    }

    if (ImGui::Button("Cheat Mode On")) {
        // TODO inf money, speed build time and cant player unit health cant be
        // damaged
    }
    if (ImGui::Button("Cheat Mode off")) {
        // TODO
    }

    ImGui::PopFont();
}
void UIClass::ShowPlayerConstructionMenu() {
    auto windowSettings = ImGuiWindowFlags_NoMove |
                          ImGuiWindowFlags_NoScrollbar |
                          ImGuiWindowFlags_NoResize;

    // put the stuff in here
    ImGui::Begin("Structure Selection Menu", nullptr, windowSettings);
    ShowPlayerStatus();
    ShowHeaderSection();

    // Adjust font texture size if necessary
    // Larger font texture size may improve text clarity on high DPI displays

    if (ImGui::BeginTabBar("", ImGuiTabBarFlags_None)) {
        ShowBuildingTab();
        ShowDefTab();
        ShowInfantryTab();
        ShowVehTab();

        ImGui::EndTabBar();
    }
    ImGui::End();
}

std::vector<ImVec2>
UIClass::getSpriteSheetCoordByIndex(std::shared_ptr<SpriteSheet> spritesheet,
                                    int index) {
    return std::vector<ImVec2>(
        {ImVec2(
             SpriteSheet::UVtoImGuiCoord(spritesheet->getUVbyIndex(index))[0].x,
             SpriteSheet::UVtoImGuiCoord(spritesheet->getUVbyIndex(index))[0]
                 .y),
         ImVec2(
             SpriteSheet::UVtoImGuiCoord(spritesheet->getUVbyIndex(index))[1].x,
             SpriteSheet::UVtoImGuiCoord(spritesheet->getUVbyIndex(index))[1]
                 .y)});
}

void UIClass::ShowBuildingTab() {
    if (ImGui::BeginTabItem("Build")) {
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 7)) {
            // power plants

            if (m_selectedStructureType == UnitType::NONE &&
                m_UIScriptProcess->GetIfFinishedBuilding(
                    UnitType::POWER_PLANT)) {

                setSelectToBuild(UnitType::POWER_PLANT);
            } else {
                m_UIScriptProcess->AddToBuildQueue(UnitType::POWER_PLANT);
            }
        }

        ImDrawList *dl = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetCursorScreenPos();
        p.x += 5.F;
        p.y -= 38.F;
        ImGui::PushFont(sacker_heav);
        if (m_UIScriptProcess->GetCurrentStructure() == UnitType::POWER_PLANT) {
            dl->AddText(p, IM_COL32(2, 255, 2, 255),
                        m_UIScriptProcess->GetFormattedCD().c_str());
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 22)) {
            // barracks

            if (m_selectedStructureType == UnitType::NONE &&
                m_UIScriptProcess->GetIfFinishedBuilding(UnitType::BARRACKS)) {
                setSelectToBuild(UnitType::BARRACKS);
            } else {
                m_UIScriptProcess->AddToBuildQueue(UnitType::BARRACKS);
            }
        }
        p.x += 80.F;
        if (m_UIScriptProcess->GetCurrentStructure() == UnitType::BARRACKS) {
            dl->AddText(p, IM_COL32(2, 255, 2, 255),
                        m_UIScriptProcess->GetFormattedCD().c_str());
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 8)) {
            // ore

            if (m_selectedStructureType == UnitType::NONE &&
                m_UIScriptProcess->GetIfFinishedBuilding(UnitType::ORE_REF)) {

                setSelectToBuild(UnitType::ORE_REF);
            } else {
                m_UIScriptProcess->AddToBuildQueue(UnitType::ORE_REF);
            }
        }
        p.x += 80.F;
        if (m_UIScriptProcess->GetCurrentStructure() == UnitType::ORE_REF) {
            dl->AddText(p, IM_COL32(2, 255, 2, 255),
                        m_UIScriptProcess->GetFormattedCD().c_str());
        }
        ImGui::NewLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 20)) {
            // war factory

            if (m_selectedStructureType == UnitType::NONE &&
                m_UIScriptProcess->GetIfFinishedBuilding(UnitType::WAR_FACT)) {

                setSelectToBuild(UnitType::WAR_FACT);
            } else {
                m_UIScriptProcess->AddToBuildQueue(UnitType::WAR_FACT);
            }
        }
        p.x += 5.F;
        p.y -= 38.F;
        if (m_UIScriptProcess->GetCurrentStructure() == UnitType::WAR_FACT) {
            dl->AddText(p, IM_COL32(2, 255, 2, 255),
                        m_UIScriptProcess->GetFormattedCD().c_str());
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 1)) {
            // advance power

            if (m_selectedStructureType == UnitType::NONE &&
                m_UIScriptProcess->GetIfFinishedBuilding(
                    UnitType::ADV_POWER_PLANT)) {

                setSelectToBuild(UnitType::ADV_POWER_PLANT);
            } else {
                m_UIScriptProcess->AddToBuildQueue(UnitType::ADV_POWER_PLANT);
            }
            LOG_DEBUG("TEST");
        }
        p.x += 80.F;
        if (m_UIScriptProcess->GetCurrentStructure() ==
            UnitType::ADV_POWER_PLANT) {
            dl->AddText(p, IM_COL32(2, 255, 2, 255),
                        m_UIScriptProcess->GetFormattedCD().c_str());
        }

        ImGui::NewLine();
        if (ImGui::Button("Radar Dome")) {
            LOG_DEBUG("TEST");
        }
        if (ImGui::Button("Service Depot")) {
            LOG_DEBUG("TEST");
        }
        if (ImGui::Button("Tech Center")) {
            LOG_DEBUG("TEST");
        }
        ImGui::PopFont();
        ImGui::EndTabItem();
    }
};

void UIClass::ShowInfantryTab() {
    ImDrawList *dl = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos();
    if (ImGui::BeginTabItem("Inf")) {
        if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet, 0)) {
            // rifle
            if (b_barackBuilt) {
                m_UIScriptProcess->AddToSpawnQueue(UnitType::INFANTRY);
                setUnitConstructCount(UnitType::INFANTRY, 1);
            }

            if (m_UIScriptProcess->GetCurrentInfType() == UnitType::INFANTRY) {
                dl->AddText(p, IM_COL32(2, 255, 2, 255),
                            m_UIScriptProcess->GetFormattedCD().c_str());
            }

            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet, 1)) {
            // rocket
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet, 2)) {
            // engineer
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::NewLine();
        if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet, 3)) {
            // medic
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet, 6)) {
            // tanya
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::EndTabItem();
    }
};
void UIClass::ShowDefTab() {
    if (ImGui::BeginTabItem("Def")) {
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 18)) {
            // sandbags

            setUnitConstructCount(UnitType::SANDBAGS, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 16)) {
            // pillbox
            setUnitConstructCount(UnitType::PILLBOX, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 14)) {
            // turret
            setUnitConstructCount(UnitType::TURRET, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::EndTabItem();
    }
};
void UIClass::ShowVehTab() {
    if (ImGui::BeginTabItem("Veh")) {
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 0)) {
            // lightTank
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 1)) {
            // mediumTank
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 4)) {
            // Art
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::NewLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 4)) {
            // Art
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 8)) {

            // OreTruck
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 4)) {
            // Art
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::NewLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 9)) {
            // MCV
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 11)) {
            // DemoTruck
            // setUnitConstructCount(UnitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (ImGui::Button("Truck")) {
            // truck
            setUnitConstructCount(UnitType::TRUCK, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::EndTabItem();
    }
};

bool UIClass::getImageButtonBySpriteSheetIndex(
    std::shared_ptr<SpriteSheet> spritesheet, int index) {

    auto uvcoord = getSpriteSheetCoordByIndex(spritesheet, index);
    return ImGui::ImageButton(
        (void *)(intptr_t)spritesheet->getGlunitByIndex(index),
        ImVec2(spritesheet->getSpriteSize().x, spritesheet->getSpriteSize().y),
        uvcoord[0], uvcoord[1]);
}

void UIClass::InitUnitQueue() {
    UIClass::s_unitConstructCount[UnitType::POWER_PLANT] = 0;
    UIClass::s_unitConstructCount[UnitType::BARRACKS] = 0;
    UIClass::s_unitConstructCount[UnitType::ORE_REF] = 0;
    UIClass::s_unitConstructCount[UnitType::WAR_FACT] = 0;
    UIClass::s_unitConstructCount[UnitType::ADV_POWER_PLANT] = 0;
    UIClass::s_unitConstructCount[UnitType::SANDBAGS] = 0;
    UIClass::s_unitConstructCount[UnitType::PILLBOX] = 0;
    UIClass::s_unitConstructCount[UnitType::TURRET] = 0;
    UIClass::s_unitConstructCount[UnitType::INFANTRY] = 0;
    UIClass::s_unitConstructCount[UnitType::TRUCK] = 0;
}
std::unique_ptr<Structure> UIClass::getSelectedBuilding() {
    switch (m_selectedStructureType) {
    case UnitType::BARRACKS: {
        setUnitConstructCount(UnitType::BARRACKS, 1);
        m_selectedStructureType = UnitType::NONE;
        m_UIScriptProcess->SetIfFinished(UnitType::BARRACKS, false);
        return std::make_unique<Barracks>();
    }
    case UnitType::ORE_REF: {
        setUnitConstructCount(UnitType::ORE_REF, 1);
        m_selectedStructureType = UnitType::NONE;
        m_UIScriptProcess->SetIfFinished(UnitType::ORE_REF, false);
        return std::make_unique<OreRefinery>();
    }
    case UnitType::POWER_PLANT: {
        setUnitConstructCount(UnitType::POWER_PLANT, 1);
        m_selectedStructureType = UnitType::NONE;
        m_UIScriptProcess->SetIfFinished(UnitType::POWER_PLANT, false);
        return std::make_unique<PowerPlants>();
    }
    case UnitType::WAR_FACT: {
        setUnitConstructCount(UnitType::WAR_FACT, 1);
        m_selectedStructureType = UnitType::NONE;
        m_UIScriptProcess->SetIfFinished(UnitType::WAR_FACT, false);
        return std::make_unique<WarFactory>();
    }
    case UnitType::ADV_POWER_PLANT: {
        setUnitConstructCount(UnitType::ADV_POWER_PLANT, 1);
        m_selectedStructureType = UnitType::NONE;
        m_UIScriptProcess->SetIfFinished(UnitType::ADV_POWER_PLANT, false);
        return std::make_unique<ADVPowerPlants>();
    }
    case UnitType::NONE: {
        printf("(UI)error! try to build when type == NONE\n");
    }
    }
}

bool UIClass::getIfAnyBuildingReadyToBuild() {

    return m_selectedStructureType != UnitType::NONE &&
           (m_UIScriptProcess->GetIfFinishedBuilding(UnitType::BARRACKS) ||
            m_UIScriptProcess->GetIfFinishedBuilding(UnitType::POWER_PLANT) ||
            m_UIScriptProcess->GetIfFinishedBuilding(UnitType::ORE_REF) ||
            m_UIScriptProcess->GetIfFinishedBuilding(UnitType::WAR_FACT) ||
            m_UIScriptProcess->GetIfFinishedBuilding(
                UnitType::ADV_POWER_PLANT));
}

void UIClass::checkExistBuilding(
    std::vector<std::shared_ptr<Structure>> buildingList) {
    b_barackBuilt = false;
    b_warfactoryBuilt = false;
    b_orerefineryBuilt = false;
    if (buildingList.size() == 0) {
        return;
    }
    for (auto i : buildingList) {
        if (std::dynamic_pointer_cast<Barracks>(i) && !b_barackBuilt) {
            m_barrackTargetCell = MapUtil::GlobalCoordToCellCoord(
                std::dynamic_pointer_cast<Barracks>(i)->GetWayPointLocation());
            b_barackBuilt = true;
            m_barrackCell =
                MapUtil::GlobalCoordToCellCoord(i->GetObjectLocation());
        } else if (std::dynamic_pointer_cast<WarFactory>(i) &&
                   !b_warfactoryBuilt) {
            m_warfactoryTargetCell = MapUtil::GlobalCoordToCellCoord(
                std::dynamic_pointer_cast<WarFactory>(i)
                    ->GetWayPointLocation());
            b_warfactoryBuilt = true;
            m_warfactoryCell =
                MapUtil::GlobalCoordToCellCoord(i->GetObjectLocation());
        } else if (std::dynamic_pointer_cast<OreRefinery>(i) &&
                   !b_orerefineryBuilt) {
            m_orerefineryTargetCell = MapUtil::GlobalCoordToCellCoord(
                std::dynamic_pointer_cast<OreRefinery>(i)
                    ->GetWayPointLocation());
            b_orerefineryBuilt = true;
            m_orerefineryCell =
                MapUtil::GlobalCoordToCellCoord(i->GetObjectLocation());
        }
    }
}

std::shared_ptr<Avatar> UIClass::getUnitFromUI() {
    // what the fuck???
    printf("(UI)return to GOM\n");
    auto Avatar = m_UIScriptProcess->spawnAvatar();
    m_UIScriptProcess->setIfReadytoSpawn(false);
    if (std::dynamic_pointer_cast<Infantry>(Avatar)) {

        Avatar->Start({m_barrackCell.x + 1, m_barrackCell.y - 1});

        // Avatar->setDestinationCell(m_barrackTargetCell);
    }
    printf("(UI)return to GOM success\n");
    return Avatar;
}
