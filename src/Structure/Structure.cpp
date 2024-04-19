//
// Created by 盧威任 on 1/30/24.
//
#include "Structure/Structure.hpp"
#include "Mechanics/GameObjectManager.hpp"
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
    onSelected();
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
}
void Structure::updateMoveable() {
    // debug
    printf("debug message : Structure movable\n");
    //
    glm::vec2 location = Util::Input::GetCursorPosition();
    location = MapUtil::ScreenToGlobalCoord(location);
    this->SetObjectLocation(location);
    this->SetVisible(true);
    this->Draw();
    glm::vec2 cellPos = MapUtil::GlobalCoordToCellCoord(location);
    //    std::shared_ptr<TileClass> tileClass =
    //    m_Map->getTileByCellPosition(cellPos);
    if (Util::Input::IsKeyPressed(
            Util::Keycode::MOUSE_LB) /*tileClass->getBuildable()*/) {
        this->SetObjectLocation(location);
        this->SetCurrentUpdateMode(updateMode::Fixed);
    }
}

void Structure::SetObjectLocation(glm::vec2 location) {
    location = MapUtil::PositionStickToGrid(location);
    ObjectLocation = location;
    DrawLocation = {location.x + 0.5 * CELL_SIZE.x,
                    location.y + 0.5 * CELL_SIZE.y};
    m_Transform.translation = DrawLocation;
}

void Structure::SetAttachVisible(bool visible) {
    m_HighLight.SetObjectLocation(this->DrawLocation);
    m_HighLight.SetVisible(visible);
}
void Structure::attachmentUpdate() {
    m_HighLight.SetObjectLocation(this->GetDrawLocation());
    m_HighLight.Draw();
}
