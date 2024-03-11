//
// Created by 盧威任 on 3/3/24.
//

#include "UI/UI.hpp"
#include "Map.hpp"

ImVec2 start_pos;
ImVec2 end_pos;
std::unordered_map<unitType, unsigned int> UIClass::s_unitQueue;

void UIClass::Start() {
    InitUnitQueue();
    m_IconSpriteSheet.Start(
        "../assets/sprites/ICON_Allied Structure SpriteSheet.png", 64, 48, 24,
        0);
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

    // put the stuff in here
    ImGui::Begin("Structure Selection Menu");

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

    if (ImGui::Button("Grid")) {
    }
    if (ImGui::BeginTabBar("", ImGuiTabBarFlags_None)) {

        if (ImGui::BeginTabItem("Buildings")) {

            if (getImageButtonBySpriteSheetIndex(7)) {
                // power plants
                setUnitCount(unitType::POWER_PLANT, 1);
                ButtonScript.buttonEvent(powerPlant);
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(22)) {
                // barracks
                setUnitCount(unitType::BARRACKS, 1);
                ButtonScript.buttonEvent(barracks);
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(8)) {
                // ore
                setUnitCount(unitType::ORE_REF, 1);
                ButtonScript.buttonEvent(oreRefinery);
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(20)) {
                // war factory
                setUnitCount(unitType::WAR_FACT, 1);
                ButtonScript.buttonEvent(warFactory);
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(1)) {
                // advance power
                setUnitCount(unitType::ADV_POWER_PLANT, 1);
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
            if (getImageButtonBySpriteSheetIndex(18)) {
                // sandbags
                setUnitCount(unitType::SANDBAGS, 1);
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(16)) {
                // pillbox
                setUnitCount(unitType::PILLBOX, 1);
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(14)) {
                // turret
                setUnitCount(unitType::TURRET, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Infantry")) {
            if (ImGui::Button("Infantry")) {
                // inf
                setUnitCount(unitType::INFANTRY, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Vehicles")) {
            if (ImGui::Button("Truck")) {
                // truck
                setUnitCount(unitType::TRUCK, 1);
                LOG_DEBUG("TEST");
            }
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::End();
}

std::vector<ImVec2> UIClass::getSpriteSheetCoordByIndex(int index) {
    return std::vector<ImVec2>(
        {ImVec2(SpriteSheet::UVtoImGuiCoord(
                    this->m_IconSpriteSheet.getUVbyIndex(index))[0]
                    .x,
                SpriteSheet::UVtoImGuiCoord(
                    m_IconSpriteSheet.getUVbyIndex(index))[0]
                    .y),
         ImVec2(SpriteSheet::UVtoImGuiCoord(
                    m_IconSpriteSheet.getUVbyIndex(index))[1]
                    .x,
                SpriteSheet::UVtoImGuiCoord(
                    m_IconSpriteSheet.getUVbyIndex(index))[1]
                    .y)});
}

bool UIClass::getImageButtonBySpriteSheetIndex(int index) {
    return ImGui::ImageButton(
        (void *)(intptr_t)m_IconSpriteSheet.getGlunitByIndex(index),
        ImVec2(m_IconSpriteSheet.getSpriteSize().x,
               m_IconSpriteSheet.getSpriteSize().y),
        this->getSpriteSheetCoordByIndex(index)[0],
        this->getSpriteSheetCoordByIndex(index)[1]);
}
void UIClass::InitUnitQueue() {
    UIClass::s_unitQueue[unitType::POWER_PLANT] = 0;
    UIClass::s_unitQueue[unitType::BARRACKS] = 0;
    UIClass::s_unitQueue[unitType::ORE_REF] = 0;
    UIClass::s_unitQueue[unitType::WAR_FACT] = 0;
    UIClass::s_unitQueue[unitType::ADV_POWER_PLANT] = 0;
    UIClass::s_unitQueue[unitType::SANDBAGS] = 0;
    UIClass::s_unitQueue[unitType::PILLBOX] = 0;
    UIClass::s_unitQueue[unitType::TURRET] = 0;
    UIClass::s_unitQueue[unitType::INFANTRY] = 0;
    UIClass::s_unitQueue[unitType::TRUCK] = 0;
}
