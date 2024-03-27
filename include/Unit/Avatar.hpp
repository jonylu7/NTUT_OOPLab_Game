//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#include "Unit/AttackAndDamageUnit.hpp"
#include "Unit/FindValidPathToDest.hpp"
#include "Unit/PathfindingUnit.hpp"

class Avatar : public PathfindingUnit, public AttackAndDamageUnit {
private:
    FindValidPathToDest m_wayPointUnit;
    bool b_SelectedByCursor = true;
    bool b_justStarted = true;

public:
    Avatar(){};
    ~Avatar() override{};

    virtual void
    Start(glm::vec2 destination,
          std::shared_ptr<MapClass> map) { // destination = Barrack's
                                           // waypointLocation
        // setCurrentCell()  //CurrentCell = Structure's Location
        this->SetDrawable(
            std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
        SetVisible(true);
        m_grid.SetActivate(true);
        m_wayPointUnit.Start(map);
        setCurrentCell(destination);
        setNextCell(destination);
        m_wayPointUnit.setCurrentCell(destination);
        m_wayPointUnit.setNextCell(destination);
        setNewDestination(getCurrentCell());

        setMovementSpeed(4);
    }
    virtual void aliveUpdate() {
        if (walkTowardNextCell() || b_justStarted) {
            b_justStarted = false;
            setCurrentCell(
                MapUtil::GlobalCoordToCellCoord(getCurrentLocation()));
            setCurrentDir(m_wayPointUnit.getFirstCellDir());
            setNextCell(getNextCellByCurrent(getCurrentDir(), getNextCell()));
            printf("(aliveUpdate) getting new dir\n");
        }
        m_wayPointUnit.Update();
        m_Transform.translation = getCurrentLocation();
        Draw();
        cursorSetNewDest();
        printf("-----------------------------\n");
    }
    virtual void Update() override {
        switch (m_currentMode) {
        case (UnitMode::DEAD): {
            SetVisible(false);
        }
        case (UnitMode::ALIVE): {
            aliveUpdate();
        }
        }
    }
    void setNewDestination(glm::vec2 destination) {
        setDestinationCell(destination.x, destination.y);
        m_wayPointUnit.resetQueue();
        m_wayPointUnit.setCurrentCell(getNextCell());
        m_wayPointUnit.setNextCell(getNextCell());
        m_wayPointUnit.findPath(getDestinationCell());
    }
    void cursorSetNewDest() {
        if (b_SelectedByCursor &&
            Util::Input::IsKeyPressed(Util::Keycode::MOUSE_RB)) {
            this->setNewDestination(
                MapUtil::GlobalCoordToCellCoord(MapUtil::ScreenToGlobalCoord(
                    Util::Input::GetCursorPosition())));
        }
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
