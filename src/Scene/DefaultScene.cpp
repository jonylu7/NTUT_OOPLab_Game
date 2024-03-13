//
// Created by 盧威任 on 2/15/24.
//
#include "Scene/DefaultScene.hpp"
#include "DrawOverlays.hpp"
#include <iostream>
void DefaultScene::Start() {

    LOG_TRACE("Start");
    /*
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
    */
    // init map
    m_TileSetSpriteSheet->Start("../assets/sprites/TILESET_Field.png", 24, 24,
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

    m_Map.Init(std::vector<std::vector<std::shared_ptr<TileClass>>>(), 255,
               255);
    m_UI.Start();
    m_testdraw.Start({0, 0}, DrawOverlays::OverlayShapes::BOXES);
    // m_GameObjectManager.Start();
}

void DefaultScene::Update() {
    Util::Transform trans;
    m_Map.Draw(trans, 0);
    m_SceneCamera.Update();
    m_Renderer.Update();
    m_UI.Update();
    Util::Transform trans2;
    trans2.translation = Structure::ChangeToCell(
        MapClass::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));
    m_testdraw.DrawUsingCamera(trans2, 1);
    // m_GameObjectManager.Update();
}
