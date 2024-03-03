//
// Created by 盧威任 on 3/3/24.
//

#include "UI.hpp"

ImVec2 start_pos;
ImVec2 end_pos;

void UIClass::Start() {
    m_SpriteSheet.Start(
        "../assets/sprites/ICON_Allied Structure SpriteSheet.png", 64, 48, 24,
        0);
    m_Grid.StartDrawingGridByWindowSize();
}

void UIClass::Update() {
    ShowCursorSelectionRegion(&start_pos, &end_pos, ImGuiMouseButton_Left);
    ShowPlayerConstructionMenu();
    m_Grid.Update();
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
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    // put the stuff in here
    ImGui::Begin("Structure Selection Menu");
    /*
    ImGui::Text(
        std::string("X: " + std::to_string(m_SceneCamera.getPosition().x) +
                    "  Y: " + std::to_string(m_SceneCamera.getPosition().y))
            .c_str());
    ImGui::Text(fmt::format("Zoom: {}", m_SceneCamera.getCameraZoom()).c_str());
    ImGui::Text(fmt::format("$ {}", 1000).c_str());
    ImGui::Text(fmt::format("Power {}", 50).c_str());
     */
    if (ImGui::Button("Grid")) {
        m_Grid.switchActivate();
    }
    if (ImGui::BeginTabBar("", ImGuiTabBarFlags_None)) {

        if (ImGui::BeginTabItem("Buildings")) {

            if (ImGui::Button("Power Plants")) {
                LOG_DEBUG("TEST");
            } else if (ImGui::Button("Barracks")) {
                LOG_DEBUG("TEST");
            } else if (ImGui::Button("Naval Yard")) {
                LOG_DEBUG("TEST");
            } else if (ImGui::Button("Ore Refinery")) {
                LOG_DEBUG("TEST");
            } else if (ImGui::ImageButton(
                           (void *)(intptr_t)m_SpriteSheet.getGlunitByIndex(3),
                           ImVec2(64, 48),
                           ImVec2(SpriteSheet::UVtoImGuiCoord(
                                      m_SpriteSheet.getUVbyIndex(3))[0]
                                      .x,
                                  SpriteSheet::UVtoImGuiCoord(
                                      m_SpriteSheet.getUVbyIndex(3))[0]
                                      .y),
                           ImVec2(SpriteSheet::UVtoImGuiCoord(
                                      m_SpriteSheet.getUVbyIndex(3))[1]
                                      .x,
                                  SpriteSheet::UVtoImGuiCoord(
                                      m_SpriteSheet.getUVbyIndex(3))[1]
                                      .y))) {
                LOG_DEBUG("TEST");
            } else if (ImGui::Button("Radar Dome")) {
                LOG_DEBUG("TEST");
            } else if (ImGui::Button("Service Depot")) {
                LOG_DEBUG("TEST");
            } else if (ImGui::Button("Advance Power")) {
                LOG_DEBUG("TEST");
            } else if (ImGui::Button("HeliPad")) {
                LOG_DEBUG("TEST");
            } else if (ImGui::Button("Tech Center")) {
                LOG_DEBUG("TEST");
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Barracks")) {
            /* ImGui::Image(, ImVec2(48, 64));

            if (ImGui::Button("Infantry")) {
                LOG_DEBUG("TEST");
            } else if (ImGui::ImageButton(
                           "", (void *)(intptr_t)image.getTextureID(),
                           ImVec2(48, 64))) {
            }
             */
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::End();

    // and above
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
