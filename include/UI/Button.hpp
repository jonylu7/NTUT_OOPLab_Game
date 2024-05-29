//
// Created by 盧威任 on 5/21/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_BUTTON_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_BUTTON_HPP
#include "Util/GameObject.hpp"
class Button : public Util::GameObject {
public:
    Button(const std::shared_ptr<Core::Drawable> &drawable, const float zIndex,
           const bool visible = true,
           const Util::Transform transfrom = Util::Transform())
        : GameObject(drawable, zIndex, visible, false, transfrom) {}
    ~Button() {}
    bool ifClicked() {
        if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {

            float maxy = m_Transform.translation.y +
                         (m_Drawable->GetSize().y * (m_Transform.scale.y)) / 2;
            float maxx = m_Transform.translation.x +
                         (m_Drawable->GetSize().x * (m_Transform.scale.x)) / 2;
            float minx = m_Transform.translation.x -
                         (m_Drawable->GetSize().x * (m_Transform.scale.x)) / 2;
            float miny = m_Transform.translation.y -
                         (m_Drawable->GetSize().y * (m_Transform.scale.y)) / 2;
            if ((Util::Input::GetCursorPosition().x <= maxx &&
                 Util::Input::GetCursorPosition().x >= minx) &&
                (Util::Input::GetCursorPosition().y <= maxy &&
                 Util::Input::GetCursorPosition().y >= miny)) {
                return true;
            }
        }
        return false;
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_BUTTON_HPP
