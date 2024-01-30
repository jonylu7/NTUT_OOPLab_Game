#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"


void App::Start() {
    LOG_TRACE("Start");

    m_Giraffe->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
    m_Giraffe->SetZIndex(5);
    m_Giraffe->Start();

    auto gf = std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 500,
                                            "Giraffe");
    gf->SetZIndex(m_Giraffe->GetZIndex() - 1);
    gf->Start();
    m_Giraffe->AppendChild(gf);

    m_Capybara->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
    m_Capybara->Start();

    m_Barracks->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/Barracks.gif"));
    m_Barracks->Start();

    m_CurrentState = State::UPDATE;

}
glm::vec2 ogLBlocation=glm::vec2(0,0);
bool LBPressing=false;
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
    }

    if(Util::Input::IsMouseMoving() && LBPressing==true){
        glm::vec2 nowLBLocation=Util::Input::GetCursorPosition();
        LOG_DEBUG("drawned size x:{}, y{}", nowLBLocation.x-ogLBlocation.x,nowLBLocation.y-ogLBlocation.y);
    }


    if(Util::Input::IsRButtonPressed()){
        LOG_DEBUG("RPressed");
        m_Barracks->Update();
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

    //m_Giraffe->Update();
    m_Barracks->Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
