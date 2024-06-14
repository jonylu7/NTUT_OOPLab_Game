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
#include "UI/MenuUI.hpp"

class MenuScene : public Scene {
public:
    enum class SceneMode { DEFAULT, MAP, MENU, TUTORIAL, SANDBOX, SKIRMISH };

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
        if (m_CurrentMode == SceneMode::MENU) {
            if (Util::Input::IsKeyPressed(Util::Keycode::P)) {
                m_BGM.Play();
            }
            if (Util::Input::IsKeyPressed(Util::Keycode::K)) {
                m_BGM.LoadMedia("../assets/BGM/Jimmy_Scott-Sycamore_Trees.mp3");
                m_BGM.Play();
            }
            if (Util::Input::IsKeyPressed(Util::Keycode::M)) {
                m_CurrentMode = SceneMode::MAP;
            }
            if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
                m_CurrentMode = SceneMode::DEFAULT;
            }
            if (Util::Input::IsKeyPressed(Util::Keycode::T) ||
                m_MenuUI.getUIStatus()->getUIStatusType() ==
                    UIStatusType::UI_START) {
                m_MenuUI.getUIStatus()->setUIStatusType(
                    UIStatusType::UI_DEFAULT);
                m_CurrentMode = SceneMode::TUTORIAL;
            }
            if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
                m_CurrentMode = SceneMode::SANDBOX;
            }
            if (m_TutorialScene->getMissionAccomplishedUI()
                    ->getUIStatus()
                    ->getUIStatusType() == UIStatusType::UI_CONTINUE) {
                m_CurrentMode = SceneMode::SKIRMISH;
            }
        }
        if (m_CurrentMode==SceneMode::TUTORIAL&&m_TutorialScene->getMissionAccomplishedUI()
                ->getUIStatus()
                ->getUIStatusType() == UIStatusType::UI_CONTINUE) {
            m_CurrentMode = SceneMode::SKIRMISH;
            m_MenuUI.getUIStatus()->setUIStatusType(
                UIStatusType::UI_DEFAULT);
            m_SandBoxScene->setStage(true);
        }

        switch (m_CurrentMode) {
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
        case (SceneMode::MENU):
            m_MenuUI.Update();
            break;
        case (SceneMode::SKIRMISH):
            // skirmish update()
            m_SandBoxScene->Update();
            break;
        }
    }

    SceneMode getSceneMode() { return m_CurrentMode; }

    bool ifExit() {
        if (m_MenuUI.getUIStatus()->getUIStatusType() ==
                UIStatusType::UI_EXIT ||
            m_TutorialScene->getMissionAccomplishedUI()
                    ->getUIStatus()
                    ->getUIStatusType() == UIStatusType::UI_EXIT) {
            return true;
        }
        return false;
    }

private:
    SceneMode m_CurrentMode = SceneMode::MENU;
    std::shared_ptr<TutorialScene> m_TutorialScene =
        std::make_shared<TutorialScene>();
    std::shared_ptr<MapScene> m_MapScene = std::make_shared<MapScene>();
    std::shared_ptr<DefaultScene> m_DefaultScene =
        std::make_shared<DefaultScene>();
    std::shared_ptr<SandBoxScene> m_SandBoxScene =
        std::make_shared<SandBoxScene>();
    Util::BGM m_BGM;

    MenuUI m_MenuUI;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MENUSCENE_HPP
