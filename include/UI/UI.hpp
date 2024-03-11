//
// Created by 盧威任 on 3/3/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#include "Camera.hpp"
#include "GameObjectID.hpp"
#include "SpriteSheet.hpp"
#include "UIScriptProcess.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl2.h"
#include "pch.hpp"
#include <unordered_map>

class UIClass {
public:
    void Start();
    void Update();

    static unsigned int getUnitConstructCount(unitType type) {
        return s_unitConstructCount[type];
    }
    static void setUnitConstructCount(unitType type, int value) {
        s_unitConstructCount[type] += value;
    }

private:
    void InitUnitQueue();
    void ShowCursorSelectionRegion(ImVec2 *start_pos, ImVec2 *end_pos,
                                   ImGuiMouseButton mouse_button);
    void ShowPlayerConstructionMenu();

    std::vector<ImVec2> getSpriteSheetCoordByIndex(int index);
    bool getImageButtonBySpriteSheetIndex(int index);

    void objUpdate();

private:
    SpriteSheet m_IconSpriteSheet;
    static std::unordered_map<unitType, unsigned int> s_unitConstructCount;
    Grid m_Grid;
    glm::vec2 m_GridSize = {100, 100};
    UIScriptProcess ButtonScript;

    std::shared_ptr<Structure> barracks = std::make_shared<Barracks>();
    std::shared_ptr<Structure> oreRefinery = std::make_shared<OreRefinery>();
    std::shared_ptr<Structure> powerPlant = std::make_shared<PowerPlants>();
    std::shared_ptr<Structure> warFactory = std::make_shared<WarFactory>();
    std::shared_ptr<Structure> advPowerPlant =
        std::make_shared<ADVPowerPlants>();
    std::vector<std::shared_ptr<Structure>> StructureArray = {
        barracks, oreRefinery, powerPlant, warFactory, advPowerPlant,
    };
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
