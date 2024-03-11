#include "Structure/OreRefinery.hpp"

void OreRefinery::Start() {
    // Set Texture----------------------------------------
    this->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/barracks.png"));
    m_wayPoint->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/flagB.png"));
    m_HighLight.SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/HighLightB.png"));
    // Set ZIndex
    this->SetZIndex(DEFAULT_ZINDEX);
    m_wayPoint->SetZIndex(DEFAULT_ZINDEX);
    m_HighLight.SetZIndex(DEFAULT_ZINDEX - 1);
    // Set Attachment Scale &
    // Visibility----------------------------------------
    m_HighLight.SetHLScale(this->GetTranScale());
    onSelected(false);
    // State
    SetCurrentUpdateMode(Structure::updateMode::Moveable);
}

void OreRefinery::updateMoveable() {
    glm::vec2 location = Util::Input::GetCursorPosition();
    location = MapClass::ScreenToGlobalCoord(location);
    location = MapClass::GlobalCoordToCellCoord(location);
    location = MapClass::CellCoordToGlobal(location);
    this->SetObjectLocation(location);
    this->SetVisible(true);
    this->Draw();
    if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
        this->SetObjectLocation(location);
        this->SetWayPointLocation({GetDrawLocation().x + CELL_SIZE.x,
                                   GetDrawLocation().y + CELL_SIZE.y});
        onSelected(false);
        this->SetCurrentUpdateMode(updateMode::Fixed);
    }
}
void OreRefinery::onSelected(bool selected) {
    if (b_selectingNewWayPoint) {
        this->SetWayPointLocation(
            MapClass::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));
        b_selectingNewWayPoint = false;
    }
    attachmentUpdate();
    this->SetAttachVisible(selected);
    if (selected) {
        if (Util::Input::IsKeyPressed(Util::Keycode::V)) {
            b_selectingNewWayPoint = true;
        }
    }
}
void OreRefinery::SetAttachVisible(bool visible) {
    m_wayPoint->SetVisible(visible);
    m_HighLight.SetVisible(visible);
    m_Grid.SetActivate(visible);
}
void OreRefinery::attachmentUpdate() {
    m_HighLight.SetObjectLocation(this->GetDrawLocation());
    m_wayPoint->SetObjectLocation(this->GetWayPointLocation());
    m_Grid.setLine(GetDrawLocation(), GetWayPointLocation(),
                   glm::vec3(0, 0, 1));
    m_wayPoint->Draw();
    m_HighLight.Draw();
    Util::Transform Trans;
    m_Grid.DrawUsingCamera(Trans, DEFAULT_ZINDEX);
}
