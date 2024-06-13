//
// Created by 盧威任 on 2/15/24.
//
#include "Scene/DefaultScene.hpp"
#include "Display/DrawOverlays.hpp"
#include <iostream>

void DefaultScene::Start() {

    LOG_TRACE("Start");
    // create map
    m_Map->Init(60, 60);

    /*
    m_Map->getTileByCellPosition(glm::vec2(6, 5))->setWalkable(0);
    m_Map->getTileByCellPosition(glm::vec2(7, 5))->setWalkable(0);
    m_Map->getTileByCellPosition(glm::vec2(8, 5))->setWalkable(0);
    m_Map->getTileByCellPosition(glm::vec2(9, 5))->setWalkable(0);
     */

    // start
    m_Player->Start(m_Map);
    m_UI->Start(m_Map, m_Player);
    m_Player->setTotalCurrency(5000);
    m_SceneCamera->Start(MapUtil::CellCoordToGlobal(glm::vec2(-5, -5)),
                         MapUtil::CellCoordToGlobal(glm::vec2(70, 70)));
}

void DefaultScene::Update() {

    m_Player->Update();

    Util::Transform trans;
    m_Map->Draw(trans, 0);
    m_SceneCamera->Update();
    m_Renderer.Update();
    m_UI->Update();

    auto tileLocation = MapUtil::GlobalCoordToCellCoord(
        MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));
    if (tileLocation.x >= 0 && tileLocation.y >= 0) {
        m_Cursor->Update(m_Map->getTileByCellPosition(tileLocation));
    }

    // build and spawn stuff

    if (m_UI->getIfAnyBuildingReadyToBuild()) {
        m_Player->getUnitManager()
            ->getStructureManager()
            ->AddStructSelectingBuiltSite(m_UI->getSelectedBuilding());
    }
    m_UI->checkExistBuilding(m_Player->getUnitManager()
                                 ->getStructureManager()
                                 ->getStructureArray()
                                 ->getBuiltStructureArray());
    if (m_UI->ifUnitReadyToSpawn()) {
        m_Player->getUnitManager()->spawnToWayPoint(
            m_UI->getUnitTypeReadyToBeSpawned(), HouseType::MY);
    }
}
