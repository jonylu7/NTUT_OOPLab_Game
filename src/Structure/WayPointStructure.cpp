//
// Created by 盧威任 on 3/26/24.
//
#include "Structure/WayPointStructure.hpp"
#include "Map/MapUtility.hpp"

void WayPointStructure::updateMoveable() {
    glm::vec2 location = Util::Input::GetCursorPosition();
    location = MapUtil::ScreenToGlobalCoord(location);
    location = MapUtil::GlobalCoordToCellCoord(location);
    location = MapUtil::CellCoordToGlobal(location);
    this->SetObjectLocation(location);
    this->SetVisible(true);
//    this->Draw();
    glm::vec2 cellPos = MapUtil::GlobalCoordToCellCoord(location);
    m_StructureSpriteSheet->DrawSpriteByIndex(m_StructureSpriteSheet->getSize()-1,m_Transform,DEFAULT_ZINDEX);
    if (Util::Input::IsKeyPressed(
            Util::Keycode::MOUSE_LB) && ifBuildable()) {
        this->SetObjectLocation(location);
        this->SetWayPointLocation({GetDrawLocation().x + CELL_SIZE.x,
                                   GetDrawLocation().y + CELL_SIZE.y});
        onSelected();
        m_SpriteSheetAnimation->initSpriteSheetAnimation(m_StructureSpriteSheet,true,INTERVAL,false);
        SetOccupiedAreaUnbuildable();
        this->SetCurrentUpdateMode(updateMode::Fixed);
    }
}
void WayPointStructure::onSelected() {
    if (getSelected()) {
        this->SetWayPointLocation(
            MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));
        setSelected(false);
    }
    attachmentUpdate();
    this->SetAttachVisible(getSelected());
}
void WayPointStructure::SetAttachVisible(bool visible) {
    m_wayPoint->SetVisible(visible);
    m_HighLight.SetVisible(visible);
    m_Grid.SetActivate(visible);
}
void WayPointStructure::attachmentUpdate() {
    m_HighLight.SetObjectLocation(this->GetDrawLocation());
    m_wayPoint->SetObjectLocation(this->GetWayPointLocation());
    m_Grid.setLine(GetDrawLocation(), GetWayPointLocation(),
                   glm::vec3(0, 0, 1));
    m_wayPoint->Draw();
    m_HighLight.Draw();
    Util::Transform Trans;
    m_Grid.DrawUsingCamera(Trans, DEFAULT_ZINDEX);
}
