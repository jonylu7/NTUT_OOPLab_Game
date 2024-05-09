//
// Created by nudle on 2024/4/28.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
#include "Cursor.hpp"
#include "Enemy/EnemyScripts.hpp"
#include "Scene.hpp"
// #include "Mechanics/GameObjectID.hpp"
#include "Task.hpp"
#include "Util/Prop.hpp"
#include <glm/glm.hpp>

#define DEBUG_KEY P

enum class Stages{STAGE1,STAGE2,STAGE3,STAGE4};
class TutorialScene : public Scene{
public:
    TutorialScene(){};
    ~TutorialScene(){};
    void Start()override;
    void Update()override;
    void stageStart();
    void stageUpdate();
private:
    SpriteSheet m_SpriteSheet;
    std::shared_ptr<CursorClass> m_Cursor = std::make_shared<CursorClass>();
    Grid testGrid;
    std::shared_ptr<EnemyPlayer> m_Enemy = std::make_shared<EnemyPlayer>(SceneMode::TUTORIAL);
    std::shared_ptr<EnemyScripts> m_EnemyScripts = std::make_shared<EnemyScripts>();
    std::shared_ptr<Task> m_Text = std::make_shared<Task>();
    std::shared_ptr<Prop> m_cellProp = std::make_shared<Prop>();
    Stages m_stage = Stages::STAGE1;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
