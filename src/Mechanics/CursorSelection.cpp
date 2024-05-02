//
// Created by 盧威任 on 4/25/24.
//
#include "Mechanics/CursorSelection.hpp"

void CursorSelection::CursorSelect(std::shared_ptr<MapClass> m_Map,
                                   glm::vec2 *start, glm::vec2 *end) {

    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        *start = Util::Input::GetCursorPosition();
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
        // clear up last selected
        for (auto i : lastSeletctedObjects) {
            i->setSelected(false);
        }
        lastSeletctedObjects.clear();

        // get cursor position
        *end = Util::Input::GetCursorPosition();

        // select objects
        auto startcell = MapUtil::GlobalCoordToCellCoord(
            MapUtil::ScreenToGlobalCoord(*start));
        auto endcell =
            MapUtil::GlobalCoordToCellCoord(MapUtil::ScreenToGlobalCoord(*end));

        int max_x_cell = std::max(startcell.x, endcell.x);
        int max_y_cell = std::max(startcell.y, endcell.y);
        int min_x_cell = std::min(startcell.x, endcell.x);
        int min_y_cell = std::min(startcell.y, endcell.y);

        std::vector<std::shared_ptr<Selectable>> selectedUnits = {};
        for (int i = min_y_cell; i <= max_y_cell; i++) {
            for (int j = min_x_cell; j <= max_x_cell; j++) {
                auto tile = m_Map->getTileByCellPosition(glm::vec2(j, i));
                if (tile->ifStrucutreExists()) {
                    auto structure = tile->getStructure();
                    structure->setSelected(true);
                    lastSeletctedObjects.push_back(structure);
                    selectedUnits.push_back(structure);
                } else {
                    auto avatars = tile->getAvatars();
                    for (auto a : avatars) {
                        a->setSelected(true);
                        lastSeletctedObjects.push_back(a);
                    }
                    selectedUnits.insert(selectedUnits.end(), avatars.begin(),
                                         avatars.end());
                }
            }
        }
    }
}
