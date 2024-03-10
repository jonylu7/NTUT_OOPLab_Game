//
// Created by 盧威任 on 2/15/24.
//
#include "Scene/DefaultScene.hpp"
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

    m_Map.Init(std::vector<std::vector<std::shared_ptr<TileClass>>>(),
               m_TileSetSpriteSheet, 255, 255);
    m_UI.Start();

    // Way Point Test Start---------------
    m_Barracks->SetObjectLocation({100, 100});

    m_OreRefinery->SetObjectLocation({-60, -60});

    m_PowerPlants->SetObjectLocation({0, 0});

    m_WarFactory->SetObjectLocation({50, 50});

    m_Barracks->Start();
    // Way Point Test End---------------
}

void DefaultScene::Update() {
    Util::Transform transform;
    transform.translation = glm::vec2(0, 0);
    /*
    for (int i = 0; i < 200; i++) {
        m_TileSetSpriteSheet->DrawSpriteByIndex(i, transform, 3);
        transform.translation.x += 24;
    }

     */
    Util::Transform trans;
    // trans.scale = {1, 1};
    m_Map.Draw(trans, 0);
    /*
    m_Structure->SetCurrentUpdateMode(Structure::updateMode::Fixed);
    m_Structure->Update();
    */
    if (Util::Input::IsKeyPressed(Util::Keycode::END)) {
        glm::vec2 ogLBlocation = Util::Input::GetCursorPosition();
        /*
        if (m_Structure->GetCurrentUpdateMode() ==
            Structure::updateMode::Moveable) {
            m_Structure->SetObjectLocation(ogLBlocation);
            m_Structure->SetCurrentUpdateMode(Structure::updateMode::Fixed);
            LOG_DEBUG("Fixed");
        }*/
    }

    m_SceneCamera.Update();

    // m_Inf->Update();

    m_Renderer.Update();
    /*
    for (auto i : m_GameObjectList) {
        i->Update();
    }*/
    m_UI.Update();

    // Way Point Test Start-----------------------------------------------------
    /*
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    clickCheck= false;
    for(auto i :m_IWayPointStructureList){
        if(m_waypointTool.checkMous(i->GetStructureLocation(),Util::Input::GetCursorPosition())){
            m_WayPoint->SetObjectLocation(i->GetWayPointLocation());
            m_WayPoint->SetVisible(true);
            clickCheck= false;
            break;
        }
    }
}*/

    // Way Point Test End-------------------------------------------------------

    // Test 0306---------------------------------
    m_Barracks->Update();
    m_PowerPlants->Update();
    m_WarFactory->Update();
    m_OreRefinery->Update();
    m_ADVPowerPlants->Update();
    // Test 0306 End---------------------------------
}
