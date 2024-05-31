//
// Created by 盧威任 on 3/26/24.
//
#include "Structure/WayPointStructure.hpp"
#include "Map/MapUtility.hpp"

void WayPointStructure::whenSelected() {
    if (this->getSelected() && this->getStructureOrder()->getBuilt()) {
        if (Util::Input::IsKeyPressed(Util::Keycode(Util::Keycode::MOUSE_RB))) {
            this->setWaypointLocationByCellCoord(
                MapUtil::GlobalCoordToCellCoord(MapUtil::ScreenToGlobalCoord(
                    Util::Input::GetCursorPosition())));
        }
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
    m_wayPoint->SetObjectLocation(this->getWaypointLocation());
    m_Grid.setLine(GetDrawLocation(), getWaypointLocation(),
                   glm::vec3(0, 0, 1));
    m_wayPoint->Draw();
    m_HighLight.Draw();
    Util::Transform Trans;
    m_Grid.DrawUsingCamera(Trans, DEFAULT_ZINDEX);
}
