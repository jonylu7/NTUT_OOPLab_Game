//
// Created by 盧威任 on 2/15/24.
//
#include "Scene/DefaultScene.hpp"
#include "Display/DrawOverlays.hpp"
#include <iostream>

void DefaultScene::Start() {

    LOG_TRACE("Start");
    m_Map->Init(98, 98);
    // m_Map->Init(
    //    MapBinReader::readBin("../assets/map/green-belt/map.bin", 98, 98), 98,
    //   98);
    // m_Map->getTileByCellPosition(glm::vec2(5, 5))->setWalkable(0);
    m_Map->getTileByCellPosition(glm::vec2(6, 5))->setWalkable(0);
    m_Map->getTileByCellPosition(glm::vec2(7, 5))->setWalkable(0);
    m_Map->getTileByCellPosition(glm::vec2(8, 5))->setWalkable(0);
    m_Map->getTileByCellPosition(glm::vec2(9, 5))->setWalkable(0);

    // m_GameObjectManager.Start();

    // m_dummy.Start({5, 5}, m_Map);
    m_GameObjectManager->Start(m_Map);
    // m_Cursor.Start(m_Map);
    m_UI.Start(m_Map, m_GameObjectManager);
    m_GameObjectManager->setTotalCurrency(5000);
    m_SceneCamera.Start(MapUtil::CellCoordToGlobal(glm::vec2(-10, -10)),
                        MapUtil::CellCoordToGlobal(glm::vec2(100, 100)));

    //    m_hunter->setCurrentCell({20,10});
    //    m_runner->setCurrentCell({10,10});

    //    m_hunter->Start({20, 9});
    //    m_runner->Start({9, 10});
    //    m_hunter->setTarget(m_runner);
    //    m_runner->setBeingChase(m_hunter);
}

void DefaultScene::Update() {
    //    m_hunter->Update();
    //    m_runner->Update();

    m_GameObjectManager->Update();

    Util::Transform trans;
    m_Map->Draw(trans, 0);
    m_SceneCamera.Update();
    m_Renderer.Update();
    m_UI.Update();

    m_Cursor->Update(
        m_Map->getTileByCellPosition(MapUtil::GlobalCoordToCellCoord(
            MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()))));

    auto tile = m_Map->getTileByCellPosition(MapUtil::GlobalCoordToCellCoord(
        MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition())));

    //  m_GameObjectManager.Update();

    if (m_UI.getIfAnyBuildingReadyToBuild()) {
        m_GameObjectManager->getStrucutreManager().AddStructSelectingBuiltSite(
            m_UI.getSelectedBuilding());
    }
    m_UI.checkExistBuilding(m_GameObjectManager->getStrucutreManager()
                                .getStructureArray()
                                .getBuiltStructureArray());
    if (m_UI.getIfUnitReadyToSpawn()) {
        m_GameObjectManager->getAvatarManager().AppendAvatar(
            m_UI.getUnitFromUI());
    }
}
