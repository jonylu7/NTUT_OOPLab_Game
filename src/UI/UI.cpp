//
// Created by 盧威任 on 3/3/24.
//

#include "UI/UI.hpp"
#include "Map/Map.hpp"

ImVec2 start_pos;
ImVec2 end_pos;
std::unordered_map<unitType, unsigned int> UIClass::s_unitConstructCount;

void UIClass::Start() {
    InitUnitQueue();
    m_StructureIconSpriteSheet->Start(
        "../assets/sprites/ICON_Allied_Structure.png", 64, 48, 24, 0);
    m_InfantryIconSpriteSheet->Start(
        "../assets/sprites/ICON_Allied_Infantry.png", 64, 48, 8, 0);
    m_VehiclesIconSpriteSheet->Start(
        "../assets/sprites/ICON_Allied_Vehicles.png", 64, 48, 12, 0);

    io.FontGlobalScale *= 0.115f; // Adjust as needed
}

void UIClass::Update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();

    ImGui::NewFrame();
    ShowCursorSelectionRegion(&start_pos, &end_pos, ImGuiMouseButton_Left);
    ShowPlayerConstructionMenu();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ButtonScript.Update(getIfAnyBuildingReadyToBuild());
    // printf("(UI)Button Lock :
    // %s,%s\n",selectLock()?"Unlock":"Lock",b_SelectToBuild?"True":"False");
}

void UIClass::ShowCursorSelectionRegion(ImVec2 *start_pos, ImVec2 *end_pos,
                                        ImGuiMouseButton mouse_button) {
    IM_ASSERT(start_pos != NULL);
    IM_ASSERT(end_pos != NULL);
    if (ImGui::IsMouseClicked(mouse_button))
        *start_pos = ImGui::GetMousePos();
    if (ImGui::IsMouseDown(mouse_button)) {
        *end_pos = ImGui::GetMousePos();
        ImDrawList *draw_list =
            ImGui::GetForegroundDrawList(); // ImGui::GetWindowDrawList();
        draw_list->AddRect(
            *start_pos, *end_pos,
            ImGui::GetColorU32(IM_COL32(255, 255, 255, 255))); // Border
        // draw_list->AddRectFilled(*start_pos, *end_pos,
        // ImGui::GetColorU32(IM_COL32(0, 130, 216, 50)));    // Background
    }
}

void UIClass::ShowHeaderSection() {

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
    ImGui::Text(fmt::format("$ {}", m_Player->getTotalCurrency()).c_str());
    ImGui::Text(
        fmt::format("Power {}", m_gameObjectManager->GetTotalPower()).c_str());
    ImGui::PushFont(sacker_med);
    if (ImGui::Button("Grid")) {
    }
    ImGui::PopFont();
}
void UIClass::ShowPlayerConstructionMenu() {
    auto windowSettings = ImGuiWindowFlags_NoMove |
                          ImGuiWindowFlags_NoScrollbar |
                          ImGuiWindowFlags_NoResize;

    // put the stuff in here
    ImGui::Begin("Structure Selection Menu", nullptr, windowSettings);
    ShowHeaderSection();
    ImGui::SetWindowSize(ImVec2(250, 580));
    ImGui::SetWindowPos(ImVec2(992, 48));

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
            if (selectLock() &&
                ButtonScript.GetIfFinished(unitType::POWER_PLANT)) {
                setSelectToBuild(unitType::POWER_PLANT);
            } else {
                ButtonScript.AddToBuildQueue(unitType::POWER_PLANT);
            }
        }

        ImDrawList *dl = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetCursorScreenPos();
        p.x += 5.F;
        p.y -= 38.F;
        ImGui::PushFont(sacker_heav);
        if (ButtonScript.GetCurrentStructure() == unitType::POWER_PLANT) {
            dl->AddText(p, IM_COL32(2, 255, 2, 255),
                        ButtonScript.GetFormattedCD().c_str());
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 22)) {
            // barracks
            if (selectLock() &&
                ButtonScript.GetIfFinished(unitType::BARRACKS)) {
                setSelectToBuild(unitType::BARRACKS);
            } else {
                ButtonScript.AddToBuildQueue(unitType::BARRACKS);
            }
        }
        p.x += 80.F;
        if (ButtonScript.GetCurrentStructure() == unitType::BARRACKS) {
            dl->AddText(p, IM_COL32(2, 255, 2, 255),
                        ButtonScript.GetFormattedCD().c_str());
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 8)) {
            // ore
            if (selectLock() && ButtonScript.GetIfFinished(unitType::ORE_REF)) {
                setSelectToBuild(unitType::ORE_REF);
            } else {
                ButtonScript.AddToBuildQueue(unitType::ORE_REF);
            }
        }
        p.x += 80.F;
        if (ButtonScript.GetCurrentStructure() == unitType::ORE_REF) {
            dl->AddText(p, IM_COL32(2, 255, 2, 255),
                        ButtonScript.GetFormattedCD().c_str());
        }
        ImGui::NewLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 20)) {
            // war factory
            if (selectLock() &&
                ButtonScript.GetIfFinished(unitType::WAR_FACT)) {
                setSelectToBuild(unitType::WAR_FACT);
            } else {
                ButtonScript.AddToBuildQueue(unitType::WAR_FACT);
            }
        }
        dl = ImGui::GetWindowDrawList();
        p = ImGui::GetCursorScreenPos();
        p.x += 5.F;
        p.y -= 38.F;
        if (ButtonScript.GetCurrentStructure() == unitType::WAR_FACT) {
            dl->AddText(p, IM_COL32(2, 255, 2, 255),
                        ButtonScript.GetFormattedCD().c_str());
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 1)) {
            // advance power
            if (selectLock() &&
                ButtonScript.GetIfFinished(unitType::ADV_POWER_PLANT)) {
                setSelectToBuild(unitType::ADV_POWER_PLANT);
            } else {
                ButtonScript.AddToBuildQueue(unitType::ADV_POWER_PLANT);
            }
            LOG_DEBUG("TEST");
        }
        p.x += 80.F;
        if (ButtonScript.GetCurrentStructure() == unitType::ADV_POWER_PLANT) {
            dl->AddText(p, IM_COL32(2, 255, 2, 255),
                        ButtonScript.GetFormattedCD().c_str());
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
    if (ImGui::BeginTabItem("Inf")) {
        if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet, 0)) {
            // rifle
            if (b_barackBuilt) {
                ButtonScript.AddToSpawnQueue(unitType::INFANTRY);
                setUnitConstructCount(unitType::INFANTRY, 1);
            }

            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet, 1)) {
            // rocket
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet, 2)) {
            // engineer
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::NewLine();
        if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet, 3)) {
            // medic
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet, 6)) {
            // tanya
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::EndTabItem();
    }
};
void UIClass::ShowDefTab() {
    if (ImGui::BeginTabItem("Def")) {
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 18)) {
            // sandbags

            setUnitConstructCount(unitType::SANDBAGS, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 16)) {
            // pillbox
            setUnitConstructCount(unitType::PILLBOX, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet, 14)) {
            // turret
            setUnitConstructCount(unitType::TURRET, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::EndTabItem();
    }
};
void UIClass::ShowVehTab() {
    if (ImGui::BeginTabItem("Veh")) {
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 0)) {
            // lightTank
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 1)) {
            // mediumTank
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 4)) {
            // Art
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::NewLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 4)) {
            // Art
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 8)) {

            // OreTruck
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 4)) {
            // Art
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::NewLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 9)) {
            // MCV
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet, 11)) {
            // DemoTruck
            // setUnitConstructCount(unitType::, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::SameLine();
        if (ImGui::Button("Truck")) {
            // truck
            setUnitConstructCount(unitType::TRUCK, 1);
            LOG_DEBUG("TEST");
        }
        ImGui::EndTabItem();
    }
};

bool UIClass::getImageButtonBySpriteSheetIndex(
    std::shared_ptr<SpriteSheet> spritesheet, int index) {
    std::string Text = "test";

    auto uvcoord = getSpriteSheetCoordByIndex(spritesheet, index);
    return ImGui::ImageButton(
        (void *)(intptr_t)spritesheet->getGlunitByIndex(index),
        ImVec2(spritesheet->getSpriteSize().x, spritesheet->getSpriteSize().y),
        uvcoord[0], uvcoord[1]);
}

void UIClass::InitUnitQueue() {
    UIClass::s_unitConstructCount[unitType::POWER_PLANT] = 0;
    UIClass::s_unitConstructCount[unitType::BARRACKS] = 0;
    UIClass::s_unitConstructCount[unitType::ORE_REF] = 0;
    UIClass::s_unitConstructCount[unitType::WAR_FACT] = 0;
    UIClass::s_unitConstructCount[unitType::ADV_POWER_PLANT] = 0;
    UIClass::s_unitConstructCount[unitType::SANDBAGS] = 0;
    UIClass::s_unitConstructCount[unitType::PILLBOX] = 0;
    UIClass::s_unitConstructCount[unitType::TURRET] = 0;
    UIClass::s_unitConstructCount[unitType::INFANTRY] = 0;
    UIClass::s_unitConstructCount[unitType::TRUCK] = 0;
}
std::unique_ptr<Structure> UIClass::getSelectedBuilding() {
    b_SelectToBuild = false;
    if (getIfSelectToBuild(unitType::BARRACKS)) {
        setUnitConstructCount(unitType::BARRACKS, 1);
        b_Baracks = false;
        ButtonScript.SetIfFinished(unitType::BARRACKS, false);
        return std::make_unique<Barracks>();
    }
    if (getIfSelectToBuild(unitType::ORE_REF)) {
        setUnitConstructCount(unitType::ORE_REF, 1);
        b_OreRefinery = false;
        ButtonScript.SetIfFinished(unitType::ORE_REF, false);
        return std::make_unique<OreRefinery>();
    }
    if (getIfSelectToBuild(unitType::POWER_PLANT)) {
        setUnitConstructCount(unitType::POWER_PLANT, 1);
        b_PowerPlants = false;
        ButtonScript.SetIfFinished(unitType::POWER_PLANT, false);
        return std::make_unique<PowerPlants>();
    }
    if (getIfSelectToBuild(unitType::WAR_FACT)) {
        setUnitConstructCount(unitType::WAR_FACT, 1);
        b_WarFactory = false;
        ButtonScript.SetIfFinished(unitType::WAR_FACT, false);
        return std::make_unique<WarFactory>();
    }
    if (getIfSelectToBuild(unitType::ADV_POWER_PLANT)) {
        setUnitConstructCount(unitType::ADV_POWER_PLANT, 1);
        b_ADVPowerPlant = false;
        ButtonScript.SetIfFinished(unitType::ADV_POWER_PLANT, false);
        return std::make_unique<ADVPowerPlants>();
    }
}
bool UIClass::getIfSelectToBuild(unitType type) {
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
void UIClass::setSelectToBuild(unitType type) {
    b_SelectToBuild = true;
    switch (type) {
    case unitType::BARRACKS:
        b_Baracks = true;
        break;
    case unitType::ORE_REF:
        b_OreRefinery = true;
        break;
    case unitType::POWER_PLANT:
        b_PowerPlants = true;
        break;
    case unitType::WAR_FACT:
        b_WarFactory = true;
        break;
    case unitType::ADV_POWER_PLANT:
        b_ADVPowerPlant = true;
        break;
    }
}
bool UIClass::selectLock() {
    return !(b_Baracks | b_OreRefinery | b_PowerPlants | b_WarFactory |
             b_ADVPowerPlant);
}
bool UIClass::getIfAnyBuildingReadyToBuild() {
    return b_SelectToBuild &&
           (ButtonScript.GetIfFinished(unitType::BARRACKS) ||
            ButtonScript.GetIfFinished(unitType::POWER_PLANT) ||
            ButtonScript.GetIfFinished(unitType::ORE_REF) ||
            ButtonScript.GetIfFinished(unitType::WAR_FACT) ||
            ButtonScript.GetIfFinished(unitType::ADV_POWER_PLANT));
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
    printf("(UI)return to GOM\n");
    auto Avatar = ButtonScript.spawnAvatar();
    ButtonScript.setIfReadytoSpawn(false);
    if (std::dynamic_pointer_cast<Infantry>(Avatar)) {

        Avatar->Start(m_barrackCell);
        Avatar->setNewDestination(m_barrackTargetCell);

    } /*else if(std::dynamic_pointer_cast< >(Avatar)){
        Avatar->Start(m_warfactoryCell,m_Map);
        Avatar->setNewDestination(m_warfactoryTargetCell);
    } else if(std::dynamic_pointer_cast< >(Avatar)){
        Avatar->Start(m_orerefineryCell,m_Map);
        Avatar->setNewDestination(m_orerefineryTargetCell);
    }*/
    printf("(UI)return to GOM success\n");
    return Avatar;
}
