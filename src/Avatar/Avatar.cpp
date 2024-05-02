//
// Created by 盧威任 on 4/28/24.
//

#include "Avatar/Avatar.hpp"

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

void Avatar::whenSelected() {
    if (b_Selected) {
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {
            m_DestinationCell = MapUtil::GlobalCoordToCellCoord(
                MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));
            b_NewDestinationIsSetted = true;
        }
    }
}

void Avatar::Update() {
    switch (m_LivingStatus) {
    case (LivingStatus::DEAD):
        SetVisible(false);
        break;

    case (LivingStatus::ALIVE):
        whenSelected();
        aliveUpdate();

        if (m_AvatarOrder == AvatarOrderType::MOVE_ATTACK) {
            // if nemesis is within weapon range
            // change move attack to
            // if nemesis is dead
        }

        break;
    }
}

void Avatar::aliveUpdate() {
    moveToNextCell();
    if (ifArrivedAtNextCell() || b_justStarted) {
        b_justStarted = false;
        // setCurrentCell(MapUtil::GlobalCoordToCellCoord(getCurrentLocation()));

        // setNextCell(
        //    PathUtility::getNextCellByCurrent(getCurrentDir(),
        //    getNextCell()));

        // printf("(aliveUpdate) getting new dir\n");
        if (m_MovePath.size() >= 1) {
            m_CurrentDir = m_MovePath.front();
            m_MovePath.pop_front();
        } else {
            m_CurrentDir = MoveDirection::IDLE;
        }
    }

    SetVisible(true);
    m_Transform.translation = m_CurrentLocation;

    Draw();
    //        m_SpriteSheetAnimation->Draw(m_Transform, DEFAULT_ZINDEX);

    printf("Avatar cell={%d,%d}\n", getCurrentLocation().x,
           getCurrentLocation().y);
    printf("-----------avatar------------------\n");
}

void Avatar::Start(glm::vec2 destination) { // destination = Barrack's
                                            // waypointLocation
    // setCurrentCell()  //CurrentCell = Structure's Location
    this->SetDrawable(customizeImage());
    //        setSpriteSheet();
    SetVisible(true);

    setMovementSpeed(4);
    m_AvatarOrder = AvatarOrderType::MOVE;
    m_Transform.scale = {1, 1};
}
