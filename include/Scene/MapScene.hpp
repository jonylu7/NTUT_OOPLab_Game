//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MAPSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MAPSCENE_HPP
#include "Camera.hpp"
#include "Core/Context.hpp"
#include "GameObjectManager.hpp"
#include "Map/MapbinReader.hpp"
#include "Map/YAMLReader.hpp"

#include "DrawOverlays.hpp"
#include "Grid.hpp"
#include "Map/Map.hpp"
#include "SpriteSheet.hpp"
#include "Structure/AdvencePowerPlants.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/IWayPointStructure.hpp"
#include "Structure/MousOverlapTool.h"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/WarFactory.hpp"
#include "Structure/WayPoint.hpp"
#include "UI/UI.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Renderer.hpp"

class MapScene {
public:
    MapScene(){};
    ~MapScene(){};

    void Start();
    void Update();
    void End(){};

private:
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
    MapbinReader reading;

    SpriteSheet m_SpriteSheet;
    DrawOverlays m_testdraw;
    CameraClass m_SceneCamera;
    Grid testGrid;
    GameObjectManager m_GameObjectManager;
    Util::Renderer m_Renderer;
    UIClass m_UI;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
