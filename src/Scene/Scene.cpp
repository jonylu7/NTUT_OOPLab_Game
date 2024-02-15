//
// Created by 盧威任 on 2/15/24.
//
#include "Scene/Scene.hpp"

ImVec2 start_pos;
ImVec2 end_pos;
void Scene::Start(){

    LOG_TRACE("Start");
    m_GameObjectList[0]->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/Raccoon3.jpg"));
    m_GameObjectList[0]->SetZIndex(10);

    auto gf = std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 500,
                                            "Giraffe");
    gf->SetZIndex(m_GameObjectList[0]->GetZIndex() - 3);
    gf->Start();
    m_GameObjectList[0]->AppendChild(gf);

    m_GameObjectList[1]->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/capybara.png"));


    m_GameObjectList[2]->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/rac.png"));


    m_Structure->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/barracks.gif"));
    m_Structure->Start();
    m_Structure->SetCurrentUpdateMode(Structure::updateMode::Moveable);

    m_Inf->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/rac.png"));
    m_Inf->Start();

    m_GameObjectList[2]->AppendChild(gf);
    //rect.Init();
    m_SpriteSheet.Start(std::make_shared<Util::Image>("../assets/sprites/Allied Strucutre/Allied Structure SpriteSheet.png"),48,64,24,0);

    for (auto i:m_GameObjectList){
        i->Start();
    }

}

void Scene::Update(){
   // m_Structure->Update();
    m_Structure->UpdateUsingCamera(m_SceneCamera);
        //rect.Draw();
        if (Util::Input::IfScroll()) {
            auto delta = Util::Input::GetScrollDistance();
            m_SceneCamera.addCameraZoom(delta.y*CameraZoomingSpeed);
            //LOG_DEBUG("Scrolling: x: {}, y: {}", delta.x, delta.y);
        }

        if(Util::Input::IsLButtonPressed()){
            glm::vec2 ogLBlocation=Util::Input::GetCursorPosition();

            if(m_Structure->GetCurrentUpdateMode()==Structure::updateMode::Moveable){
                m_Structure->SetObjectLocation(ogLBlocation);
                m_Structure->SetCurrentUpdateMode(Structure::updateMode::Fixed);
                LOG_DEBUG("Fixed");
            }
        }
        if(Util::Input::IsRButtonPressed()){
            LOG_DEBUG("RPressed");
        }

        if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) ||
            Util::Input::IfExit()) {
        }

        if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
            LOG_DEBUG("A");
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
            LOG_DEBUG("B");
            Util::Input::SetCursorPosition({0.0F, 0.0F});
        }
        if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)){
            LOG_DEBUG("Left");
        }

        if(Util::Input::IsKeyPressed(Util::Keycode::UP)){
            LOG_DEBUG("UP");
        }
        if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)){
            LOG_DEBUG("RIght");
        }
        if(Util::Input::IsKeyPressed(Util::Keycode::DOWN)){
            LOG_DEBUG("Down");
        }

        /*
     *
         */

        int cursorAtBoarder=Core::Context::IsCurosrAtBoarder();
        switch(cursorAtBoarder){
        case(0):
            CameraPosition.y+=CameraMovingSpeed;
            break;
        case(1):
            CameraPosition.x+=CameraMovingSpeed;
            break;
        case(2):
            CameraPosition.y-=CameraMovingSpeed;
            break;
        case(3):
            CameraPosition.x-=CameraMovingSpeed;
            break;
        case(4):
            break;
        }
        cellTest.Draw();
        m_SpriteSheet.Update();

        m_Inf->Update();
        rect.Update();

        for (auto i:m_GameObjectList){
            i->Update();
        }
}

void Scene::imgui_ShowSelectionRect(ImVec2* start_pos, ImVec2* end_pos, ImGuiMouseButton mouse_button){
        IM_ASSERT(start_pos != NULL);
        IM_ASSERT(end_pos != NULL);
        if (ImGui::IsMouseClicked(mouse_button))
            *start_pos = ImGui::GetMousePos();
        if (ImGui::IsMouseDown(mouse_button))
        {
            *end_pos = ImGui::GetMousePos();
            ImDrawList* draw_list = ImGui::GetForegroundDrawList(); //ImGui::GetWindowDrawList();
            draw_list->AddRect(*start_pos, *end_pos, ImGui::GetColorU32(IM_COL32(255, 255, 255, 255)));   // Border
            //draw_list->AddRectFilled(*start_pos, *end_pos, ImGui::GetColorU32(IM_COL32(0, 130, 216, 50)));    // Background
        }
}




void Scene::imgui(){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        // put the stuff in here
        ImGui::Begin("Structure Selection Menu");
        m_SceneCamera.setPosition(CameraPosition);

        ImGui::Text(std::string("X: "+std::to_string(CameraPosition.x)+"  Y: "+std::to_string(CameraPosition.y)).c_str());
        ImGui::Text(fmt::format("Zoom: {}",CameraZoom).c_str());
        ImGui::Text(fmt::format("$ {}",1000).c_str());
        ImGui::Text(fmt::format("Power {}",50).c_str());
        if(ImGui::BeginTabBar("",ImGuiTabBarFlags_None) ){
            if (ImGui::BeginTabItem("Buildings")) {

                if (ImGui::Button("Power Plants")) {
                    LOG_DEBUG("TEST");
                } else if (ImGui::Button("Barracks")) {
                    LOG_DEBUG("TEST");
                    m_Structure->SetCurrentUpdateMode(Structure::updateMode::Moveable);
                } else if (ImGui::Button("Naval Yard")) {
                    LOG_DEBUG("TEST");
                    m_Inf->SetObjectLocation(glm::vec2(-190,100));
                    m_Inf->SetCurrentUpdateMode(Infantry::updateMode::MovingToDestination);
                } else if (ImGui::Button("Ore Refinery")) {
                    LOG_DEBUG("TEST");
                    m_Inf->SetCurrentUpdateMode(Infantry::updateMode::Standing);
                } else if (ImGui::Button("War Factory")) {
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
                Util::Image image("../assets/sprites/Service.png");
                ImGui::Image((void*)image.getTextureID(),ImVec2(48,64));

                if (ImGui::Button("Infantry")) {
                    LOG_DEBUG("TEST");
                }
                else if(ImGui::ImageButton("",(void*)(intptr_t)image.getTextureID(),ImVec2(48,64))){

                }
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        imgui_ShowSelectionRect(&start_pos,&end_pos);
        ImGui::End();

        //and above
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}