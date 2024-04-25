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
                      glm::vec2 *end);

protected:
    std::vector<std::shared_ptr<Selectable>> lastSeletctedObjects;
    glm::vec2 cursorstart;
    glm::vec2 cursorend;
};

;
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CURSORSELECTION_HPP
