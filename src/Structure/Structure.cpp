//
// Created by 盧威任 on 1/30/24.
//

#include "Structure/Structure.hpp"
#include "Util/Input.hpp"
#include "Util/Transform.hpp"
#include "config.hpp"
void Structure::Start() {
    m_HighLight.SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/HighLightB.png"));
    m_HighLight.SetHLScale(this->GetTranScale());
    m_HighLight.SetZIndex(DEFAULT_ZINDEX - 1);
    SetZIndex(DEFAULT_ZINDEX);
    this->SetAttachVisible(false);
    m_CurrentState = updateMode::Moveable;
}
void Structure::Update() {
    switch (m_CurrentState) {
    case updateMode::Invisidable: {
        this->updateInvinsible();
        break;
    }
    case updateMode::Fixed: {
        this->updateFixed();
        break;
    }
    case updateMode::Moveable: {
        this->updateMoveable();
        break;
    }
    }
}
void Structure::updateFixed() {
    // Attachment and self readjust location and draw---------------
    attachmentUpdate();
    this->Draw();
    // Script when select--------------------
    if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB) &&
        !b_selectingNewWayPoint) {
        if (MousOverlapTool::checkMous(
                GetObjectLocation() /*,GetScaledSize()*/)) {
            b_selected = true;
        } else {
            b_selected = false;
        }
    }
    if (b_selected) {
        onSelected(true);
    } else {
        onSelected(false);
    }
}
void Structure::updateMoveable() {
    glm::vec2 location = Util::Input::GetCursorPosition();
    location = MapClass::ScreenToGlobalCoord(location);
    this->SetObjectLocation(location);
    this->SetVisible(true);
    this->Draw();
    if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
        this->SetObjectLocation(location);
        this->SetCurrentUpdateMode(updateMode::Fixed);
        //在這裡增加設置Tile屬性
    }
}
void Structure::updateInvinsible() {
    this->SetAttachVisible(false);
}

void Structure::DecreaseHp(float Hp) {
    this->buildingHp -= Hp;
}
float Structure::GetElectricPower() {
    return this->electricPower;
}
float Structure::GetBuildingTime() {
    return this->buildingTime;
}
float Structure::GetBuildingCost() {
    return this->buildingCost;
}
float Structure::GetBuildingHp() {
    return this->buildingHp;
}
glm::vec2 Structure::ChangeToCell(glm::vec2 location) {
    int _x = location.x / CELL_SIZE.x;
    int _y = location.y / CELL_SIZE.y;
    return {_x * CELL_SIZE.x, _y * CELL_SIZE.y};
}
void Structure::SetObjectLocation(glm::vec2 location) {
    location = ChangeToCell(location);
    ObjectLocation = location;
    DrawLocation = {location.x + 0.5 * CELL, location.y + 0.5 * CELL};
    m_Transform.translation = DrawLocation;
}
void Structure::onSelected(bool selected) {
    this->SetAttachVisible(selected);
};

void Structure::SetAttachVisible(bool visible) {
    m_HighLight.SetObjectLocation(this->DrawLocation);
    m_HighLight.SetVisible(visible);
}
void Structure::attachmentUpdate() {
    m_HighLight.SetObjectLocation(this->GetDrawLocation());
    m_HighLight.Draw();
}
