//
// Created by nudle on 2024/4/28.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
#include "Cursor.hpp"
#include "Enemy/EnemyScripts.hpp"
#include "Scene.hpp"
// #include "Mechanics/GameObjectID.hpp"
#include <glm/glm.hpp>

class TutorialScene : public Scene{
public:
    TutorialScene(){};
    ~TutorialScene(){};
    void Start()override;
    void Update()override;
private:
    SpriteSheet m_SpriteSheet;
    std::shared_ptr<CursorClass> m_Cursor = std::make_shared<CursorClass>();
    Grid testGrid;
    std::shared_ptr<EnemyPlayer> m_Enemy = std::make_shared<EnemyPlayer>(SceneMode::TUTORIAL);
    std::shared_ptr<EnemyScripts> m_EnemyScripts = std::make_shared<EnemyScripts>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TUTORIALSCENE_HPP
