//
// Created by 盧威任 on 4/28/24.
//

#include "Avatar/Avatar.hpp"
#include "Map/MapUtility.hpp"
void Avatar::whenSelected() {
    // setAttackementVisible
}

void Avatar::Update() {
    DrawAvatar();
    if (getMoving()->ifMovePathEmpty()) {
        getAvatarOrder()->setAvatarOrder(AvatarOrderType::NO_ORDER);
    }
    switch (*m_Health->getLivingStatus()) {

    case (LivingStatus::DEAD):
        SetVisible(false);
        break;

    case (LivingStatus::ALIVE):
        SetVisible(true);
        whenSelected();

        if (getAvatarOrder()->getAvatarOrder() == AvatarOrderType::OPEN_FIRE) {
            // open fire
        } else if (getAvatarOrder()->getAvatarOrder() ==
                   AvatarOrderType::MOVE) {
            m_Moving->moveUpdate();
            if (getMoving()->getCurrentDir() == MoveDirection::IDLE) {
                getAvatarOrder()->setAvatarOrder(AvatarOrderType::NO_ORDER);
            }
        } else if (getAvatarOrder()->getAvatarOrder() ==
                   AvatarOrderType::CHASE) {
            m_Moving->moveUpdate();
            if (getMoving()->getCurrentDir() == MoveDirection::IDLE) {
                getAvatarOrder()->setAvatarOrder(AvatarOrderType::NO_ORDER);
            }
        }else if (getAvatarOrder()->getAvatarOrder() ==
                   AvatarOrderType::NO_ORDER) {
            noorderUpdate();
        } else if (getAvatarOrder()->getAvatarOrder() ==
                   AvatarOrderType::TAKEN_DAMAGE) {

            // takendamage
        } else if (getAvatarOrder()->getAvatarOrder() ==
                   AvatarOrderType::SPAWNED) {
            spawnedUpdate();
        }

        break;
    }
}

void Avatar::noorderUpdate() {
    getMoving()->setCurrentDir(MoveDirection::IDLE);
    m_Transform.translation = getMoving()->getCurrentLocation();
}

void Avatar::spawnedUpdate() {
    m_Transform.translation = getMoving()->getCurrentLocation();
}

void Avatar::Start(glm::vec2 spawnlocationcell) { // destination = Barrack's
                                                  // waypointLocation
    // setCurrentCell()  //CurrentCell = Structure's Location
    this->SetDrawable(customizeImage());
    //        setSpriteSheet();
    getMoving()->setMovementSpeed(4);
    getAvatarOrder()->setAvatarOrder(AvatarOrderType::SPAWNED);
    getMoving()->setCurrentLocation(
        MapUtil::CellCoordToGlobal(spawnlocationcell));
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

void Avatar::DrawAvatar() {
    m_Transform.translation = getMoving()->getCurrentLocation();

    if (getAvatarOrder()->getAvatarOrder() == AvatarOrderType::OPEN_FIRE) {
        this->SetDrawable(std::make_shared<Util::Image>(
            "../assets/sprites/mech_open_fire.png"));
    } else if (getAvatarOrder()->getAvatarOrder() ==
               AvatarOrderType::TAKEN_DAMAGE) {
        if (getHealth()->getHP() < 50) {
            this->SetDrawable(std::make_shared<Util::Image>(
                "../assets/sprites/mech_dead.png"));
        } else {
            this->SetDrawable(std::make_shared<Util::Image>(
                "../assets/sprites/mech_taken_damage.png"));
        }
    } else {
        this->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/mech_single.png"));
    }

    Draw();
}
