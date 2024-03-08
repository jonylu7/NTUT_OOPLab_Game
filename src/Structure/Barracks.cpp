#include "Structure/Barracks.hpp"
void Barracks::Start() {
    this->SetWayPointLocation({this->GetObjectLocation().x + 50,
                               this->GetObjectLocation().y + 50}); // Debug Only
    // Set Texture----------------------------------------
    this->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/barracks.png"));
    m_wayPoint->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/flagB.png"));
    m_HighLight.SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/HighLightB.png"));
    this->SetZIndex(DEFAULT_ZINDEX);
    m_wayPoint->SetZIndex(DEFAULT_ZINDEX);
    m_HighLight.SetZIndex(DEFAULT_ZINDEX);
    // Set Attachment Location &
    // Visibility----------------------------------------
    m_wayPoint->SetObjectLocation(this->GetWayPointLocation());
    m_HighLight.SetHLScale(this->GetTranScale());
    m_HighLight.SetObjectLocation(this->GetObjectLocation());
    this->SetAttachVisible(false);
    // Line Setup----------------------------------------
    m_Grid.Start(
        std::vector<Line>({Line(GetObjectLocation(), GetWayPointLocation())}));
    m_Grid.SetActivate(false);
    // State
    SetCurrentUpdateMode(Structure::updateMode::Moveable);
}
void Barracks::updateFixed() {
    m_Grid.setLine(GetObjectLocation(), GetWayPointLocation());
    Util::Transform Trans;
    m_Grid.DrawUsingCamera(Trans, DEFAULT_ZINDEX);

    // Attachment and self readjust location and draw---------------
    m_wayPoint->SetObjectLocation(this->GetWayPointLocation());
    m_HighLight.SetObjectLocation({GetObjectLocation().x + 0.5 * CELL_SIZE.x,
                                   GetObjectLocation().y + 0.5 * CELL_SIZE.y});
    this->Draw();
    m_wayPoint->Draw();
    m_HighLight.Draw();

    // Script when select--------------------
    if (Util::Input::IsKeyDown(Util::Keycode::T)) {
        b_select = !b_select;
    }
    if (b_select) {
        onSelected(true);
    } else {
        onSelected(false);
    }
}
void Barracks::updateMoveable() {
    glm::vec2 location = Util::Input::GetCursorPosition();
    location = MapClass::ScreenToGlobalCoord(location);
    location = MapClass::GlobalCoordToCellCoord(location);
    location = MapClass::CellCoordToGlobal(location);
    this->SetObjectLocation(location);
    this->SetVisible(true);
    this->Draw();
    if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
        this->SetObjectLocation(location);

        m_HighLight.SetObjectLocation(
            {GetObjectLocation().x + 0.5 * CELL_SIZE.x,
             GetObjectLocation().y + 0.5 * CELL_SIZE.y});

        this->SetWayPointLocation(
            {this->GetObjectLocation().x + 48 - 0.5 * CELL_SIZE.x,
             this->GetObjectLocation().y + 48 - 0.5 * CELL_SIZE.y});
        onSelected(false);
        this->SetCurrentUpdateMode(updateMode::Fixed);
    }
}

void Barracks::onSelected(bool selected) {
    this->SetAttachVisible(selected);
    if (selected) {
        if (Util::Input::IsKeyDown(Util::Keycode::V)) {
            this->SetWayPointLocation(
                {GetWayPointLocation().x + 5, GetWayPointLocation().y + 5});
        }
    }
}
void Barracks::SetAttachVisible(bool visible) {
    m_wayPoint->SetVisible(visible);
    m_HighLight.SetVisible(visible);
    m_Grid.SetActivate(visible);
}
