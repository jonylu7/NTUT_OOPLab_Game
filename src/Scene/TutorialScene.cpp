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
    m_SceneCamera->Start(MapUtil::CellCoordToGlobal(glm::vec2(-10, -10)),
                        MapUtil::CellCoordToGlobal(glm::vec2(100, 100)));
    m_GameObjectManager->importEnemy(m_Enemy);
    m_EnemyScripts->Start(m_Enemy, m_GameObjectManager, m_Map);


    m_GameObjectManager->spawn(m_Map, UnitType::BARRACKS, HouseType::ENEMY,
                               {20, 20});
    m_GameObjectManager->spawn(m_Map, UnitType::POWER_PLANT, HouseType::ENEMY,
                               {25, 25});
    m_GameObjectManager->spawn(m_Map, UnitType::ORE_REF, HouseType::ENEMY,
                               {25, 20});
    m_GameObjectManager->spawn(m_Map, UnitType::INFANTRY, HouseType::MY,
                                   {5, 5});
    stageStart();
}
void TutorialScene::Update() {
    m_GameObjectManager->Update();

    stageUpdate();
    Util::Transform trans;
    m_Map->Draw(trans, 0);
    m_SceneCamera->Update();
    m_Renderer.Update();
    m_UI.Update();

    m_Cursor->Update(
        m_Map->getTileByCellPosition(MapUtil::GlobalCoordToCellCoord(
            MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()))));

    auto tile = m_Map->getTileByCellPosition(MapUtil::GlobalCoordToCellCoord(
        MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition())));

    if (m_UI.getIfAnyBuildingReadyToBuild()) {
        m_GameObjectManager->getStructureManager()->AddStructSelectingBuiltSite(
            m_UI.getSelectedBuilding());
    }
    m_UI.checkExistBuilding(*m_GameObjectManager->getStructureManager()
                                 ->getStructureArray()
                                 ->getBuiltStructureArray());
    if (m_UI.getIfUnitReadyToSpawn()) {
        m_GameObjectManager->getAvatarManager()->AppendAvatar(
            m_UI.getUnitFromUI());
    }
}
void TutorialScene::stageStart(){
    m_Text->importCamera(m_SceneCamera);
    m_Text->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/Task/Task1.png"));
    m_Text->setObjectScale(0.6);
    m_Text->SetVisible(true);
    m_Text->setMovingRelativeToCamera(true);

    m_cellProp->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/Task/Task_Cell.png"));
    m_cellProp->setHighLightImage("../assets/sprites/Task/Task_Cell_Text1.png");
    m_cellProp->setHighLightOffset({-100,0});
    m_cellProp->Start({2,2});
    m_cellProp->setObjectLocation({750,750},0);
}
void TutorialScene::stageUpdate(){
    switch (m_stage) {
    case Stages::STAGE1:{
        m_Text->Draw();
        m_cellProp->Update();
        for(auto i:m_GameObjectManager->getAvatarManager()->getAvatarArray()){
            if(i->getHouseType()==HouseType::MY){
                if(m_cellProp->isOverlaps(i->getCurrentCell()) || Util::Input::IsKeyPressed(Util::Keycode::DEBUG_KEY)){
                    //change next stage's text&prop here
                    m_Text->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/Task/Task2.png"));

                    m_cellProp->setHighLightImage("../assets/sprites/Task/Task_Cell_Text2.png");
                    m_cellProp->setScale({6,4});
                    m_cellProp->setObjectLocation({600,1000},0);
                    m_cellProp->Start({12,8});
                    m_stage=Stages::STAGE2;
                }
            }
        }
        break;
    }
    case Stages::STAGE2:{
        m_Text->Draw();
        m_cellProp->Update();
        int structCount = 0;
        for(auto i:*(m_GameObjectManager->getStructureManager()->getStructureArray()->getBuiltStructureArray())){
            if(i->getHouseType()==HouseType::MY){
                structCount++;
            }
        }
        if(structCount>=3 || Util::Input::IsKeyPressed(Util::Keycode::DEBUG_KEY)){
            //change next stage's text&prop here
            m_Text->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/Task/Task3.png"));

            m_cellProp->setHighLightImage("../assets/sprites/Task/Task_Cell_Text3.png");
            m_cellProp->setScale({2,2});
            m_cellProp->setObjectLocation({850,850},0);
            m_cellProp->Start({4,4});
            m_stage=Stages::STAGE3;
        }
        break;
    }
    case Stages::STAGE3:{
        m_Text->Draw();
        m_cellProp->Update();
        int avatarCount = 0;
        for(auto i:m_GameObjectManager->getAvatarManager()->getAvatarArray()){
            if(i->getHouseType()==HouseType::MY){
                if(m_cellProp->isOverlaps(i->getCurrentCell())){
                    avatarCount++;
                }
            }
        }
        if(avatarCount>=4|| Util::Input::IsKeyPressed(Util::Keycode::DEBUG_KEY)){
            //change next stage's text&prop here
            m_Text->SetDrawable(std::make_unique<Util::Image>("../assets/sprites/Task/Task4.png"));

            m_cellProp->setHighLightImage("../assets/sprites/Task/Task_Cell_Text4.png");
            m_cellProp->setScale({4,3});
            m_cellProp->setObjectLocation({1200,850},0);
            m_cellProp->Start({8,6});
            m_GameObjectManager->spawn(m_Map, UnitType::INFANTRY, HouseType::ENEMY,
                                       {24, 17});
            m_GameObjectManager->spawn(m_Map, UnitType::INFANTRY, HouseType::ENEMY,
                                       {26, 18});
            m_GameObjectManager->spawn(m_Map, UnitType::INFANTRY, HouseType::ENEMY,
                                       {25, 17});
            m_stage=Stages::STAGE4;
        }
        break;
    }
    case Stages::STAGE4:{
        m_Text->Draw();
        m_cellProp->Update();
        break;
    }
    }
}
