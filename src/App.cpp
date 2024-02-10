#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

void App::Start() {

    LOG_TRACE("Start");

    m_Giraffe->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
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

    m_Structure->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/Airfield.png"));
    m_Structure->Start();


    m_Barracks->AppendChild(gf);
    m_CurrentState = State::UPDATE;


}
glm::vec2 ogLBlocation=glm::vec2(0,0);
bool LBPressing=false;
Util::Transform lbLocation;
enum buttonMode{A,B,C};
buttonMode currentModde;
void App::Update() {


    if (Util::Input::IfScroll()) {
        auto delta = Util::Input::GetScrollDistance();
        LOG_DEBUG("Scrolling: x: {}, y: {}", delta.x, delta.y);
    }
    if(Util::Input::IsLButtonUp()&&LBPressing==true){
        ogLBlocation=glm::vec2(0,0);
        LBPressing=false;
    }

    if(Util::Input::IsLButtonPressed()){
        glm::vec2 ogLBlocation=Util::Input::GetCursorPosition();
        LBPressing=true;
        LOG_DEBUG("LButton");
        lbLocation.translation=ogLBlocation;
        LOG_DEBUG("location x:{}, y{}",lbLocation.translation.x,lbLocation.translation.y);

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

    if(Util::Input::IsMouseMoving() && LBPressing==true){
        glm::vec2 nowLBLocation=Util::Input::GetCursorPosition();
        LOG_DEBUG("drawned size x:{}, y{}", nowLBLocation.x-ogLBlocation.x,nowLBLocation.y-ogLBlocation.y);
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

    m_Barracks->Update();
    m_Giraffe->Update();
    m_Capybara->Update(lbLocation);
    m_Triangle.Update();
    m_Structure->Update();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    // put the stuff in here
    ImGui::Begin("Structure Selection Menu");
    ImGui::Text("$ {}",1000);
    ImGui::Text("02:31");
    ImGui::Text("{} L",50);
    if (ImGui::Button("Power Plants")){
        currentModde=buttonMode::A;
    }else if (ImGui::Button("Barracks")){
        currentModde=buttonMode::B;
        m_Structure->SetCurrentUpdateMode(Structure::updateMode::Moveable);
        }else if (ImGui::Button("Naval Yard")){
        currentModde=buttonMode::C;
        }else if (ImGui::Button("Ore Refinery")){
        currentModde=buttonMode::C;
        }else if (ImGui::Button("War Factory")){
        currentModde=buttonMode::C;
        }else if (ImGui::Button("Radar Dome")){
        currentModde=buttonMode::C;
        }else if (ImGui::Button("Service Depot")){
        currentModde=buttonMode::C;
        }else if (ImGui::Button("Advance Power")){
        currentModde=buttonMode::C;
        }else if (ImGui::Button("HeliPad")){
        currentModde=buttonMode::C;
        }else if (ImGui::Button("Tech Center")){
        currentModde=buttonMode::C;
        }

    ImGui::End();

    //and above
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //ImGui::ShowDemoWindow();

}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
