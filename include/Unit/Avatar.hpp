//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#include "FindValidPathToDest.hpp"
#include "PathfindingUnit.hpp"
#include "Unit/AttackAndDamageUnit.hpp"

class Avatar : public PathfindingUnit,
               public AttackAndDamageUnit,
               public Util::GameObject {
    enum class UnitMode { DEAD, MOVE, IDLE, MOVE_ATTACK };

private:
    bool b_SelectedByCursor = true;
    bool b_justStarted = true;

public:
    Avatar(){};
    ~Avatar() override{};

    virtual void Start(glm::vec2 destination) { // destination = Barrack's
                                                // waypointLocation
        // setCurrentCell()  //CurrentCell = Structure's Location
        this->SetDrawable(
            std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
        SetVisible(true);
        setCurrentCell(destination);
        setNextCell(destination);

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
        printf("-----------------------------\n");
    }
    virtual void Update() override {
        switch (m_currentMode) {
        case (UnitMode::DEAD): {
            SetVisible(false);
        }
        case (UnitMode::MOVE): {
            aliveUpdate();
        }
            // attack
        }
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
