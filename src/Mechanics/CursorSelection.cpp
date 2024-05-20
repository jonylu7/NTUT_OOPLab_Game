//
// Created by 盧威任 on 4/25/24.
//
#include "Mechanics/CursorSelection.hpp"

void CursorSelection::cursorSelect() {

    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        m_CursorStart = Util::Input::GetCursorPosition();
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
        // clear up last selected
        clearAllSelectedObjects();
        // get cursor position
        m_CursorEnd = Util::Input::GetCursorPosition();

        // select objects
        auto startcell = MapUtil::GlobalCoordToCellCoord(
            MapUtil::ScreenToGlobalCoord(m_CursorStart));
        auto endcell = MapUtil::GlobalCoordToCellCoord(
            MapUtil::ScreenToGlobalCoord(m_CursorEnd));

        int max_x_cell = std::max(startcell.x, endcell.x);
        int max_y_cell = std::max(startcell.y, endcell.y);
        int min_x_cell = std::min(startcell.x, endcell.x);
        int min_y_cell = std::min(startcell.y, endcell.y);

        for (int i = min_y_cell; i <= max_y_cell; i++) {
            for (int j = min_x_cell; j <= max_x_cell; j++) {
                auto tile = m_Map->getTileByCellPosition(glm::vec2(j, i));
                if (tile->ifStructureExists()) {
                    auto structure = tile->getStructure();
                    Append(structure);

                } else {
                    auto avatars = tile->getAvatars();
                    for (auto a : avatars) {
                        Append(a);
                    }
                }
            }
        }
    }
}

void CursorSelection::Update() {
    cursorSelect();
}

void CursorSelection::clearAllSelectedObjects() {

    for (auto a : m_SelectedUnits) {
        a->setSelected(false);
    }
    m_SelectedUnits.clear();
}

void CursorSelection::Append(std::shared_ptr<Avatar> avatar) {
    avatar->setSelected(true);
    m_SelectedUnits.push_back(avatar);
}

void CursorSelection::Append(std::shared_ptr<Structure> structure) {
    structure->setSelected(true);
    m_SelectedUnits.push_back(structure);
}
