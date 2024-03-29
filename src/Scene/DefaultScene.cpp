//
// Created by 盧威任 on 2/15/24.
//
#include "Scene/DefaultScene.hpp"
#include "DrawOverlays.hpp"
#include <iostream>
void DefaultScene::Start() {
    // image.SetImage("../assets/sprites/Shapes/B_Box.png");
    LOG_TRACE("Start");

    /* doing some weird stuff, fix is needed
    std::vector<std::shared_ptr<TileClass>> maps =
        m_Map.readMapAndTileSet(m_OgMap, m_tileSets);
        */

    m_Map->Init(255, 255);
    // m_Map->getTileByCellPosition(glm::vec2(5, 5))->setWalkable(0);
    m_Map->getTileByCellPosition(glm::vec2(6, 5))->setWalkable(0);
    m_Map->getTileByCellPosition(glm::vec2(7, 5))->setWalkable(0);
    m_Map->getTileByCellPosition(glm::vec2(8, 5))->setWalkable(0);
    m_Map->getTileByCellPosition(glm::vec2(9, 5))->setWalkable(0);
    m_UI.Start();
    m_testdraw.Start(std::vector({glm::vec2(0.F, 0.F)}),
                     DrawOverlays::OverlayShapes::R_CROSS);
    // m_GameObjectManager.Start();

    //m_dummy.Start({5, 5}, m_Map);
    m_UI.importMap(m_Map);
    m_UI.importPlayer(m_Player);

    m_Player->setTotalCurrency(50000);
}

void DefaultScene::Update() {
    //m_dummy.Update();

    m_Manager.Update();

    Util::Transform trans;
    m_Map->Draw(trans, 0);
    m_SceneCamera.Update();
    m_Renderer.Update();
    m_UI.Update();

    Util::Transform trans2;
    trans2.translation = Structure::ChangeToCell(
        MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));

    auto tile = m_Map->getTileByCellPosition(MapUtil::GlobalCoordToCellCoord(
        MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition())));

    if (tile->getWalkable()) {
        m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::B_BOXES);
    } else {
        m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::R_CROSS);
    }

    m_testdraw.DrawUsingCamera(trans2, 1);
    //  m_GameObjectManager.Update();

    if (m_UI.getIfAnyBuildingReadyToBuild()) {
        m_Manager.Append(m_UI.getSelectedBuilding());
    }
    m_UI.checkExistBuilding(m_Manager.getStructureArray());
    if(m_UI.getIfUnitReadyToSpawn()){
        m_Manager.unitAppend(m_UI.getUnitFromUI());
    }
}
