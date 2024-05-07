//
// Created by nudle on 2024/4/29.
//
#include "Scene/TutorialScene.hpp"

void TutorialScene::Start() {
    LOG_TRACE("Start");
    m_Map->Init(100, 100);
    m_GameObjectManager->Start(m_Map);
    m_UI.Start(m_Map, m_GameObjectManager);
    m_Player->setTotalCurrency(5000);
    m_Enemy->setTotalCurrency(5000);
    m_SceneCamera.Start(MapUtil::CellCoordToGlobal(glm::vec2(-10, -10)),
                        MapUtil::CellCoordToGlobal(glm::vec2(100, 100)));
    m_GameObjectManager->importEnemy(m_Enemy);
    m_EnemyScripts->Start(m_Enemy, m_GameObjectManager, m_Map);
    m_GameObjectManager->spawn(m_Map, UnitType::BARRACKS, HouseType::ENEMY,
                               {10, 10});
    m_GameObjectManager->spawn(m_Map, UnitType::POWER_PLANT, HouseType::ENEMY,
                               {15, 15});
    m_GameObjectManager->spawn(m_Map, UnitType::ORE_REF, HouseType::ENEMY,
                               {15, 10});
    //    m_GameObjectManager->spawn(m_Map, UnitType::INFANTRY, HouseType::MY,
    //                               {5, 5});
}
void TutorialScene::Update() {
    m_GameObjectManager->Update();
    m_EnemyScripts->Update();

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
