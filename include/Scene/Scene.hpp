//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP

#include "Barracks.hpp"
#include "Camera.hpp"
#include "Capybara.hpp"
#include "Cell.hpp"
#include "Core/Context.hpp"
#include "Giraffe.hpp"
#include "Grid.hpp"
#include "Infantry.hpp"
#include "Rectangle.hpp"
#include "SpriteSheet.hpp"
#include "Structure.hpp"
#include "Triangle.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl2.h"
#include <ctime>

class Scene {
public:
    Scene(){};
    ~Scene(){};

    void Start();
    void Update();
    void End(){};

    void imgui();

    std::time_t How_long_has_passed() { return std::time(0) - initialTime; }

    void imgui_ShowSelectionRect(
        ImVec2 *start_pos, ImVec2 *end_pos,
        ImGuiMouseButton mouse_button = ImGuiMouseButton_Left);

private:
    std::vector<std::shared_ptr<Util::GameObject>> m_GameObjectList = {
        std::make_shared<Giraffe>(), std::make_shared<Capybara>(),
        std::make_shared<Barracks>()};

    Rectangle rect;
    std::shared_ptr<Structure> m_Structure = std::make_shared<Structure>();
    std::shared_ptr<Infantry> m_Inf = std::make_shared<Infantry>();

    std::time_t initialTime = std::time(0);
    CellClass cellTest;
    SpriteSheet m_SpriteSheet;

    CameraClass m_SceneCamera;
    Grid testGrid;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP
