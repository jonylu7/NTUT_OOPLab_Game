//
// Created by 盧威任 on 5/21/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_AIGROUPCOMMANDER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_AIGROUPCOMMANDER_HPP
#include "Avatar/Avatar.hpp"
#include "Mechanics/UnitManager.hpp"
#define GROUP_SIZE 4
#define AUTO_FIND_RANGE 4
#define AUTO_ATTACK_METHOD 2
class AIGroupCommander {
private:
    std::shared_ptr<UnitManager> m_PlayerUnitManager;
    std::shared_ptr<UnitManager> m_AIUnitManager;
    std::shared_ptr<AvatarManager> m_AIAvatarManager;
    std::shared_ptr<MapClass> m_Map;

    std::vector<std::vector<std::shared_ptr<Avatar>>> m_offensiveGroup;
    std::vector<std::shared_ptr<Avatar>> m_defensiveGroup;

public:
    AIGroupCommander(std::shared_ptr<UnitManager> PlayerUnitManager,
                     std::shared_ptr<UnitManager> AIUnitManager,
                     std::shared_ptr<MapClass> Map)
        : m_PlayerUnitManager(PlayerUnitManager),
          m_AIUnitManager(AIUnitManager),
          m_Map(Map){};
    ~AIGroupCommander(){};
    void Start() {
        m_AIAvatarManager = m_AIUnitManager->getAvatarManager();
        m_defensiveGroup = m_AIAvatarManager->getAvatarArray();
    }
    void Update() {
        updateDefensiveGroup();
        updateOffensiveGroup();
    }

    void setAllTroopToAttackMode() {
        if (m_defensiveGroup.empty()) {
            return;
        }
        for (auto i : m_defensiveGroup) {
            addTroopToOffensiveGroup(i);
        }
        m_defensiveGroup.clear();
    }
    void setTroopToAttackMode(int num) {
        if (m_defensiveGroup.empty()) {
            return;
        }
        int max = static_cast<int>(m_defensiveGroup.size());
        for (int i = max - 1; i >= 0 && num >= max - i; i--) {
            addTroopToOffensiveGroup(m_defensiveGroup[i]);
            m_defensiveGroup.pop_back();
        }
    }

    int getDefensiveTroopSize() {
        return static_cast<int>(m_defensiveGroup.size());
    }

    int getOffensiveTroopSize() {
        int totalSize = 0;
        for (const auto &row : m_offensiveGroup) {
            totalSize += static_cast<int>(row.size());
        }
        return totalSize;
    }

protected:
    void updateOffensiveGroup() {
        for (auto i : m_offensiveGroup) {
            for (int j = 0; j < static_cast<int>(i.size()); j++) {
                if (i[j]->getHealth()->ifDead()) {
                    i.erase(i.begin() + j);
                    j--;
                }
            }
        }
        updateOffensiveTroopAttackTarget();
    }
    void updateDefensiveGroup() {
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
    void addTroopToOffensiveGroup(std::shared_ptr<Avatar> unit) {
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
    void autoAttack(std::shared_ptr<Avatar> unit, int method) {
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
            if (targetCell.x == -1 && targetCell.y == -1) {
                return;
            }
            // attack
            m_AIAvatarManager->assignAttackOrderToAvatar(unit, targetCell,
                                                         HouseType::ENEMY);
            break;
        }
    }
    void updateOffensiveTroopAttackTarget() {
        for (int i = static_cast<int>(m_offensiveGroup.size()); i > 0; --i) {
            auto &currentGroup = m_offensiveGroup[i - 1];
            printf("(updateOffensiveTroopAttackTarget)groupSize : %d\n",
                   static_cast<int>(currentGroup.size()));
            if (!currentGroup.empty()) {
                if (!m_AIAvatarManager->ifAvatarHasNemesis(
                        currentGroup.front())) {
                    // find new target
                    glm::vec2 targetCell =
                        findTargetForOffensiveUnit(currentGroup.front());
                    if (targetCell.x == -1.f) {
                        printf(
                            "(updateOffensiveTroopAttackTarget) No Target\n");
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
                    glm::vec2 targetCell =
                        m_AIAvatarManager->getAvatarNemesisCell(
                            currentGroup.front());
                    printf("(updateOffensiveTroopAttackTarget)AvatarHasNemesis "
                           ": {%d,%d}\n",
                           static_cast<int>(targetCell.x),
                           static_cast<int>(targetCell.y));
                }
            } else {
                m_offensiveGroup.erase(m_offensiveGroup.begin() + i - 1);
            }
        }
    }

    glm::vec2 findTargetForOffensiveUnit(std::shared_ptr<Avatar> unit) {
        glm::vec2 targetCell = {-1.f, -1.f};
        // issue: empty group should delete before this
        if (false &&
            static_cast<int>(m_offensiveGroup.size()) >=
                static_cast<int>(m_PlayerUnitManager->getAvatarManager()
                                     ->getAvatarArray()
                                     .size())) {
            if (!m_PlayerUnitManager->getStructureManager()
                     ->getStructureArray()
                     ->getBuiltStructureArray()
                     .empty()) {
                targetCell = m_PlayerUnitManager->getStructureManager()
                                 ->getStructureArray()
                                 ->getBuiltStructureArray()
                                 .front()
                                 ->getCurrentLocationInCell();
            }
            for (auto i : m_PlayerUnitManager->getStructureManager()
                              ->getStructureArray()
                              ->getBuiltStructureArray()) {
                if (unit->getDistance(i->getCurrentLocationInCell()) <
                    unit->getDistance(targetCell)) {
                    // attack
                    targetCell = i->getCurrentLocationInCell();
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
                    targetCell = i->getCurrentLocationInCell();
                }
            }
        }
        printf("(findTargetForOffensiveUnit) TargetCell : {%d,%d}\n",
               targetCell.x, targetCell.y);
        return targetCell;
    }
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_AIGROUPCOMMANDER_HPP
