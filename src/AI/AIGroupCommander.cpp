//
// Created by 盧威任 on 6/17/24.
//
#include "AI/AIGroupCommander.hpp"

glm::vec2
AIGroupCommander::findTargetForOffensiveUnit(std::shared_ptr<Avatar> unit) {
    glm::vec2 targetCell = {-10.f, -10.f};
    // issue: empty group should delete before this
    if (static_cast<int>(m_offensiveGroup.size()) >=
            static_cast<int>(m_PlayerUnitManager->getAvatarManager()
                                 ->getAvatarArray()
                                 .size()) &&
        !m_PlayerUnitManager->getStructureManager()
             ->getStructureArray()
             ->getBuiltStructureArray()
             .empty()) {
        if (!m_PlayerUnitManager->getStructureManager()
                 ->getStructureArray()
                 ->getBuiltStructureArray()
                 .empty()) {
            targetCell = m_PlayerUnitManager->getStructureManager()
                             ->getStructureArray()
                             ->getBuiltStructureArray()
                             .front()
                             ->getTopRightCell();
        } else {
            return targetCell;
        }
        for (auto i : m_PlayerUnitManager->getStructureManager()
                          ->getStructureArray()
                          ->getBuiltStructureArray()) {
            if (unit->getDistance(i->getTopRightCell()) <
                unit->getDistance(targetCell)) {
                targetCell = i->getTopRightCell();
            }
        }
    } else {
        if (!m_PlayerUnitManager->getAvatarManager()
                 ->getAvatarArray()
                 .empty()) {
            targetCell = m_PlayerUnitManager->getAvatarManager()
                             ->getAvatarArray()
                             .front()
                             ->getCurrentLocationInCell();
        }
        for (auto i :
             m_PlayerUnitManager->getAvatarManager()->getAvatarArray()) {
            if (i->getDistance(unit->getCurrentLocationInCell()) <
                unit->getDistance(targetCell)) {
                // attack
                if (m_Map->getTileByCellPosition(targetCell)
                        ->getAvatars()
                        .size() > 0) {
                    if (m_AIAvatarManager->ifAvatarHasNemesis(
                            m_Map->getTileByCellPosition(targetCell)
                                ->getAvatars()
                                .front())) {
                        continue;
                    }
                }
                targetCell = i->getCurrentLocationInCell();
            }
        }
    }
    printf("(findTargetForOffensiveUnit) TargetCell : {%d,%d}\n", targetCell.x,
           targetCell.y);
    return targetCell;
}

void AIGroupCommander::updateOffensiveTroopAttackTarget() {
    for (int i = 0; i < static_cast<int>(m_offensiveGroup.size()); i++) {
        auto &currentGroup = m_offensiveGroup[i];
        printf("(updateOffensiveTroopAttackTarget)groupSize : %d\n",
               static_cast<int>(currentGroup.size()));
        if (!currentGroup.empty()) {
            if (!m_AIAvatarManager->ifAvatarHasNemesis(currentGroup.front())) {
                // find new target
                glm::vec2 targetCell =
                    findTargetForOffensiveUnit(currentGroup.front());
                if (targetCell.x < 0) {
                    printf("(updateOffensiveTroopAttackTarget) No Target\n");
                    break;
                }
                // attack
                for (int j = 0; j < static_cast<int>(currentGroup.size());
                     j++) {
                    if (currentGroup[j]->getHealth()->ifDead()) {
                        currentGroup.erase(currentGroup.begin() + j);
                        j--;
                    } else {
                        m_AIAvatarManager->assignAttackOrderToAvatar(
                            currentGroup[j], targetCell, HouseType::ENEMY);
                    }
                }
            } else {
                glm::vec2 targetCell = m_AIAvatarManager->getAvatarNemesisCell(
                    currentGroup.front());
                printf("(updateOffensiveTroopAttackTarget)AvatarHasNemesis "
                       ": {%d,%d}\n",
                       static_cast<int>(targetCell.x),
                       static_cast<int>(targetCell.y));
            }
        } else {
            m_offensiveGroup.erase(m_offensiveGroup.begin() + i);
        }
    }
}

void AIGroupCommander::autoAttack(std::shared_ptr<Avatar> unit, int method) {
    switch (method) {
    case 1:
        for (auto i :
             m_PlayerUnitManager->getAvatarManager()->getAvatarArray()) {
            if (i->getDistance(unit->getCurrentLocationInCell()) <=
                AUTO_FIND_RANGE) {
                // attack
                m_AIAvatarManager->assignAttackOrderToAvatar(
                    unit, i->getCurrentLocationInCell(), HouseType::ENEMY);
                return;
            }
        }
        break;
    case 2:
        glm::vec2 targetCell = m_Map->findEnemyInRange(
            AUTO_FIND_RANGE, unit->getCurrentLocationInCell(),
            HouseType::ENEMY);
        if (targetCell.x < 0) {
            return;
        }
        // attack
        m_AIAvatarManager->assignAttackOrderToAvatar(unit, targetCell,
                                                     HouseType::ENEMY);
        break;
    }
}

void AIGroupCommander::addTroopToOffensiveGroup(std::shared_ptr<Avatar> unit) {
    auto it =
        std::find_if(m_offensiveGroup.begin(), m_offensiveGroup.end(),
                     [](const std::vector<std::shared_ptr<Avatar>> &group) {
                         return group.size() < GROUP_SIZE;
                     });
    unit->setAIType(AI_Type::ATTACK);
    if (it != m_offensiveGroup.end()) {
        it->push_back(unit);
    } else {
        m_offensiveGroup.push_back(std::vector<std::shared_ptr<Avatar>>());
        m_offensiveGroup.back().push_back(unit);
    }
}

void AIGroupCommander::updateDefensiveGroup() {
    for (int i = 0; i < static_cast<int>(m_defensiveGroup.size()); i++) {
        if (m_defensiveGroup[i]->getHealth()->ifDead()) {
            m_defensiveGroup.erase(m_defensiveGroup.begin() + i);
            i--;
        } else {
            autoAttack(m_defensiveGroup[i], AUTO_ATTACK_METHOD);
        };
    }
    std::vector<std::shared_ptr<Avatar>> temp =
        m_AIAvatarManager->getAvatarArray();
    for (int i = static_cast<int>(temp.size()) - 1; i >= 0; i--) {
        if (temp[i]->getAIType() == AI_Type::NONE) {
            temp[i]->setAIType(AI_Type::DEFENCE);
            m_defensiveGroup.push_back(temp[i]);
        }
    }
}
