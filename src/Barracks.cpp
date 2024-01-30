//
// Created by 盧威任 on 1/28/24.
//
#include "Barracks.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Text.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include "Util/Input.hpp"
#include "config.hpp"

void Barracks::Update([[maybe_unused]] const Util::Transform &transform) {
    static glm::vec2 dir = {1, 0.5};

    auto &pos = m_Transform.translation;

    if (pos.y > WINDOW_HEIGHT || pos.y + WINDOW_HEIGHT < 0) {
        dir.y *= -1;
    }
    if (pos.x > WINDOW_WIDTH || pos.x + WINDOW_WIDTH < 0) {
        dir.x *= -1;
    }

    auto delta = static_cast<float>(Util::Time::GetDeltaTime());

    Util::Transform tras{Util::Input::GetCursorPosition()};

    pos =tras.translation;

    m_Drawable->Draw(m_Transform, m_ZIndex);
    for (auto &child : m_Children) {
        child->Update(tras);
    }

    // LOG_DEBUG("GIRA: x: {}, y: {}", pos.x, pos.y);
}