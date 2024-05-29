//
// Created by 盧威任 on 4/1/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MENUSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MENUSCENE_HPP
#include "SandBoxScene.hpp"
#include "Scene/DefaultScene.hpp"
#include "Scene/MapScene.hpp"
#include "Scene/Scene.hpp"
#include "TutorialScene.hpp"

class MenuScene : public Scene {
    enum class SceneMode { DEFAULT, MAP, MENU, TUTORIAL, SANDBOX };

public:
    MenuScene()
        : m_BGM("../assets/BGM/RA3-Soviet_March.mp3") {}
    ~MenuScene() {}

    void Start() override {
        m_MapScene->Start();
        m_DefaultScene->Start();
        m_TutorialScene->Start();
        m_SandBoxScene->Start();
    }

    void Update() override {

        if (m_currentMode == SceneMode::MENU) {
            if (Util::Input::IsKeyPressed(Util::Keycode::P)) {
                m_BGM.Play();
            }
            if (Util::Input::IsKeyPressed(Util::Keycode::K)) {
                m_BGM.LoadMedia("../assets/BGM/Jimmy_Scott-Sycamore_Trees.mp3");
                m_BGM.Play();
            }
            if (Util::Input::IsKeyPressed(Util::Keycode::M)) {
                m_currentMode = SceneMode::MAP;
            }
            if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
                m_currentMode = SceneMode::DEFAULT;
            }
            if (Util::Input::IsKeyPressed(Util::Keycode::T)) {
                m_currentMode = SceneMode::TUTORIAL;
            }
            if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
                m_currentMode = SceneMode::SANDBOX;
            }
        }

        switch (m_currentMode) {
        case (SceneMode::MAP):
            m_MapScene->Update();
            break;
        case (SceneMode::DEFAULT):
            m_DefaultScene->Update();
            break;
        case (SceneMode::TUTORIAL):
            m_TutorialScene->Update();
            break;
        case (SceneMode::SANDBOX):
            m_SandBoxScene->Update();
            break;
        }
    }

private:
    SceneMode m_currentMode = SceneMode::MENU;
    std::shared_ptr<TutorialScene> m_TutorialScene =
        std::make_shared<TutorialScene>();
    std::shared_ptr<MapScene> m_MapScene = std::make_shared<MapScene>();
    std::shared_ptr<DefaultScene> m_DefaultScene =
        std::make_shared<DefaultScene>();
    std::shared_ptr<SandBoxScene> m_SandBoxScene =
        std::make_shared<SandBoxScene>();
    Util::BGM m_BGM;
    std::shared_ptr<Util::Image> m_ButtonSinglePlayer =
        std::make_shared<Util::Image>(
            "../assets/Button/Button_SinglePlayer.png");
    std::shared_ptr<Util::Image> m_ButtonSetting =
        std::make_shared<Util::Image>("../assets/Button/Button_Setting.png");
    std::shared_ptr<Util::Image> m_ButtonExit =
        std::make_shared<Util::Image>("../assets/Button/Button_Exit.png");

    std::shared_ptr<Util::Image> m_ButtonExtra =
        std::make_shared<Util::Image>("../assets/Button/Button_Extras.png");
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MENUSCENE_HPP
