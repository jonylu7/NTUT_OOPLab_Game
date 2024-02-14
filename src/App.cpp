#include "App.hpp"
#include "Infantry.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Core/Context.hpp"
#include "Cell.hpp"

void App::Start() {

    LOG_TRACE("Start");

    m_Giraffe->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/Raccoon3.jpg"));
    m_Giraffe->SetZIndex(10);
    m_Giraffe->Start();

    auto gf = std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 500,
                                            "Giraffe");
    gf->SetZIndex(m_Giraffe->GetZIndex() - 3);
    gf->Start();
    m_Giraffe->AppendChild(gf);

    m_Capybara->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
    m_Capybara->Start();

    m_Barracks->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/Barracks.gif"));
    m_Barracks->Start();

    m_Structure->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/Barracks.gif"));
    m_Structure->Start();

    m_Inf->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/rac.png"));
    m_Inf->Start();

    m_Barracks->AppendChild(gf);
    m_CurrentState = State::UPDATE;
    //rect.Init();


}
glm::vec2 ogLBlocation=glm::vec2(0,0);
bool LBPressing=false;
Util::Transform lbLocation;
enum buttonMode{A,B,C};
buttonMode currentModde;
ImVec2 start_pos;
ImVec2 end_pos;

bool ShowSelectionRect(ImVec2* start_pos, ImVec2* end_pos, ImGuiMouseButton mouse_button = ImGuiMouseButton_Left)
{
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
    return ImGui::IsMouseReleased(mouse_button);
}

void App::Update() {

    //rect.Draw();
    if (Util::Input::IfScroll()) {
        auto delta = Util::Input::GetScrollDistance();
        CameraZoom+=delta.y*CameraZoomingSpeed;
        //LOG_DEBUG("Scrolling: x: {}, y: {}", delta.x, delta.y);
    }
    if(Util::Input::IsLButtonUp()&&LBPressing==true){
        ogLBlocation=glm::vec2(0,0);
        LBPressing=false;
    }

    if(Util::Input::IsLButtonPressed()){
        glm::vec2 ogLBlocation=Util::Input::GetCursorPosition();


        auto newCappy=std::make_shared<Capybara>();
        newCappy->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
        newCappy->SetZIndex(-1);
        m_Capybara->AppendChild(newCappy);
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
        m_CurrentState = State::END;
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
    m_Barracks->Update();
    //m_Giraffe->Update();
    m_Capybara->Update(lbLocation);
    //m_Triangle.Update();
    m_Structure->Update();
    m_Inf->Update();
    rect.Update();




    //Ui->update at here

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    // put the stuff in here
    ImGui::Begin("Structure Selection Menu");

    ImGui::Text(std::string("X: "+std::to_string(CameraPosition.x)+"  Y: "+std::to_string(CameraPosition.y)).c_str());
    ImGui::Text(fmt::format("Zoom: {}",CameraZoom).c_str());
    ImGui::Text(fmt::format("$ {}",1000).c_str());
    ImGui::Text(fmt::format("Power {}",50).c_str());
    if(ImGui::BeginTabBar("",ImGuiTabBarFlags_None) ){
        if (ImGui::BeginTabItem("Buildings")) {

        if (ImGui::Button("Power Plants")) {
            currentModde = buttonMode::A;
        } else if (ImGui::Button("Barracks")) {
            currentModde = buttonMode::B;
            m_Structure->SetCurrentUpdateMode(Structure::updateMode::Moveable);
        } else if (ImGui::Button("Naval Yard")) {
            currentModde = buttonMode::C;
            m_Inf->SetObjectLocation(glm::vec2(-190,100));
            m_Inf->SetCurrentUpdateMode(Infantry::updateMode::MovingToDestination);
        } else if (ImGui::Button("Ore Refinery")) {
            currentModde = buttonMode::C;
            m_Inf->SetCurrentUpdateMode(Infantry::updateMode::Standing);
        } else if (ImGui::Button("War Factory")) {
            currentModde = buttonMode::C;
        } else if (ImGui::Button("Radar Dome")) {
            currentModde = buttonMode::C;
        } else if (ImGui::Button("Service Depot")) {
            currentModde = buttonMode::C;
        } else if (ImGui::Button("Advance Power")) {
            currentModde = buttonMode::C;
        } else if (ImGui::Button("HeliPad")) {
            currentModde = buttonMode::C;
        } else if (ImGui::Button("Tech Center")) {
            currentModde = buttonMode::C;
        }
        ImGui::EndTabItem();
        } else if (ImGui::BeginTabItem("Barracks")) {
        //it wont show up, need to be fixed
        if (ImGui::Button("Normal Troops")) {
            currentModde = buttonMode::C;
        }
        ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ShowSelectionRect(&start_pos,&end_pos);
    ImGui::End();

    //and above
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
