//
// Created by 盧威任 on 1/30/24.
//

#include "Infantry.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Text.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include "config.hpp"

float CalculateDistance(glm::vec2 d1,glm::vec2 d2){
    return pow(pow(d2.x-d1.x,2)+pow(d2.y-d1.y,2),0.5);
}

float MoveToDestination(glm::vec2 Destination){
    //moving destination
    //crash and find algorithm

}

void Infantry::Update([[maybe_unused]] const Util::Transform &transform) {
    static glm::vec2 dir = {1, 0.5};

    auto &pos = m_Transform.translation;

    if (pos.y > WINDOW_HEIGHT || pos.y + WINDOW_HEIGHT < 0) {
        dir.y *= -1;
    }
    if (pos.x > WINDOW_WIDTH || pos.x + WINDOW_WIDTH < 0) {
        dir.x *= -1;
    }

    auto delta = static_cast<float>(Util::Time::GetDeltaTime());
    switch (m_CurrentState) {
case(updateMode::Uncreated):
        break;
    case(updateMode::MovingToDestination):
        if(pos==Destination){
            updateMode::Standing;
        }else{
            float dis=CalculateDistance(pos,Destination);
        }
        m_Drawable->Draw(m_Transform, m_ZIndex);
        break;
    case(updateMode::Attacking):
        pos = ObjectLocation;
        m_Drawable->Draw(m_Transform, m_ZIndex);
        break;
    }



    // LOG_DEBUG("GIRA: x: {}, y: {}", pos.x, pos.y);
}



