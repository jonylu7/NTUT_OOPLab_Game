//
// Created by 盧威任 on 3/3/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#include "Camera.hpp"
#include "GameObjectID.hpp"
#include "SpriteSheet.hpp"
#include "UI/UIScriptProcess.hpp"
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
    static void resetUnitConstructCount(unitType type) {
        s_unitConstructCount[type] = 0;
    }

    std::unique_ptr<Structure> getSelectedBuilding();
    bool
    getIfAnythingCanSelectToBuild(); // 避免Scene收到空的getSelectedBuilding

private:
    UIScriptProcess ButtonScript;
    void InitUnitQueue();
    void ShowCursorSelectionRegion(ImVec2 *start_pos, ImVec2 *end_pos,
                                   ImGuiMouseButton mouse_button);
    void ShowPlayerConstructionMenu();
    void ShowHeaderSection();
    void ShowBuildingTab();
    void ShowInfantryTab();
    void ShowDefTab();
    void ShowVehTab();

    std::vector<ImVec2>
    getSpriteSheetCoordByIndex(std::shared_ptr<SpriteSheet> spritesheet,
                               int index);

    std::shared_ptr<Util::CustomizableImage> m_image =
        std::make_shared<Util::CustomizableImage>("../assets/sprites/p05.png");
    bool
    getImageButtonBySpriteSheetIndex(std::shared_ptr<SpriteSheet> spritesheet,
                                     int index);

    std::shared_ptr<SpriteSheet> m_StructureIconSpriteSheet =
        std::make_shared<SpriteSheet>();
    std::shared_ptr<SpriteSheet> m_InfantryIconSpriteSheet =
        std::make_shared<SpriteSheet>();
    std::shared_ptr<SpriteSheet> m_VehiclesIconSpriteSheet =
        std::make_shared<SpriteSheet>();

    static std::unordered_map<unitType, unsigned int> s_unitConstructCount;
    Grid m_Grid;
    glm::vec2 m_GridSize = {100, 100};

    // 0318
    bool getIfSelectToBuild(unitType type);
    void setSelectToBuild(unitType type);
    bool selectLock();

    ImGuiIO &io = ImGui::GetIO();

    ImFont *sacker_med = io.Fonts->AddFontFromFileTTF(
        "../assets/fonts/sackersgothicstd-medium.otf", 100);
    ImFont *sacker_heav = io.Fonts->AddFontFromFileTTF(
        "../assets/fonts/sackersgothicstd-heavy.otf", 100);
    ImFont *sacker_light = io.Fonts->AddFontFromFileTTF(
        "../assets/fonts/sackersgothicstd-light.otf", 100);

    bool b_Baracks = false;
    bool b_OreRefinery = false;
    bool b_PowerPlants = false;
    bool b_WarFactory = false;
    bool b_ADVPowerPlant = false;
    bool b_SelectToBuild = false;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
