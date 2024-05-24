//
// Created by nudle on 2024/4/28.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
#include "AI/EnemyScripts.hpp"
#include "Cursor.hpp"
#include "Scene.hpp"
// #include "Mechanics/GameObjectID.hpp"
#include "Util/Prop.hpp"
#include "pch.hpp"

#define DEBUG_KEY P


enum class TutorialStages { STAGE1, STAGE2, STAGE3, STAGE4 };

class TutorialScene : public Scene {
    enum class Stages { STAGE1, STAGE2, STAGE3, STAGE4 };
public:
    TutorialScene(){};
    ~TutorialScene(){};
    void Start() override;
    void Update() override;

private:
    void stageStart();
    void stageUpdate();
    void stage1Update();
    void stage2Update();
    void stage3Update();
    void stage4Update();

private:
    SpriteSheet m_SpriteSheet;
    std::shared_ptr<CursorClass> m_Cursor = std::make_shared<CursorClass>();
    Grid testGrid;
    std::shared_ptr<EnemyPlayer> m_Enemy =
        std::make_shared<EnemyPlayer>(SceneMode::TUTORIAL);
    std::shared_ptr<EnemyScripts> m_EnemyScripts =
        std::make_shared<EnemyScripts>();
    std::shared_ptr<Util::GameObject> m_PlayerObjectivesText =
        std::make_shared<Util::GameObject>();
    std::shared_ptr<Prop> m_cellProp = std::make_shared<Prop>();
    TutorialStages m_stage;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
