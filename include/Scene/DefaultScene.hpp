//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP

#include "Camera.hpp"
#include "Core/Context.hpp"
#include "GameObjectManager.hpp"

#include "Grid.hpp"
#include "Map.hpp"
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

class DefaultScene {
public:
    DefaultScene(){};
    ~DefaultScene(){};

    void Start();
    void Update();
    void End(){};

private:
    SpriteSheet m_SpriteSheet;

    CameraClass m_SceneCamera;
    Grid testGrid;
    GameObjectManager m_GameObjectManager;
    Util::Renderer m_Renderer;
    UIClass m_UI;
    MapClass m_Map;
    std::map<int, TileClass> m_tileSets;
    std::vector<int> m_OgMap;
    std::shared_ptr<SpriteSheet> m_TileSetSpriteSheet =
        std::make_shared<SpriteSheet>();
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
