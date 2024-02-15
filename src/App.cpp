#include "App.hpp"
#include "Util/Logger.hpp"


void App::Start() {
    testScene.Start();
    m_CurrentState=App::State::UPDATE;
}

void App::Update() {

testScene.Update();
testScene.imgui();
m_CurrentState=App::State::UPDATE;
}

void App::End() { // NOLINT(this method will mutate members in the future)

    LOG_TRACE("End");
}
