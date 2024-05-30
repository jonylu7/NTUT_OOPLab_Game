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
    m_GameObjectManager->Start(m_Map);
    m_EnemyObjectManager->Start(m_Map);
    m_UI->Start(m_Map, m_GameObjectManager);
    m_GameObjectManager->setTotalCurrency(5000);
    m_EnemyObjectManager->setTotalCurrency(5000);
    m_SceneCamera->Start(MapUtil::CellCoordToGlobal(glm::vec2(-10, -10)),
                         MapUtil::CellCoordToGlobal(glm::vec2(100, 100)));
}
void SandBoxScene::Update() {
    m_GameObjectManager->Update();
    m_EnemyObjectManager->Update();
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
        m_GameObjectManager->getStructureManager()->AddStructSelectingBuiltSite(
            m_UI->getSelectedBuilding());
    }
    m_UI->checkExistBuilding(m_GameObjectManager->getStructureManager()
                                 ->getStructureArray()
                                 ->getBuiltStructureArray());
    if (m_UI->ifUnitReadyToSpawn()) {
        m_GameObjectManager->spawnToWayPoint(
            m_UI->getUnitTypeReadyToBeSpawned(), HouseType::MY);
    }
}
void SandBoxScene::stageStart() {
    switch (m_stage) {
    case Stages::STAGE1: {
        m_GameObjectManager->spawn(UnitType::INFANTRY, HouseType::MY, {5, 5});
        m_GameObjectManager->spawn(UnitType::INFANTRY, HouseType::MY, {5, 6});
        m_GameObjectManager->spawn(UnitType::INFANTRY, HouseType::MY, {5, 7});
        m_GameObjectManager->spawn(UnitType::INFANTRY, HouseType::MY, {5, 8});
        m_GameObjectManager->spawn(UnitType::INFANTRY, HouseType::MY, {5, 9});
        m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY,
                                    {10, 5});
        m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY,
                                    {10, 6});
        m_stage = Stages::END;
        break;
    }
    case Stages::STAGE2: {
        m_GameObjectManager->spawn(UnitType::INFANTRY, HouseType::MY, {5, 5});
        m_GameObjectManager->spawn(UnitType::INFANTRY, HouseType::MY, {5, 6});

        m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY,
                                    {10, 5});
        m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY,
                                    {10, 6});
        m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY,
                                    {10, 7});
        m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY,
                                    {10, 8});
        m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY,
                                    {10, 9});
        m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY,
                                    {10, 10});
        m_stage = Stages::END;
        break;
    }
    case Stages::STAGE3: {
        m_GameObjectManager->spawn(UnitType::INFANTRY, HouseType::MY, {5, 5});
        m_GameObjectManager->spawn(UnitType::INFANTRY, HouseType::MY, {5, 6});

        m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY,
                                    {10, 5});
        m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY,
                                    {10, 6});
        m_stage = Stages::END;
        break;
    }
    case Stages::STAGE4: {
        for (int i = 0; i < 50; i++) {
            m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY,
                                        {30 + i / 5, 5 + i % 5});
        }
        m_stage = Stages::END;
        break;
    }
    }
}
void SandBoxScene::stageUpdate() {
    if (m_stage == Stages::START) {
        if (Util::Input::IsKeyPressed(Util::Keycode::NUM_1)) {
            m_stage = Stages::STAGE1;
            m_EnemyScripts->Start(m_GameObjectManager, m_EnemyObjectManager,
                                  m_Map);
            stageStart();
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::NUM_2)) {
            m_stage = Stages::STAGE2;
            m_EnemyScripts->Start(m_GameObjectManager, m_EnemyObjectManager,
                                  m_Map);
            stageStart();
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::NUM_3)) {
            m_stage = Stages::STAGE3;
            m_EnemyScripts->Start(m_GameObjectManager, m_EnemyObjectManager,
                                  m_Map);
            stageStart();
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::NUM_4)) {
            m_stage = Stages::STAGE4;
            m_EnemyScripts->Start(m_GameObjectManager, m_EnemyObjectManager,
                                  m_Map, false);
            stageStart();
        }
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::DEBUG_KEY)) {
        m_Enemy->addTotalCurrency(500);
    }
}