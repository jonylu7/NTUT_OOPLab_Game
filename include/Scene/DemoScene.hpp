//
// Created by 盧威任 on 4/26/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DEMOSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DEMOSCENE_HPP
#include "Scene.hpp"
class DemoScene : public Scene {

public:
    DemoScene(){};
    ~DemoScene(){};

    void Start() override;
    void Update() override;

private:
    SpriteSheet m_SpriteSheet;
    std::shared_ptr<CursorClass> m_Cursor = std::make_shared<CursorClass>();
    Grid testGrid;

    Avatar m_dummy;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DEMOSCENE_HPP
