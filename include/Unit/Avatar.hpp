//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#include "Unit/AttackAndDamageUnit.hpp"
#include "Unit/FindValidPathToDest.hpp"
#include "Unit/PathfindingUnit.hpp"

class Avatar : public PathfindingUnit, public AttackAndDamageUnit {

    enum class UnitMode { DEAD, MOVE, IDLE, MOVE_ATTACK };


protected:
    std::shared_ptr<Util::Image> m_Image;

private:
    bool b_SelectedByCursor = true;
    bool b_justStarted = true;
    UnitMode m_currentMode;

public:
    Avatar(){};
    ~Avatar() override{};

    virtual void Start(glm::vec2 destination) { // destination = Barrack's
                                                // waypointLocation
        // setCurrentCell()  //CurrentCell = Structure's Location
        this->SetDrawable(
            customizeImage());
        SetVisible(true);
        m_grid.SetActivate(true);
        setCurrentCell(destination);
        setNextCell(destination);
        setNewDestination(getCurrentCell());

        setMovementSpeed(4);
    }
    virtual void aliveUpdate() {
        if (walkTowardNextCell() || b_justStarted) {
            b_justStarted = false;
            setCurrentCell(
                MapUtil::GlobalCoordToCellCoord(getCurrentLocation()));
            // setCurrentDir(m_wayPointUnit.getFirstCellDir());
            setNextCell(getNextCellByCurrent(getCurrentDir(), getNextCell()));
            printf("(aliveUpdate) getting new dir\n");
        }
        // m_wayPointUnit.Update();
        m_Transform.translation = getCurrentLocation();
        Draw();
        cursorSetNewDest();
        printf("-----------------------------\n");
    }
    virtual void customizeUpdate(){}
    virtual std::shared_ptr<Util::Image> customizeImage(){ return std::make_unique<Util::Image>("../assets/sprites/capybara.png");}
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
    void setNewDestination(glm::vec2 destination) {
        setDestinationCell(destination.x, destination.y);
    }
    void cursorSetNewDest() {
        if (b_SelectedByCursor &&
            Util::Input::IsKeyPressed(Util::Keycode::MOUSE_RB)) {
            this->setNewDestination(
                MapUtil::GlobalCoordToCellCoord(MapUtil::ScreenToGlobalCoord(
                    Util::Input::GetCursorPosition())));
        }
    }
    float getDistance(glm::vec2 cell){
        return sqrt(pow(cell.x-getCurrentCell().x,2)+pow(cell.y-getCurrentCell().y,2));
    }

    void DEBUG_printCurrentMoveDirection(MoveDirection Dir){
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
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
