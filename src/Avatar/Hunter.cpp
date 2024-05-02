//
// Created by nudle on 2024/3/29.
//

#include "Avatar/Hunter.hpp"

void Hunter::customizeUpdate() {
    glm::vec2 targetCell = m_target->getCurrentCell();
    if (getDistance(targetCell) > ATTACK_RANGE - 1 &&
        lastTargetCell != m_target->getCurrentCell()) {
        //            glm::vec2 nextCell =
        //            getNextCellByCurrent(getDirByRelativeCells(getCurrentCell(),targetCell),getCurrentCell());
        setDestinationCell(m_target->getCurrentCell());
        lastTargetCell = m_target->getCurrentCell();
        //            setNewDestination(nextCell);
    } else if (getDistance(targetCell) < ATTACK_RANGE - 1) {
        setDestinationCell(getCurrentCell());
        lastTargetCell = getCurrentCell();
        attack(m_target);
    }
}
