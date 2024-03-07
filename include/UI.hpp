//
// Created by 盧威任 on 3/3/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#include "Camera.hpp"
#include "Grid.hpp"
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

    void InitGrid(){
        std::vector<Line> lineV;
        float cellWidth = 48.F;
        float cellHeight = 48.F;
        /*
        for (int i = (WINDOW_WIDTH / 2); i >= int(-(WINDOW_WIDTH / 2));
             i -= cellHeight) {
            // vertical
            lineV.push_back(Line(glm::vec2(i/(WINDOW_WIDTH / 2), float(-(WINDOW_HEIGHT / 2)/(WINDOW_HEIGHT/2))),
                                        glm::vec2(i/(WINDOW_WIDTH / 2), float((WINDOW_HEIGHT / 2)/(WINDOW_HEIGHT/2)))));
        }

        for (int i = (WINDOW_HEIGHT / 2); i >= int(-(WINDOW_HEIGHT / 2));
             i -= cellWidth) {
            // horz
            lineV.push_back(Line(glm::vec2(int(-(WINDOW_WIDTH / 2)), i),
                                        glm::vec2(int(WINDOW_WIDTH / 2), i)));
        }
         */
        lineV.push_back(Line(glm::vec2(-0.5,-0.5),glm::vec2(0.5,0.5)));
        m_Grid.Start(lineV);
    }

    std::vector<ImVec2> getSpriteSheetCoordByIndex(int index);
    bool getImageButtonBySpriteSheetIndex(int index);

private:
    SpriteSheet m_SpriteSheet;
    Grid m_Grid;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
