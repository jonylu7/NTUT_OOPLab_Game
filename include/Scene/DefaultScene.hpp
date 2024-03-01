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
#include "Rectangle.hpp"
#include "SpriteSheet.hpp"
#include "Structure.hpp"
#include "Triangle.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Root.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl2.h"

class DefaultScene {
public:
    DefaultScene(){};
    ~DefaultScene(){};

    void Start();
    void Update();
    void End(){};

    void imgui();

    std::time_t How_long_has_passed() { return std::time(0); }

    void imgui_ShowSelectionRect(
        ImVec2 *start_pos, ImVec2 *end_pos,
        ImGuiMouseButton mouse_button = ImGuiMouseButton_Left);

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
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DEFAULTSCENE_HPP
