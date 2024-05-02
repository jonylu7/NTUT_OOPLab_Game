#include "Util/GameObject.hpp"

namespace Util {

void GameObject::Draw() {
    if (!m_Visible) {
        return;
    }
    if (b_MovingRelativeToCamera) {
        m_Drawable->DrawUsingCamera(m_Transform, m_ZIndex);
    } else {
        m_Drawable->Draw(m_Transform, m_ZIndex);
    }
}

} // namespace Util
