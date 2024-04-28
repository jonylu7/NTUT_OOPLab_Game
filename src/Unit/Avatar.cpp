//
// Created by 盧威任 on 4/28/24.
//

#include "Unit/Avatar.hpp"

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
            m_destinationCell = MapUtil::GlobalCoordToCellCoord(
                MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));
            b_newDestinationIsSetted = true;
        }
    }
}

void Avatar::Update() {
    whenSelected();
    switch (m_currentMode) {
    case (UnitMode::DEAD): {
        SetVisible(false);
        break;
    }
    case (UnitMode::MOVE): {
        aliveUpdate();
        break;
    }
    case (UnitMode::MOVE_ATTACK): {
        aliveUpdate();
        customizeUpdate();
        break;
    }
        // attack
    }
}

void Avatar::aliveUpdate() {
    if (arrivedAtNextCell() || b_justStarted) {
        walkTowardNextCell();
        b_justStarted = false;
        setCurrentCell(MapUtil::GlobalCoordToCellCoord(getCurrentLocation()));
        // setCurrentDir(m_wayPointUnit.getFirstCellDir());
        setNextCell(
            PathUtility::getNextCellByCurrent(getCurrentDir(), getNextCell()));
        // printf("(aliveUpdate) getting new dir\n");
        if (m_movepath.size() >= 1) {
            m_currentDir = m_movepath.front();
            m_movepath.pop_front();
        } else {
            m_currentDir = MoveDirection::IDLE;
        }
    }
    // m_wayPointUnit.Update();

    SetVisible(true);
    m_Transform.translation = getCurrentLocation();

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
    setCurrentCell(destination);
    setNextCell(destination);

    setMovementSpeed(4);
    m_currentMode = UnitMode::MOVE;
    m_Transform.scale = {1, 1};
}
