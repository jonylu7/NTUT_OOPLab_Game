//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP

#include "Camera.hpp"
#include "Core/Context.hpp"
#include "Grid.hpp"
#include "Map.hpp"
#include "SpriteSheet.hpp"
#include "UI.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Renderer.hpp"

#include "Structure/AdvencePowerPlants.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/IWayPointStructure.hpp"
#include "Structure/MousOverlapTool.h"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/WarFactory.hpp"
#include "Structure/WayPoint.hpp"


class DefaultScene {
public:
    DefaultScene(){};
    ~DefaultScene(){};

    void Start();
    void Update();
    void End(){};

private:
    /*
    std::vector<std::shared_ptr<Util::GameObject>> m_GameObjectList = {
        std::make_shared<Capybara>(), std::make_shared<Capybara>(),
        std::make_shared<Barracks>()};
    */
    /*
    std::shared_ptr<Infantry> m_Inf = std::make_shared<Infantry>();
    */
    SpriteSheet m_SpriteSheet;

    CameraClass m_SceneCamera;
    Grid testGrid;

    Util::Renderer m_Renderer;
    UIClass m_UI;
    MapClass m_Map;
    std::map<int, TileClass> m_tileSets;
    std::vector<int> m_OgMap;
    std::shared_ptr<SpriteSheet> m_TileSetSpriteSheet =
        std::make_shared<SpriteSheet>();

    // Way Point Test Start---------------
    MousOverlapTool m_waypointTool;
    std::shared_ptr<Barracks> m_Barracks = std::make_shared<Barracks>();
    std::shared_ptr<OreRefinery> m_OreRefinery =
        std::make_shared<OreRefinery>();
    std::shared_ptr<PowerPlants> m_PowerPlants =
        std::make_shared<PowerPlants>();
    std::shared_ptr<WarFactory> m_WarFactory = std::make_shared<WarFactory>();
    std::shared_ptr<ADVPowerPlants> m_ADVPowerPlants =
        std::make_shared<ADVPowerPlants>();

    std::vector<std::shared_ptr<IWayPointStructure>> m_IWayPointStructureList =
        {m_Barracks, m_OreRefinery, m_WarFactory};

    // Way Point Test End---------------
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
