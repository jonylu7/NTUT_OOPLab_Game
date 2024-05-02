//
// Created by 盧威任 on 3/3/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#include "Camera.hpp"
#include "Display/SpriteSheet.hpp"
#include "Mechanics//Player.hpp"
#include "Mechanics/GameObjectID.hpp"
#include "Mechanics/UnitManager.hpp"
#include "UI/UIScriptProcess.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "pch.hpp"
#include <unordered_map>

class UIClass {
public:
    void Start(std::shared_ptr<MapClass> map,
               std::shared_ptr<UnitManager> gameobjectmanager);
    void Update();

    static unsigned int getUnitConstructCount(UnitType type) {
        return s_unitConstructCount[type];
    }
    static void setUnitConstructCount(UnitType type, int value) {
        s_unitConstructCount[type] += value;
    }
    static void resetUnitConstructCount(UnitType type) {
        s_unitConstructCount[type] = 0;
    }

    std::unique_ptr<Structure> getSelectedBuilding();
    bool getIfAnyBuildingReadyToBuild(); // 避免Scene收到空的getSelectedBuilding

    std::shared_ptr<Avatar> getUnitFromUI();
    bool getIfUnitReadyToSpawn() { return ButtonScript.getIfReadytoSpawn(); }
    void setIfUnitReadyToSpawn(bool b) { ButtonScript.setIfReadytoSpawn(b); }

    void
    checkExistBuilding(std::vector<std::shared_ptr<Structure>> buildingList);

protected:
    void importMap(std::shared_ptr<MapClass> m_Map) { this->m_Map = m_Map; }
    void importGameObjManager(std::shared_ptr<UnitManager> gameObjectManager) {
        m_gameObjectManager = gameObjectManager;
        ButtonScript.importGameObjManager(gameObjectManager);
    }

private:
    UIScriptProcess ButtonScript;
    void InitUnitQueue();

    void ShowPlayerConstructionMenu();
    void ShowPlayerStatus();
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

    static std::unordered_map<UnitType, unsigned int> s_unitConstructCount;
    Grid m_Grid;
    glm::vec2 m_GridSize = {100, 100};

    // 0318
    void setSelectToBuild(UnitType type) { m_selectedStructureType = type; }

    ImGuiIO &io = ImGui::GetIO();

    ImFont *sacker_med = io.Fonts->AddFontFromFileTTF(
        "../assets/fonts/sackersgothicstd-medium.otf", 11);
    ImFont *sacker_heav = io.Fonts->AddFontFromFileTTF(
        "../assets/fonts/sackersgothicstd-heavy.otf", 11);
    ImFont *sacker_light = io.Fonts->AddFontFromFileTTF(
        "../assets/fonts/sackersgothicstd-light.otf", 11);

    bool b_barackBuilt = false;
    bool b_warfactoryBuilt = false;
    bool b_orerefineryBuilt = false;

    glm::vec2 m_barrackCell;
    glm::vec2 m_barrackTargetCell;
    glm::vec2 m_warfactoryCell;
    glm::vec2 m_warfactoryTargetCell;
    glm::vec2 m_orerefineryCell;
    glm::vec2 m_orerefineryTargetCell;
    UnitType m_selectedStructureType = UnitType::NONE;

    // ptr import from scene
    std::shared_ptr<MapClass> m_Map;
    std::shared_ptr<UnitManager> m_gameObjectManager;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
