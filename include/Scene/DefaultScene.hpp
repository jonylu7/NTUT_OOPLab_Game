//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP

#include "Barracks.hpp"
#include "Camera.hpp"
#include "Capybara.hpp"
#include "Core/Context.hpp"
#include "Grid.hpp"
#include "Infantry.hpp"
#include "Map.hpp"
#include "Rectangle.hpp"
#include "SpriteSheet.hpp"
#include "Structure.hpp"
#include "Triangle.hpp"
#include "UI.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Root.hpp"

class DefaultScene {
public:
    DefaultScene(){};
    ~DefaultScene(){};

    void Start();
    void Update();
    void End(){};

private:
    std::vector<std::shared_ptr<Util::GameObject>> m_GameObjectList = {
        std::make_shared<Capybara>(), std::make_shared<Capybara>(),
        std::make_shared<Barracks>()};

    Rectangle rect;
    std::shared_ptr<Structure> m_Structure = std::make_shared<Structure>();
    std::shared_ptr<Infantry> m_Inf = std::make_shared<Infantry>();

    SpriteSheet m_SpriteSheet;

    CameraClass m_SceneCamera;
    Grid testGrid;

    Util::Root m_Renderer;
    UIClass m_UI;
    MapClass m_Map;
    std::map<int, TileClass> m_tileSets;
    std::vector<int> m_OgMap;
    std::shared_ptr<SpriteSheet> m_TileSetSpriteSheet =
        std::make_shared<SpriteSheet>();
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
