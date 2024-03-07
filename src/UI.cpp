//
// Created by 盧威任 on 3/3/24.
//

#include "UI.hpp"
#include "Map.hpp"

ImVec2 start_pos;
ImVec2 end_pos;

void UIClass::Start() {
    m_SpriteSheet.Start(
        "../assets/sprites/ICON_Allied Structure SpriteSheet.png", 64, 48, 24,
        0);
    InitGrid();

}

void UIClass::Update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();

    ImGui::NewFrame();
    ShowCursorSelectionRegion(&start_pos, &end_pos, ImGuiMouseButton_Left);
    ShowPlayerConstructionMenu();

    Util::Transform trans;
    trans.translation={-1250.F,0};
    trans.scale={2.F,2.F};
    int zindex = 2;
    m_Grid.DrawUsingCamera(trans, zindex);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

    glm::vec2 CursorGlobalPosition=MapClass::ScreenToGlobalCoord(glm::vec2(Util::Input::GetCursorPosition()));
    ImGui::Text(
        std::string("X: " + std::to_string(  CursorGlobalPosition.x) +
                    "  Y: " + std::to_string(CursorGlobalPosition.y))
            .c_str());
    //ImGui::Text(fmt::format("Zoom: {}", m_SceneCamera.getCameraZoom()).c_str());
    ImGui::Text(fmt::format("$ {}", 1000).c_str());
    ImGui::Text(fmt::format("Power {}", 50).c_str());

    if (ImGui::Button("Grid")) {
        m_Grid.switchActivate();
    }
    if (ImGui::BeginTabBar("", ImGuiTabBarFlags_None)) {

        if (ImGui::BeginTabItem("Buildings")) {

            if (getImageButtonBySpriteSheetIndex(7)) {
                // power plants
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(22)) {
                // barracks
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(8)) {
                // ore
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(20)) {
                // war factory
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(1)) {
                // advance power
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
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(16)) {
                // pillbox
                LOG_DEBUG("TEST");
            }
            if (getImageButtonBySpriteSheetIndex(14)) {
                // turret
                LOG_DEBUG("TEST");
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Troopers")) {
            if (ImGui::Button("Infantry")) {
                // inf
                LOG_DEBUG("TEST");
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Vehicles")) {
            if (ImGui::Button("Truck")) {
                // truck
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
        {ImVec2(
             SpriteSheet::UVtoImGuiCoord(
                 this->m_SpriteSheet.getUVbyIndex(index))[0]
                 .x,
             SpriteSheet::UVtoImGuiCoord(m_SpriteSheet.getUVbyIndex(index))[0]
                 .y),
         ImVec2(
             SpriteSheet::UVtoImGuiCoord(m_SpriteSheet.getUVbyIndex(index))[1]
                 .x,
             SpriteSheet::UVtoImGuiCoord(m_SpriteSheet.getUVbyIndex(index))[1]
                 .y)});
}

bool UIClass::getImageButtonBySpriteSheetIndex(int index) {
    return ImGui::ImageButton(
        (void *)(intptr_t)m_SpriteSheet.getGlunitByIndex(index),
        ImVec2(m_SpriteSheet.getSpriteSize().x,
               m_SpriteSheet.getSpriteSize().y),
        this->getSpriteSheetCoordByIndex(index)[0],
        this->getSpriteSheetCoordByIndex(index)[1]);
}
