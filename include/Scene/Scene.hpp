//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP

#include "Infantry.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Core/Context.hpp"
#include "Cell.hpp"
#include "SpriteSheet.hpp"
#include <ctime>
#include "Barracks.hpp"
#include "Capybara.hpp"
#include "Giraffe.hpp"
#include "Structure.hpp"
#include "Triangle.hpp"
#include "Infantry.hpp"
#include "Cell.hpp"
#include "Rectangle.hpp"
#include "SpriteSheet.hpp"


class Scene{
public:


Scene(){}
~Scene(){}

void Start();
void Update();
void End(){};

void imgui();


std::time_t How_long_has_passed(){
    return std::time(0)-initialTime;
}

void imgui_ShowSelectionRect(ImVec2* start_pos, ImVec2* end_pos, ImGuiMouseButton mouse_button = ImGuiMouseButton_Left);

private:
    Rectangle rect;

    std::vector<std::shared_ptr<Util::GameObject>> m_GameObjectList={
        std::make_shared<Giraffe>(),std::make_shared<Capybara>(),std::make_shared<Barracks>()
    };

    std::shared_ptr<Structure> m_Structure=std::make_shared<Structure>();
    std::shared_ptr<Infantry> m_Inf=std::make_shared<Infantry>();

    glm::vec2 CameraStartingPosition=glm::vec2(0.F,0.F);
    glm::vec2 CameraPosition=CameraStartingPosition;
    float CameraZoom=0.F;
    float CameraMovingSpeed=0.5F;
    float CameraZoomingSpeed=0.5F;

    std::time_t initialTime=std::time(0);
    CellClass cellTest;
    SpriteSheet m_SpriteSheet;

};



#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP
