//
// Created by nudle on 2024/4/28.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
#include "AI/AIGeneral.hpp"
#include "Cursor.hpp"
#include "Scene.hpp"
#include "UI/MissionAccomplishedUI.hpp"
#include "Util/Prop.hpp"
#include "pch.hpp"

#define DEBUG_KEY P

enum class TutorialStages { STAGE1, STAGE2, STAGE3, STAGE4, STAGE_FINAL };

class TutorialScene : public Scene {

public:
    TutorialScene(){};
    ~TutorialScene(){};
    void Start() override;
    void Update() override;

    std::shared_ptr<MissionAccomplishedUI> getMissionAccomplishedUI() {
        return m_MUI;
    }

private:
    void stageStart();
    void stageUpdate();
    // update stage
    void stage1Update();
    void stage2Update();
    void stage3Update();
    void stage4Update();
    void stageFinalUpdate();
    // init stage
    void initStage2();
    void initStage3();
    void initStage4();
    void initFinalStage();

private:
    SpriteSheet m_SpriteSheet;
    std::shared_ptr<CursorClass> m_Cursor = std::make_shared<CursorClass>();
    Grid testGrid;
    std::shared_ptr<AIGeneral> m_EnemyScripts = std::make_shared<AIGeneral>();
    std::shared_ptr<Util::GameObject> m_PlayerObjectivesText =
        std::make_shared<Util::GameObject>();
    std::shared_ptr<Prop> m_cellProp = std::make_shared<Prop>();
    TutorialStages m_stage;

    std::shared_ptr<MissionAccomplishedUI> m_MUI =
        std::make_shared<MissionAccomplishedUI>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
