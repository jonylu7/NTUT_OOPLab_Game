//
// Created by nudle on 2024/4/29.
//
#include "Scene/SandBoxScene.hpp"

void SandBoxScene::Start() {

    LOG_TRACE("Start");
    // m_Map->Init(MapBinReader::readBin("../assets/map/ore-lord/map.bin", 64,
    // 64),
    //             64, 64);
    m_Map->Init(
        MapBinReader::readBin("../assets/map/green-belt/map.bin", 98, 98), 98,
        98);
    m_Player->Start(m_Map);
    m_AIPlayer->Start(m_Map);
    m_UI->Start(m_Map, m_Player);
    m_Player->setTotalCurrency(5000);
    m_AIPlayer->setTotalCurrency(5000);
    m_SceneCamera->Start(MapUtil::CellCoordToGlobal(glm::vec2(-10, -10)),
                         MapUtil::CellCoordToGlobal(glm::vec2(100, 100)));
}
void SandBoxScene::Update() {
    m_Player->Update();
    m_AIPlayer->Update();
    if (m_stage != Stages::START) {
        m_EnemyScripts->Update();
    }
    stageUpdate();
    Util::Transform trans;
    m_Map->Draw(trans, 0);
    m_SceneCamera->Update();
    m_Renderer.Update();
    m_UI->Update();

    // temperarory place here
    auto tileLocation = MapUtil::GlobalCoordToCellCoord(
        MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));
    if (tileLocation.x >= 0 && tileLocation.y >= 0) {
        m_Cursor->Update(m_Map->getTileByCellPosition(tileLocation));
    }

    auto tile = m_Map->getTileByCellPosition(MapUtil::GlobalCoordToCellCoord(
        MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition())));

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
void SandBoxScene::stageStart() {
    switch (m_stage) {
    case Stages::STAGE1: {
        m_Player->getUnitManager()->spawn(UnitType::INFANTRY, HouseType::MY,
                                          {5, 5});
        m_Player->getUnitManager()->spawn(UnitType::INFANTRY, HouseType::MY,
                                          {5, 6});
        m_Player->getUnitManager()->spawn(UnitType::INFANTRY, HouseType::MY,
                                          {5, 7});
        m_Player->getUnitManager()->spawn(UnitType::INFANTRY, HouseType::MY,
                                          {5, 8});
        m_Player->getUnitManager()->spawn(UnitType::INFANTRY, HouseType::MY,
                                          {5, 9});
        m_AIPlayer->getUnitManager()->spawn(UnitType::INFANTRY,
                                            HouseType::ENEMY, {10, 5});
        m_AIPlayer->getUnitManager()->spawn(UnitType::INFANTRY,
                                            HouseType::ENEMY, {10, 6});
        m_stage = Stages::END;
        break;
    }
    case Stages::STAGE2: {
        m_Player->getUnitManager()->spawn(UnitType::INFANTRY, HouseType::MY,
                                          {5, 5});
        m_Player->getUnitManager()->spawn(UnitType::INFANTRY, HouseType::MY,
                                          {5, 6});

        m_AIPlayer->getUnitManager()->spawn(UnitType::INFANTRY,
                                            HouseType::ENEMY, {10, 5});
        m_AIPlayer->getUnitManager()->spawn(UnitType::INFANTRY,
                                            HouseType::ENEMY, {10, 6});
        m_AIPlayer->getUnitManager()->spawn(UnitType::INFANTRY,
                                            HouseType::ENEMY, {10, 7});
        m_AIPlayer->getUnitManager()->spawn(UnitType::INFANTRY,
                                            HouseType::ENEMY, {10, 8});
        m_AIPlayer->getUnitManager()->spawn(UnitType::INFANTRY,
                                            HouseType::ENEMY, {10, 9});
        m_AIPlayer->getUnitManager()->spawn(UnitType::INFANTRY,
                                            HouseType::ENEMY, {10, 10});
        m_stage = Stages::END;
        break;
    }
    case Stages::STAGE3: {
        m_Player->getUnitManager()->spawn(UnitType::INFANTRY, HouseType::MY,
                                          {5, 5});
        m_Player->getUnitManager()->spawn(UnitType::INFANTRY, HouseType::MY,
                                          {5, 6});

        m_AIPlayer->getUnitManager()->spawn(UnitType::INFANTRY,
                                            HouseType::ENEMY, {10, 5});
        m_AIPlayer->getUnitManager()->spawn(UnitType::INFANTRY,
                                            HouseType::ENEMY, {10, 6});
        m_stage = Stages::END;
        break;
    }
    case Stages::STAGE4: {
        m_Player->getUnitManager()->spawn(UnitType::BARRACKS, HouseType::MY,
                                          {7, 5});
        m_Player->getUnitManager()->spawn(UnitType::INFANTRY, HouseType::MY,
                                          {7, 9});
        m_Player->getUnitManager()->spawn(UnitType::INFANTRY, HouseType::MY,
                                          {7, 8});
        m_stage = Stages::END;
        break;
    }
    }
}
void SandBoxScene::stageUpdate() {
    if (m_stage == Stages::START) {
        if (Util::Input::IsKeyPressed(Util::Keycode::NUM_1)) {
            m_stage = Stages::STAGE1;
            m_EnemyScripts->Start(m_Player->getUnitManager(),
                                  m_AIPlayer->getUnitManager(), m_Map);
            stageStart();
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::NUM_2)) {
            m_stage = Stages::STAGE2;
            m_EnemyScripts->Start(m_Player->getUnitManager(),
                                  m_AIPlayer->getUnitManager(), m_Map);
            stageStart();
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::NUM_3)) {
            m_stage = Stages::STAGE3;
            m_EnemyScripts->Start(m_Player->getUnitManager(),
                                  m_AIPlayer->getUnitManager(), m_Map);
            stageStart();
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::NUM_4)) {
            m_stage = Stages::STAGE4;
            m_EnemyScripts->Start(m_Player->getUnitManager(),
                                  m_AIPlayer->getUnitManager(), m_Map, true);
            stageStart();
        }
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::DEBUG_KEY)) {
        m_AIPlayer->addTotalCurrency(500);
    }
}
