//
// Created by 盧威任 on 3/8/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DRAWOVERLAYS_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DRAWOVERLAYS_HPP
#include "Core/Drawable.hpp"
#include "Util/Image.hpp"
#include "Util/TransformUtils.hpp"
#include "pch.hpp"
class DrawOverlays : public Core::Drawable {

    /* boxes:draw box on cell
     *cross:draw cross on cell
     * selected: defines bottom left & top right, show selected "corner" on
     *given cell range circle: defines only the center(cell coord) & the
     *radius(cell) circle-dash: defines only the center(cell coord) & the
     *radius(cell)
     */

public:
    enum class OverlayShapes {
        B_BOXES,
        R_BOXES,
        R_CROSS,
        B_SLATED,
        R_SLATED,
        B_CROSS,
        CROSSWBOX,
        SELECTED,
        CIRCLE,
        CIRCLE_DASHED
    };
    DrawOverlays(){};
    ~DrawOverlays(){};
    void Start(std::vector<glm::vec2> cellcoords, OverlayShapes shapes) {
        m_DrawShapes = shapes;
        m_DrawCellLocation = cellcoords;
        if (m_DrawShapes == OverlayShapes::B_BOXES) {
            m_Image = std::make_shared<Util::Image>(
                std::string("../assets/sprites/Shapes/B_Box.png"));
        } else if (m_DrawShapes == OverlayShapes::R_CROSS) {
            m_Image = std::make_shared<Util::Image>(
                std::string("../assets/sprites/Shapes/R_Cross.png"));
        } else if (m_DrawShapes == OverlayShapes::B_SLATED) {
            m_Image = std::make_shared<Util::Image>(
                std::string("../assets/sprites/Shapes/B_Slated.png"));
        } else if (m_DrawShapes == OverlayShapes::R_SLATED) {
            m_Image = std::make_shared<Util::Image>(
                std::string("../assets/sprites/Shapes/R_Slated.png"));
        }
    }
    void setDrawMode(OverlayShapes shapes) {
        m_DrawShapes = shapes;
        if (m_DrawShapes == OverlayShapes::B_BOXES) {
            m_Image->SetImage(
                std::string("../assets/sprites/Shapes/B_Box.png"));
        } else if (m_DrawShapes == OverlayShapes::R_CROSS) {
            m_Image->SetImage(
                std::string("../assets/sprites/Shapes/R_Cross.png"));
        } else if (m_DrawShapes == OverlayShapes::B_SLATED) {
            m_Image->SetImage(
                std::string("../assets/sprites/Shapes/B_Slated.png"));
        } else if (m_DrawShapes == OverlayShapes::R_SLATED) {
            m_Image->SetImage(
                std::string("../assets/sprites/Shapes/R_Slated.png"));
        }
    }
    void setDrawCellLocation(std::vector<glm::vec2> cellcoords) {
        m_DrawCellLocation = cellcoords;
    }
    void Draw(const Util::Transform &trans, const float zindex) override {}

    void DrawUsingCamera(const Util::Transform &trans,
                         const float zindex) override {

        Util::Transform trans2 = trans;
        if (m_DrawShapes == OverlayShapes::B_BOXES ||
            m_DrawShapes == OverlayShapes::R_CROSS) {
            if (trans2.translation.x < 0) {
                trans2.translation =
                    glm::vec2(trans.translation.x - m_Image->GetSize().x / 2,
                              trans.translation.y + m_Image->GetSize().y / 2);
            } else {
                trans2.translation =
                    glm::vec2(trans.translation.x + m_Image->GetSize().x / 2,
                              trans.translation.y + m_Image->GetSize().y / 2);
            }

            m_Image->DrawUsingCamera(trans2, zindex);
        } else if (m_DrawShapes == OverlayShapes::B_SLATED ||
                   m_DrawShapes == OverlayShapes::R_SLATED) {
            trans2.translation = {0, 0};
            for (auto i : m_DrawCellLocation) {
                m_Image->DrawUsingCamera(trans2, zindex);
            }
        }
    }

private:
    std::vector<glm::vec2> m_DrawCellLocation;
    std::shared_ptr<Util::Image> m_Image;
    OverlayShapes m_DrawShapes;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DRAWOVERLAYS_HPP
