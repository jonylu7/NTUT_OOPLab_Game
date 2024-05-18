//
// Created by nudle on 2024/3/29.
//

#include "Avatar/Hunter.hpp"

void Hunter::customizeUpdate() {
    glm::vec2 targetCell = m_target->getMoving()->getCurrentCell();
    if (getDistance(targetCell) > ATTACK_RANGE - 1 &&
        lastTargetCell != m_target->getMoving()->getCurrentCell()) {
        //            glm::vec2 nextCell =
        //            getNextCellByCurrent(getDirByRelativeCells(getCurrentCell(),targetCell),getCurrentCell());

        lastTargetCell = m_target->getMoving()->getCurrentCell();
        //            setNewDestination(nextCell);
    } else if (getDistance(targetCell) < ATTACK_RANGE - 1) {
        lastTargetCell = getMoving()->getCurrentCell();
        attack(m_target);
    }
}
