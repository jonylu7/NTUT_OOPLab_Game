//
// Created by 盧威任 on 2/15/24.
//
#include "Scene/DefaultScene.hpp"

ImVec2 start_pos;
ImVec2 end_pos;
void DefaultScene::Start() {

    LOG_TRACE("Start");
    m_GameObjectList[0]->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/Raccoon3.jpg"));
    m_GameObjectList[0]->SetZIndex(10);

    m_GameObjectList[1]->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/capybara.png"));

    m_Structure->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/barracks.png"));
    m_Structure->SetZIndex(0);
    m_Structure->SetObjectLocation({0, 0});
    m_Structure->Start();
    m_Structure->SetCurrentUpdateMode(Structure::updateMode::Moveable);
    m_Renderer.AddChild(m_Structure);

    m_Inf->Start();

    //`m_GameObjectList[2]->AppendChild(gf);
    // rect.Init();
    m_SpriteSheet.Start(
        "../assets/sprites/ICON_Allied Structure SpriteSheet.png", 64, 48, 24,
        0);

    for (auto i : m_GameObjectList) {
        i->Start();
    }
    testGrid.StartDrawingGridByWindowSize();

    m_Renderer.AddChild(m_Structure);

    // init map
    m_TileSetSpriteSheet->Start("../assets/sprites/TILESET_Field.png", 64, 64,
                                200, 0);

    m_OgMap = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    m_OgMap = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<std::shared_ptr<TileClass>> maps;
    for (unsigned int i = 0; i < 10; i++) {
        maps.push_back(std::make_shared<TileClass>("rock-" + std::to_string(i),
                                                   false, false, true, i));
    }
    /* doing some weird stuff, fix is needed
    std::vector<std::shared_ptr<TileClass>> maps =
        m_Map.readMapAndTileSet(m_OgMap, m_tileSets);
        */

    m_Map.Init(maps, m_TileSetSpriteSheet, 5, 2);
}

void DefaultScene::Update() {

    m_Map.Draw();
    testGrid.Update();
    m_Structure->SetCurrentUpdateMode(Structure::updateMode::Fixed);
    m_Structure->Update();

    if (Util::Input::IsKeyPressed(Util::Keycode::END)) {
        glm::vec2 ogLBlocation = Util::Input::GetCursorPosition();

        if (m_Structure->GetCurrentUpdateMode() ==
            Structure::updateMode::Moveable) {
            m_Structure->SetObjectLocation(ogLBlocation);
            m_Structure->SetCurrentUpdateMode(Structure::updateMode::Fixed);
            LOG_DEBUG("Fixed");
        }
    }

    m_SceneCamera.Update();

    m_SpriteSheet.DrawSpriteByIndex(10, Util::Transform(), 0);

    m_Inf->Update();
    rect.Update();
    m_Renderer.Update();

    for (auto i : m_GameObjectList) {
        i->Update();
    }
}

void DefaultScene::imgui_ShowSelectionRect(ImVec2 *start_pos, ImVec2 *end_pos,
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

void DefaultScene::imgui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    // put the stuff in here
    ImGui::Begin("Structure Selection Menu");

    ImGui::Text(
        std::string("X: " + std::to_string(m_SceneCamera.getPosition().x) +
                    "  Y: " + std::to_string(m_SceneCamera.getPosition().y))
            .c_str());
    ImGui::Text(fmt::format("Zoom: {}", m_SceneCamera.getCameraZoom()).c_str());
    ImGui::Text(fmt::format("$ {}", 1000).c_str());
    ImGui::Text(fmt::format("Power {}", 50).c_str());
    if (ImGui::Button("Grid")) {
        testGrid.switchActivate();
    }
    if (ImGui::BeginTabBar("", ImGuiTabBarFlags_None)) {

        if (ImGui::BeginTabItem("Buildings")) {

            if (ImGui::Button("Power Plants")) {
                LOG_DEBUG("TEST");
            } else if (ImGui::Button("Barracks")) {
                LOG_DEBUG("TEST");
                m_Structure->SetCurrentUpdateMode(
                    Structure::updateMode::Moveable);
            } else if (ImGui::Button("Naval Yard")) {
                LOG_DEBUG("TEST");
                m_Inf->SetObjectLocation(glm::vec2(-190, 100));
                m_Inf->SetCurrentUpdateMode(
                    Infantry::updateMode::MovingToDestination);
            } else if (ImGui::Button("Ore Refinery")) {
                LOG_DEBUG("TEST");
                m_Inf->SetCurrentUpdateMode(Infantry::updateMode::Standing);
            } else if (ImGui::ImageButton(
                           (void *)(intptr_t)m_SpriteSheet.getGlunitByIndex(10),
                           ImVec2(64, 48))) {
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
    imgui_ShowSelectionRect(&start_pos, &end_pos);
    ImGui::End();

    // and above
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
