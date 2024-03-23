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
#include "Map.hpp"
#include "SpriteSheet.hpp"
#include "Structure/AdvencePowerPlants.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/IWayPointStructure.hpp"
#include "Structure/MouseOverlapTool.h"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/WarFactory.hpp"
#include "Structure/WayPoint.hpp"
#include "UI/UI.hpp"
#include "Unit/Avatar.hpp"
#include "Unit/FindValidPathToDest.hpp"
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
    GameObjectManager m_Manager;

    Avatar m_dummy;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
