//
// Created by 盧威任 on 2/15/24.
//
#include "Scene/DefaultScene.hpp"
#include "DrawOverlays.hpp"
#include <iostream>
void DefaultScene::Start() {
    // image.SetImage("../assets/sprites/Shapes/B_Box.png");
    OccupiedID::InitID();
    LOG_TRACE("Start");

    // init map
    m_TileSetSpriteSheet->Start("../assets/sprites/TILESET_Field.png", 24, 24,
                                20, 0);

    std::vector<std::shared_ptr<TileClass>> maps;
    for (unsigned int i = 0; i < 10; i++) {
        maps.push_back(std::make_shared<TileClass>("rock-" + std::to_string(i),
                                                   false, false, true, i));
    }
    /* doing some weird stuff, fix is needed
    std::vector<std::shared_ptr<TileClass>> maps =
        m_Map.readMapAndTileSet(m_OgMap, m_tileSets);
        */

    m_Map.Init(255, 255);
    m_UI.Start();
    m_testdraw.Start(std::vector({glm::vec2(0.F, 0.F)}),
                     DrawOverlays::OverlayShapes::R_CROSS);
    // m_GameObjectManager.Start();

    // m_dummy.Start();
    m_waypointUnit.setCurrentCell({glm::vec2(0, 0)});
    m_waypointUnit.setNextCell({glm::vec2(0, 0)});
    m_waypointUnit.findPath(15, 10);
}

void DefaultScene::Update() {
    // m_dummy.Update();

    m_waypointUnit.Update();

    for (auto i : m_BuiltStructure) {
        i->Update();
    }

    Util::Transform trans;
    m_Map.Draw(trans, 0);
    m_SceneCamera.Update();
    m_Renderer.Update();
    m_UI.Update();

    Util::Transform trans2;
    trans2.translation = Structure::ChangeToCell(
        MapClass::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));

    auto tile = m_Map.getTileByCellPosition(MapClass::GlobalCoordToCellCoord(
        MapClass::ScreenToGlobalCoord(Util::Input::GetCursorPosition())));

    if (tile->getClickable()) {
        m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::B_BOXES);
    } else {
        m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::R_CROSS);
    }

    m_testdraw.DrawUsingCamera(trans2, 1);
    //  m_GameObjectManager.Update();

    if (m_UI.getIfAnythingCanSelectToBuild()) {
        m_BuiltStructure.push_back(m_UI.getSelectedBuilding());
        m_BuiltStructure.back()->Start();
        printf("(Scene) Structure Started\n");
    }
}
