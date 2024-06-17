//
// Created by 盧威任 on 4/24/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_CURSORSELECTION_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_CURSORSELECTION_HPP
#include "Map/Map.hpp"
#include "Map/MapUtility.hpp"
#include "Unit/Selectable.hpp"
#include "pch.hpp"
class CursorSelection {
public:
    CursorSelection() {}
    virtual ~CursorSelection() {}
    void Start(std::shared_ptr<MapClass> map) { m_Map = map; }
    void cursorSelect();
    void Update();

private:
    void clearAllSelectedObjects();
    void Append(std::shared_ptr<Structure> structure);
    void Append(std::shared_ptr<Avatar> avatar);

private:
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();

    std::vector<std::shared_ptr<Selectable>> m_SelectedUnits;
    glm::vec2 m_CursorStart;
    glm::vec2 m_CursorEnd;
};

;
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CURSORSELECTION_HPP
