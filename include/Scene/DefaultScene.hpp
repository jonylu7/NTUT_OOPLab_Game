//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
#include "Avatar/Avatar.hpp"
#include "Cursor.hpp"
#include "Scene.hpp"
#include <glm/glm.hpp>

class DefaultScene : public Scene {

public:
    DefaultScene(){};
    ~DefaultScene(){};

    void Start() override;
    void Update() override;

private:
    SpriteSheet m_SpriteSheet;
    std::shared_ptr<CursorClass> m_Cursor = std::make_shared<CursorClass>();
    Grid testGrid;

    Avatar m_dummy;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
