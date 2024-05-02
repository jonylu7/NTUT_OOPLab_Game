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
    void CursorSelect(std::shared_ptr<MapClass> m_Map);

private:
    std::vector<std::shared_ptr<Selectable>> m_LastSeletctedObjects;
    glm::vec2 m_CursorStart;
    glm::vec2 m_CursorEnd;
};

;
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CURSORSELECTION_HPP
