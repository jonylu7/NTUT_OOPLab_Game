//
// Created by 盧威任 on 2/15/24.
//
#include "Scene/DefaultScene.hpp"
void DefaultScene::Start() {

    LOG_TRACE("Start");
    m_GameObjectList[0]->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/Raccoon3.jpg"));
    m_GameObjectList[0]->SetZIndex(10);

    m_GameObjectList[1]->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/capybara.png"));

    m_Structure->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/barracks.png"));
    m_Structure->SetZIndex(0);
    m_Structure->SetObjectLocation({0, 0});
    m_Structure->Start();
    m_Structure->SetCurrentUpdateMode(Structure::updateMode::Moveable);
    m_Renderer.AddChild(m_Structure);

    m_Inf->Start();

    for (auto i : m_GameObjectList) {
        i->Start();
    }

    m_Renderer.AddChild(m_Structure);

    // init map
    m_TileSetSpriteSheet->Start("../assets/sprites/TILESET_Field.png", 64, 64,
                                20, 0);

    m_OgMap = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    m_OgMap = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<std::shared_ptr<TileClass>> maps;
    for (unsigned int i = 0; i < 10; i++) {
        maps.push_back(std::make_shared<TileClass>("rock-" + std::to_string(i),
                                                   false, false, true, i));
    }
    /* doing some weird stuff, fix is needed
    std::vector<std::shared_ptr<TileClass>> maps =
        m_Map.readMapAndTileSet(m_OgMap, m_tileSets);
        */

    m_Map.Init(maps, m_TileSetSpriteSheet, 5, 2);
    m_UI.Start();
}

void DefaultScene::Update() {

    m_Map.Draw();

    m_Structure->SetCurrentUpdateMode(Structure::updateMode::Fixed);
    m_Structure->Update();

    if (Util::Input::IsKeyPressed(Util::Keycode::END)) {
        glm::vec2 ogLBlocation = Util::Input::GetCursorPosition();

        if (m_Structure->GetCurrentUpdateMode() ==
            Structure::updateMode::Moveable) {
            m_Structure->SetObjectLocation(ogLBlocation);
            m_Structure->SetCurrentUpdateMode(Structure::updateMode::Fixed);
            LOG_DEBUG("Fixed");
        }
    }

    m_SceneCamera.Update();

    m_Inf->Update();
    rect.Update();
    m_Renderer.Update();

    for (auto i : m_GameObjectList) {
        i->Update();
    }
    m_UI.Update();
}
