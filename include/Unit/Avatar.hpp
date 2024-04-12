//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP

#include "Map/MapUtility.hpp"
#include "PathfindingUnit.hpp"
#include "Unit/AttackAndDamageUnit.hpp"

class Avatar : public PathfindingUnit,
               public AttackAndDamageUnit,
               public Util::GameObject,
               public Selectable {

public:
    enum class UnitMode { DEAD, MOVE, IDLE, MOVE_ATTACK, ALIVE };
    Avatar(){};
    ~Avatar() override{};

    virtual void Start(glm::vec2 destination) { // destination = Barrack's
                                                // waypointLocation
        // setCurrentCell()  //CurrentCell = Structure's Location
        this->SetDrawable(customizeImage());
        SetVisible(true);
        setCurrentCell(destination);
        setNextCell(destination);

        setMovementSpeed(4);
        customizeStart();
    }
    virtual void customizeStart(){};

    virtual void aliveUpdate() {
        if (walkTowardNextCell() || b_justStarted) {
            b_justStarted = false;
            setCurrentCell(
                MapUtil::GlobalCoordToCellCoord(getCurrentLocation()));
            // setCurrentDir(m_wayPointUnit.getFirstCellDir());
            setNextCell(PathUtility::getNextCellByCurrent(getCurrentDir(),
                                                          getNextCell()));
            printf("(aliveUpdate) getting new dir\n");
        }
        // m_wayPointUnit.Update();
        m_Transform.translation = getCurrentLocation();
        Draw();
        printf("-----------------------------\n");
    }

    float getDistance(glm::vec2 cell) {
        return sqrt(pow(cell.x - getCurrentCell().x, 2) +
                    pow(cell.y - getCurrentCell().y, 2));
    }

    void DEBUG_printCurrentMoveDirection(MoveDirection Dir) {
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

    UnitMode getUnitMode() { return m_currentMode; }
    virtual void customizeUpdate() {
        if (1 == 1) {
        }
    }

    virtual std::shared_ptr<Util::Image> customizeImage() {
        return std::make_unique<Util::Image>("../assets/sprites/capybara.png");
    }
    virtual void Update() override {
        switch (m_currentMode) {
        case (UnitMode::DEAD): {
            SetVisible(false);
        }
        case (UnitMode::MOVE): {
            aliveUpdate();
        }
        case (UnitMode::MOVE_ATTACK): {
            aliveUpdate();
            customizeUpdate();
        }
            // attack
        }
    }

protected:
    std::shared_ptr<Util::Image> m_Image;

private:
    bool b_SelectedByCursor = true;
    bool b_justStarted = true;
    UnitMode m_currentMode;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
