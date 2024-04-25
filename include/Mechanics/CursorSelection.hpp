//
// Created by 盧威任 on 4/24/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_CURSORSELECTION_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_CURSORSELECTION_HPP
#include "Map/Map.hpp"
#include "Map/MapUtility.hpp"
#include "Selectable.hpp"
#include "pch.hpp"
class CursorSelection {
public:
    CursorSelection() {}
    virtual ~CursorSelection() {}
    void CursorSelect(std::shared_ptr<MapClass> m_Map, glm::vec2 *start,
                      glm::vec2 *end) {

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
            auto endcell = MapUtil::GlobalCoordToCellCoord(
                MapUtil::ScreenToGlobalCoord(*end));

            int max_x_cell = std::max(startcell.x, endcell.x);
            int max_y_cell = std::max(startcell.y, endcell.y);
            int min_x_cell = std::min(startcell.x, endcell.x);
            int min_y_cell = std::min(startcell.y, endcell.y);

            for (int i = min_y_cell; i <= max_y_cell; i++) {
                for (int j = min_x_cell; j <= max_x_cell; j++) {
                    auto objects = m_Map->getTileByCellPosition(glm::vec2(j, i))
                                       ->getSelectableObjects();
                    for (auto i : objects) {
                        if (i->getSelected() == false) {
                            i->setSelected(true);
                            lastSeletctedObjects.push_back(i);
                        }
                    }
                }
            }
        }
    }

protected:
    std::vector<std::shared_ptr<Selectable>> lastSeletctedObjects;
    glm::vec2 cursorstart;
    glm::vec2 cursorend;
};

;
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CURSORSELECTION_HPP
