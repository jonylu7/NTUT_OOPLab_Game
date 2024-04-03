//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP

#include "Scene.hpp"
#include "Unit/Avatar.hpp"
#include "Unit/Hunter.hpp"
#include "Unit/Runner.hpp"
class DefaultScene : public Scene {

public:
    DefaultScene(){};
    ~DefaultScene(){};

    void Start() override;
    void Update() override;

private:
    SpriteSheet m_SpriteSheet;
    DrawOverlays m_testdraw;
    Grid testGrid;

    Avatar m_dummy;
    std::shared_ptr<Hunter> m_hunter = std::make_shared<Hunter>();
    std::shared_ptr<Runner> m_runner = std::make_shared<Runner>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
