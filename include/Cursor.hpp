//
// Created by 盧威任 on 4/13/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_CURSOR_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_CURSOR_HPP
#include "DrawOverlays.hpp"
#include "Map/Map.hpp"
#include "Map/MapUtility.hpp"
#include "Structure/Structure.hpp"
class CursorClass {
public:
    CursorClass() {
        m_testdraw.Start(std::vector({glm::vec2(0.F, 0.F)}),
                         DrawOverlays::OverlayShapes::R_CROSS);
    }
    ~CursorClass() {}
    void Update(std::shared_ptr<TileClass> tile) {
        DrawWalkable(tile->getWalkable());

        Util::Transform trans2;
        trans2.translation = Structure::PositionStickToGrid(
            MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));
        m_testdraw.DrawUsingCamera(trans2, 1);
    }

    void DrawWalkable(bool tilewalkable) {
        if (tilewalkable) {
            m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::B_BOXES);
        } else {
            m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::R_CROSS);
        }
    }

    void DrawBuildable(bool tilebuildable) {
        if (tilebuildable) {
            m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::B_SLATED);
        } else {
            m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::R_SLATED);
        }
    }

private:
    DrawOverlays m_testdraw;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CURSOR_HPP
