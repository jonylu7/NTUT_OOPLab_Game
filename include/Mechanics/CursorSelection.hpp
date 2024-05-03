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
    void cursorSelect(std::shared_ptr<MapClass> m_Map);
    void Update();

private:
    void clearAllSelectedObjects();
    void Append(std::shared_ptr<Structure> structure);
    void Append(std::shared_ptr<Avatar> avatar);

private:
    std::shared_ptr<Structure> m_SelectedStructure =
        std::make_shared<Structure>();
    std::vector<std::shared_ptr<Avatar>> m_SelectedAvatars =
        std::vector<std::shared_ptr<Avatar>>();
    glm::vec2 m_CursorStart;
    glm::vec2 m_CursorEnd;
};

;
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CURSORSELECTION_HPP
