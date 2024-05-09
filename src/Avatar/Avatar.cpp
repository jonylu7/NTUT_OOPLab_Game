//
// Created by 盧威任 on 4/28/24.
//

#include "Avatar/Avatar.hpp"
#include "Map/MapUtility.hpp"
void Avatar::whenSelected() {
    // setAttackementVisible
}

void Avatar::Update() {
    switch (*m_Health->getLivingStatus()) {
    case (LivingStatus::DEAD):
        SetVisible(false);
        break;

    case (LivingStatus::ALIVE):
        whenSelected();

        if (m_AvatarOrder == AvatarOrderType::OPEN_FIRE) {

        } else if (m_AvatarOrder == AvatarOrderType::MOVE) {
            moveUpdate();
        } else if (m_AvatarOrder == AvatarOrderType::NO_ORDER) {
            noOrderUpdate();
        } else if (m_AvatarOrder == AvatarOrderType::TAKEN_DAMAGE) {
        } else if (m_AvatarOrder == AvatarOrderType::SPAWNED) {
            spawnedUpdate();
        }

        break;
    }
}

void Avatar::noOrderUpdate() {
    m_CurrentDir = MoveDirection::IDLE;
    SetVisible(true);
    m_Transform.translation = getCurrentLocation();

    Draw();
}

void Avatar::spawnedUpdate() {
    SetVisible(true);
    m_Transform.translation = getCurrentLocation();

    Draw();
}
void Avatar::moveUpdate() {

    if (ifArrivedAtNextCell()) {
        m_PrevCell = getCurrentCell();
        if (!m_MovePath.empty()) {
            m_CurrentDir = m_MovePath.front();
            m_MovePath.pop_front();
        } else {
            m_CurrentDir = MoveDirection::IDLE;
            m_AvatarOrder = AvatarOrderType::NO_ORDER;
        }
    }
    moveToNextCell();

    SetVisible(true);
    m_Transform.translation = getCurrentLocation();

    Draw();
}

void Avatar::Start(glm::vec2 spawnlocationcell) { // destination = Barrack's
                                                  // waypointLocation
    // setCurrentCell()  //CurrentCell = Structure's Location
    this->SetDrawable(customizeImage());
    //        setSpriteSheet();
    SetVisible(true);
    setMovementSpeed(4);
    m_AvatarOrder = AvatarOrderType::SPAWNED;
    m_CurrentLocation = MapUtil::CellCoordToGlobal(spawnlocationcell);
    m_Transform.scale = {1, 1};
    getHealth()->setLivingStatus(
        std::make_shared<LivingStatus>(LivingStatus::ALIVE));
}

void Avatar::deadUpdate() {}

void Avatar::DEBUG_printCurrentMoveDirection(MoveDirection Dir) {
    switch (Dir) {
    case MoveDirection::RIGHT: {
        printf("(DEBUG)Avatar DIR:Right\n");
        break;
    }
    case MoveDirection::LEFT: {
        printf("(DEBUG)Avatar DIR:Left\n");
        break;
    }
    case MoveDirection::UP: {
        printf("(DEBUG)Avatar DIR:Up\n");
        break;
    }
    case MoveDirection::DOWN: {
        printf("(DEBUG)Avatar DIR:Down\n");
        break;
    }
    case MoveDirection::UP_RIGHT: {
        printf("(DEBUG)Avatar DIR:Up_Right\n");
        break;
    }
    case MoveDirection::DOWN_LEFT: {
        printf("(DEBUG)Avatar DIR:Down_Left\n");
        break;
    }
    case MoveDirection::DOWN_RIGHT: {
        printf("(DEBUG)Avatar DIR:Down_Right\n");
        break;
    }
    case MoveDirection::UP_LEFT: {
        printf("(DEBUG)Avatar DIR:Up_Left\n");
        break;
    }
    case MoveDirection::IDLE: {
        printf("(DEBUG)Avatar DIR:IDLE\n");
        break;
    }
    }
}
