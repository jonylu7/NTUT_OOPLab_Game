//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP

#include "Camera.hpp"
#include "Core/Context.hpp"
#include "GameObjectManager.hpp"

#include "DrawOverlays.hpp"
#include "Grid.hpp"
#include "Map/Map.hpp"
#include "SpriteSheet.hpp"
#include "Structure/AdvencePowerPlants.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/IWayPointStructure.hpp"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/WarFactory.hpp"
#include "Structure/WayPoint.hpp"
#include "UI/UI.hpp"
#include "Unit/Avatar.hpp"
#include "Unit/FindValidPathToDest.hpp"
#include "Unit/Hunter.hpp"
#include "Unit/Runner.hpp"
#include "Unit/PathfindingUnit.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Renderer.hpp"

class DefaultScene {

public:
    DefaultScene(){};
    ~DefaultScene(){};

    void Start();
    void Update();
    void End(){};

private:
    SpriteSheet m_SpriteSheet;
    DrawOverlays m_testdraw;
    CameraClass m_SceneCamera;
    Grid testGrid;
    GameObjectManager m_GameObjectManager;
    Util::Renderer m_Renderer;
    UIClass m_UI;

    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    std::shared_ptr<Player> m_Player = std::make_shared<Player>();
    std::shared_ptr<GameObjectManager> m_Manager =
        std::make_shared<GameObjectManager>();

    Avatar m_dummy;
    std::shared_ptr<Hunter> m_hunter=std::make_shared<Hunter>();
    std::shared_ptr<Runner> m_runner=std::make_shared<Runner>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
