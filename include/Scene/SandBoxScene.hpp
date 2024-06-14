//
// Created by nudle on 2024/4/28.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SANDBOXSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SANDBOXSCENE_HPP
#include "AI/AIScripts.hpp"
#include "Cursor.hpp"
#include "Scene.hpp"
#include "Util/Prop.hpp"
#include <glm/glm.hpp>

#define DEBUG_KEY P

class SandBoxScene : public Scene {
    enum class Stages { STAGE1, STAGE2, STAGE3, STAGE4, START, END ,FORMAL_START ,FORMAL_UPDATE ,PLAYER_WON ,AI_WON};

public:
    SandBoxScene(){};
    ~SandBoxScene(){};
    void Start() override;
    void Update() override;
    void stageStart();
    void stageUpdate();
    void setStage(bool stage){
        if(stage){
            m_stage = Stages::FORMAL_START;
        }
    }
private:
    SpriteSheet m_SpriteSheet;
    std::shared_ptr<CursorClass> m_Cursor = std::make_shared<CursorClass>();
    Grid testGrid;
    std::shared_ptr<AIScript> m_EnemyScripts = std::make_shared<AIScript>();
    std::shared_ptr<UnitManager> m_GameObjectManager =
        std::make_shared<UnitManager>();
    std::shared_ptr<UnitManager> m_EnemyObjectManager =
        std::make_shared<UnitManager>();
    Stages m_stage = Stages::START;
    std::shared_ptr<Util::GameObject> m_Text =
        std::make_shared<Util::GameObject>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SANDBOXSCENE_HPP
