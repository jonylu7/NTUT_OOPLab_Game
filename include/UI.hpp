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
#include "UIScriptProcess.h"

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
        for (float i = float(WINDOW_WIDTH / 2); i >= -float(WINDOW_WIDTH / 2);
             i -= cellHeight) {
            // vertical
            lineV.push_back(Line(glm::vec2(float(WINDOW_WIDTH/2)/cellWidth, float(-(WINDOW_HEIGHT / 2))/ cellHeight ),
                                        glm::vec2(float(WINDOW_WIDTH/2)/cellWidth, float((WINDOW_HEIGHT / 2))/ cellHeight) ));
        }
         */
        /*
        for (float i =float(WINDOW_HEIGHT / 2); i >= -float(WINDOW_HEIGHT);i -= cellWidth/3) {
            // horz
            int c;
            lineV.push_back(Line(glm::vec2(-1.02F, float(i/ float(WINDOW_HEIGHT/0.3F))),
                                        glm::vec2(0.05F, float(i /float(WINDOW_HEIGHT/0.3F)))));
        }

        */

        auto width=m_GridSize.y*cellWidth;
        auto height=m_GridSize.x*cellHeight;
        for (int i=0;i<m_GridSize.x;i++){
            lineV.push_back(Line(glm::vec2(-(width/2),i*cellHeight),glm::vec2(width/2,i*cellWidth)));
        }
        for(int j=0;j<m_GridSize.y;j++){
            lineV.push_back(Line(glm::vec2(j*cellWidth,-(height/2)),glm::vec2(j*cellWidth,(height/2))));
        }

        //lineV.push_back(Line(glm::vec2(-120.F,-117.F),glm::vec2(3.F,6.F)));

        m_Grid.Start(lineV);
    }

    std::vector<ImVec2> getSpriteSheetCoordByIndex(int index);
    bool getImageButtonBySpriteSheetIndex(int index);

private:
    SpriteSheet m_SpriteSheet;
    Grid m_Grid;
    glm::vec2 m_GridSize={100,100};
    UIScriptProcess ButtonScript;
    std::shared_ptr<Structure> barracks = std::make_shared<Barracks>();
    std::shared_ptr<Structure> oreRefinery = std::make_shared<OreRefinery>();
    std::shared_ptr<Structure> powerPlant = std::make_shared<PowerPlants>();
    std::shared_ptr<Structure> warFactory = std::make_shared<WarFactory>();
    std::shared_ptr<Structure> advPowerPlant = std::make_shared<ADVPowerPlants>();
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
