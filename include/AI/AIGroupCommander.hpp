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
    void updateDefensiveGroup();
    void addTroopToOffensiveGroup(std::shared_ptr<Avatar> unit);
    void autoAttack(std::shared_ptr<Avatar> unit, int method);
    void updateOffensiveTroopAttackTarget();

    glm::vec2 findTargetForOffensiveUnit(std::shared_ptr<Avatar> unit);
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_AIGROUPCOMMANDER_HPP
