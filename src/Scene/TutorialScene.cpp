//
// Created by nudle on 2024/4/29.
//
#include "Scene/TutorialScene.hpp"

void TutorialScene::Start() {

    LOG_TRACE("Start");
    m_Map->Init(MapBinReader::readBin("../assets/map/ore-lord/map.bin", 64, 64),
                64, 64);
    m_GameObjectManager->Start(m_Map);
    m_EnemyObjectManager->Start(m_Map);
    m_GameObjectManager->setTotalCurrency(5000);
    m_EnemyObjectManager->setTotalCurrency(5000);
    m_UI->Start(m_Map, m_GameObjectManager);
    m_SceneCamera->Start(MapUtil::CellCoordToGlobal(glm::vec2(-10, -10)),
                         MapUtil::CellCoordToGlobal(glm::vec2(100, 100)));

    m_GameObjectManager->spawn(UnitType::INFANTRY, HouseType::MY, {5, 5});
    stageStart();
}
void TutorialScene::Update() {
    stageUpdate();
    if (m_stage == TutorialStages::STAGE_FINAL) {
        return;
    }
    m_GameObjectManager->Update();
    m_EnemyObjectManager->Update();
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
void TutorialScene::stageStart() {
    m_PlayerObjectivesText->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/Task/Task1.png"));
    m_PlayerObjectivesText->SetVisible(true);
    m_PlayerObjectivesText->setMovingRelativeToCamera(false);
    Util::Transform trans;
    trans.translation = {40, 5};
    trans.scale = {0.7, 0.7};
    m_PlayerObjectivesText->SetTransform(trans);

    m_cellProp->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/Task/Task_Cell.png"));
    m_cellProp->setHighLightImage("../assets/sprites/Task/Task_Cell_Text1.png");
    m_cellProp->setHighLightOffset({-100, 0});
    m_cellProp->Start({2, 2});
    m_cellProp->setObjectLocation({750, 750}, 0);
    m_stage = TutorialStages::STAGE1;
}
void TutorialScene::stageUpdate() {
    if (Util::Input::IsKeyDown(Util::Keycode::R)) {
        stageStart();
    }
    switch (m_stage) {
    case TutorialStages::STAGE1: {
        stage1Update();
        break;
    }
    case TutorialStages::STAGE2: {
        stage2Update();
        break;
    }
    case TutorialStages::STAGE3: {
        stage3Update();
        break;
    }
    case TutorialStages::STAGE4: {
        stage4Update();
        break;
    }
    case TutorialStages::STAGE_FINAL: {
        stageFinalUpdate();
        break;
    }
    }
}

void TutorialScene::stage1Update() {
    m_PlayerObjectivesText->Draw();
    m_cellProp->Update();
    for (auto i : m_GameObjectManager->getAvatarManager()->getAvatarArray()) {

        if ((i->getSelected() &&
             m_cellProp->ifOverlaps(i->getMoving()->getCurrentCell())) ||
            Util::Input::IsKeyDown(Util::Keycode::DEBUG_KEY)) {
            initStage2();
            break;
        }
    }
}

void TutorialScene::initStage2() {
    m_PlayerObjectivesText->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/Task/Task2.png"));

    m_cellProp->setHighLightImage("../assets/sprites/Task/Task_Cell_Text2.png");
    m_cellProp->setScale({6, 4});
    m_cellProp->setObjectLocation({600, 1000}, 0);
    m_cellProp->Start({12, 8});
    m_stage = TutorialStages::STAGE2;
};

void TutorialScene::stage2Update() {
    m_PlayerObjectivesText->Draw();
    m_cellProp->Update();
    int structCount = 0;
    for (auto i : (m_GameObjectManager->getStructureManager()
                       ->getStructureArray()
                       ->getBuiltStructureArray())) {
        if (i->getHouseType() == HouseType::MY) {
            structCount++;
        }
    }
    if (m_GameObjectManager->getStructureManager()
                ->getStructureArray()
                ->ifBarrackBuilt() &&
            m_GameObjectManager->getStructureManager()
                ->getStructureArray()
                ->ifPowerPlantBuilt() &&
            m_GameObjectManager->getStructureManager()
                ->getStructureArray()
                ->ifOreRefinaryBuilt() ||
        Util::Input::IsKeyDown(Util::Keycode::DEBUG_KEY)) {
        // change next stage's text&prop here
        initStage3();
    }
}

void TutorialScene::initStage3() {
    m_PlayerObjectivesText->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/Task/Task3.png"));

    m_cellProp->setHighLightImage("../assets/sprites/Task/Task_Cell_Text3.png");
    m_cellProp->setScale({1, 1});
    m_cellProp->setObjectLocation({850, 850}, 0);
    m_cellProp->Start({2, 2});
    m_stage = TutorialStages::STAGE3;
}

void TutorialScene::stage3Update() {
    m_PlayerObjectivesText->Draw();
    m_cellProp->Update();
    int avataroverlapscount = 0;
    for (auto i : m_GameObjectManager->getAvatarManager()->getAvatarArray()) {
        if (i->getHouseType() == HouseType::MY) {
            if (m_cellProp->ifOverlaps(i->getMoving()->getCurrentCell())) {
                avataroverlapscount++;
            }
        }
    }
    if (avataroverlapscount >= 4 ||
        Util::Input::IsKeyDown(Util::Keycode::DEBUG_KEY)) {
        // change next stage's text&prop here
        initStage4();
    }
}
void TutorialScene::initStage4() {
    m_PlayerObjectivesText->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/Task/Task4.png"));

    m_cellProp->setHighLightImage("../assets/sprites/Task/Task_Cell_Text4.png");
    m_cellProp->setScale({4, 3});
    m_cellProp->setObjectLocation({1200, 850}, 0);
    m_cellProp->Start({8, 6});
    m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY, {24, 17});
    m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY, {26, 18});
    m_EnemyObjectManager->spawn(UnitType::INFANTRY, HouseType::ENEMY, {25, 17});
    m_stage = TutorialStages::STAGE4;
}

void TutorialScene::stage4Update() {
    m_PlayerObjectivesText->Draw();
    m_cellProp->Update();
    if (m_EnemyObjectManager->getAvatarManager()->getAvatarArray().size() ==
            0 ||
        Util::Input::IsKeyDown(Util::Keycode::DEBUG_KEY)) {
        initFinalStage();
    }
}

void TutorialScene::initFinalStage() {
    m_stage = TutorialStages::STAGE_FINAL;
}

void TutorialScene::stageFinalUpdate() {
    m_MUI->Update();
}
