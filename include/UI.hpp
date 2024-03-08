//
// Created by 盧威任 on 3/3/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#include "Camera.hpp"
#include "SpriteSheet.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl2.h"
#include "pch.hpp"

// not sure how does it work commented by Lu
enum class ButtonClicked {
    // buildings
    POWER_PLANT,
    BARRACKS,
    ORE_REF,
    WAR_FACT,
    ADV_POWER_PLANT,

    // defense
    SANDBAGS,
    PILLBOX,
    TURRET,

    // Troopers
    INFANTRY,

    // Vehicles
    TRUCK
};

class UIClass {
public:
    void Start();
    void Update();

private:
    void ShowCursorSelectionRegion(ImVec2 *start_pos, ImVec2 *end_pos,
                                   ImGuiMouseButton mouse_button);
    void ShowPlayerConstructionMenu();


    std::vector<ImVec2> getSpriteSheetCoordByIndex(int index);
    bool getImageButtonBySpriteSheetIndex(int index);

private:
    SpriteSheet m_SpriteSheet;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
