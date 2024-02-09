#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

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

    buttonTest->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/Airfield.png"));
    buttonTest->Start();


    m_Barracks->AppendChild(gf);
    m_CurrentState = State::UPDATE;


}
glm::vec2 ogLBlocation=glm::vec2(0,0);
bool LBPressing=false;
Util::Transform lbLocation;
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
    buttonTest->Update();


}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
