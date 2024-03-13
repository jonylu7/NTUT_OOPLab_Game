//
// Created by 盧威任 on 3/3/24.
//

#include "UI/UI.hpp"
#include "Map.hpp"

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
}

void UIClass::Update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();

    ImGui::NewFrame();
    ShowCursorSelectionRegion(&start_pos, &end_pos, ImGuiMouseButton_Left);
    ShowPlayerConstructionMenu();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ButtonScript.Update();
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

void UIClass::ShowPlayerConstructionMenu() {
    auto windowSettings = ImGuiWindowFlags_NoMove |
                          ImGuiWindowFlags_NoScrollbar |
                          ImGuiWindowFlags_NoResize;

    // put the stuff in here
    ImGui::Begin("Structure Selection Menu", nullptr, windowSettings);

    glm::vec2 CursorGlobalPosition = MapClass::ScreenToGlobalCoord(
        glm::vec2(Util::Input::GetCursorPosition()));
    ImGui::Text(std::string("X: " + std::to_string(CursorGlobalPosition.x) +
                            "  Y: " + std::to_string(CursorGlobalPosition.y))
                    .c_str());
    auto cellLocation = MapClass::GlobalCoordToCellCoord(CursorGlobalPosition);
    ImGui::Text(std::string("Cell X: " + std::to_string(int(cellLocation.x)) +
                            "  Cell Y: " + std::to_string(int(cellLocation.y)))
                    .c_str());
    // ImGui::Text(fmt::format("Zoom: {}",
    // m_SceneCamera.getCameraZoom()).c_str());
    ImGui::Text(fmt::format("$ {}", 1000).c_str());
    ImGui::Text(fmt::format("Power {}", 50).c_str());
    ImGui::SetWindowSize(ImVec2(250, 580));
    ImGui::SetWindowPos(ImVec2(992, 48));
    if (ImGui::Button("Grid")) {
    }
    if (ImGui::BeginTabBar("", ImGuiTabBarFlags_None)) {

        if (ImGui::BeginTabItem("Buildings")) {
            if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet,
                                                 7)) {
                // power plants

                setUnitConstructCount(unitType::POWER_PLANT, 1);
                ButtonScript.buttonEvent(powerPlant);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet,
                                                 22)) {
                // barracks
                setUnitConstructCount(unitType::BARRACKS, 1);
                ButtonScript.buttonEvent(barracks);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet,
                                                 8)) {
                // ore
                setUnitConstructCount(unitType::ORE_REF, 1);
                ButtonScript.buttonEvent(oreRefinery);
                LOG_DEBUG("TEST");
            }

            ImGui::NewLine();
            if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet,
                                                 20)) {
                // war factory
                setUnitConstructCount(unitType::WAR_FACT, 1);
                ButtonScript.buttonEvent(warFactory);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet,
                                                 1)) {
                // advance power
                setUnitConstructCount(unitType::ADV_POWER_PLANT, 1);
                ButtonScript.buttonEvent(advPowerPlant);
                LOG_DEBUG("TEST");
            }
            if (ImGui::Button("Radar Dome")) {
                LOG_DEBUG("TEST");
            }
            if (ImGui::Button("Service Depot")) {
                LOG_DEBUG("TEST");
            }
            if (ImGui::Button("Tech Center")) {
                LOG_DEBUG("TEST");
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Defense Structure")) {
            if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet,
                                                 18)) {
                // sandbags
                setUnitConstructCount(unitType::SANDBAGS, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet,
                                                 16)) {
                // pillbox
                setUnitConstructCount(unitType::PILLBOX, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_StructureIconSpriteSheet,
                                                 14)) {
                // turret
                setUnitConstructCount(unitType::TURRET, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Infantry")) {
            if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet,
                                                 0)) {
                // rifle
                setUnitConstructCount(unitType::INFANTRY, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet,
                                                 1)) {
                // rocket
                // setUnitConstructCount(unitType::, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet,
                                                 2)) {
                // engineer
                // setUnitConstructCount(unitType::, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::NewLine();
            if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet,
                                                 3)) {
                // medic
                // setUnitConstructCount(unitType::, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_InfantryIconSpriteSheet,
                                                 6)) {
                // tanya
                // setUnitConstructCount(unitType::, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Vehicles")) {
            if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet,
                                                 0)) {
                // lightTank
                // setUnitConstructCount(unitType::, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet,
                                                 1)) {
                // mediumTank
                // setUnitConstructCount(unitType::, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet,
                                                 4)) {
                // Art
                // setUnitConstructCount(unitType::, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::NewLine();
            if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet,
                                                 4)) {
                // Art
                // setUnitConstructCount(unitType::, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet,
                                                 8)) {
                // OreTruck
                // setUnitConstructCount(unitType::, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet,
                                                 4)) {
                // Art
                // setUnitConstructCount(unitType::, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::NewLine();
            if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet,
                                                 9)) {
                // MCV
                // setUnitConstructCount(unitType::, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::SameLine();
            if (getImageButtonBySpriteSheetIndex(m_VehiclesIconSpriteSheet,
                                                 11)) {
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

bool UIClass::getImageButtonBySpriteSheetIndex(
    std::shared_ptr<SpriteSheet> spritesheet, int index) {
    std::string Text = "test";
    ImDrawList *dl = ImGui::GetWindowDrawList();
    dl->AddText(ImVec2(100.f, 100.f), IM_COL32(255, 255, 255, 100), "TEST");
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
