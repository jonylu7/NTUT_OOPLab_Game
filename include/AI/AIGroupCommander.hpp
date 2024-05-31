//
// Created by 盧威任 on 5/21/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_AIGROUPCOMMANDER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_AIGROUPCOMMANDER_HPP
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
    AIGroupCommander(std::shared_ptr<UnitManager> PlayerUnitManager,std::shared_ptr<UnitManager> AIUnitManager,std::shared_ptr<MapClass> Map):m_PlayerUnitManager(PlayerUnitManager),m_AIUnitManager(AIUnitManager),m_Map(Map){};
    ~AIGroupCommander(){};
    void Start(){
        m_AIAvatarManager = m_AIUnitManager->getAvatarManager();
        m_defensiveGroup = m_AIAvatarManager->getAvatarArray();
    }
    void Update(){
        updateDefensiveGroup();
        updateOffensiveGroup();
    }


    void setAllTroopToAttackMode(){
        for(auto i : m_defensiveGroup){
            addTroopToOffensiveGroup(i);
        }
        m_defensiveGroup.clear();
    }
    void setTroopToAttackMode(int num){
        int max  =  static_cast<int>(m_defensiveGroup.size());
        for(int i=max-1;i>=0 && num>=max-i;i--){
            addTroopToOffensiveGroup(m_defensiveGroup[i]);
            m_defensiveGroup.pop_back();
        }
    }

    int getDefensiveTroopSize(){
        return static_cast<int>(m_defensiveGroup.size());
    }

    int getOffensiveTroopSize(){
        int totalSize = 0;
        for (const auto& row : m_offensiveGroup) {
            totalSize += static_cast<int>(row.size());
        }
        return totalSize;
    }
protected:
    void updateOffensiveGroup(){
        for(auto i : m_offensiveGroup){
            for(int j=0;j<static_cast<int>(i.size());j++){
                if(i[j]->getHealth()->ifDead()){
                    i.erase(i.begin()+j);
                }
            }
        }
        updateOffensiveTroopAttackTarget();
    }
    void updateDefensiveGroup(){
        int t=0;
        for(auto i : m_defensiveGroup){
            if(i->getHealth()->ifDead()){
                m_defensiveGroup.erase(m_defensiveGroup.begin()+t);
            }else{
                autoAttack(i,AUTO_ATTACK_METHOD);
            };
            t++;
        }
        std::vector<std::shared_ptr<Avatar>> temp = m_AIAvatarManager->getAvatarArray();
        for(int i=static_cast<int>(temp.size());i>=0;i--){
            if(temp[i]->getAIType()==AI_Type::NONE){
                temp[i]->setAIType(AI_Type::DEFENCE);
                m_defensiveGroup.push_back(temp[i]);
            }else{
                break;
            }
        }
    }
    void addTroopToOffensiveGroup(std::shared_ptr<Avatar> unit){
        auto it = std::find_if(m_offensiveGroup.begin(), m_offensiveGroup.end(), [](const std::vector<std::shared_ptr<Avatar>>& group) {
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
    void autoAttack(std::shared_ptr<Avatar> unit,int method){
        switch (method) {
        case 1:
            for(auto i : m_PlayerUnitManager->getAvatarManager()->getAvatarArray()){
                if(i->getDistance(unit->getCurrentLocationInCell())<=AUTO_FIND_RANGE){
                    //attack
                    m_AIAvatarManager->assignAttackOrderToAvatar(unit,i->getCurrentLocationInCell());
                    return;
                }
            }
            break;
        case 2:
            glm::vec2 targetCell = m_Map->findEnemyInRange(AUTO_FIND_RANGE,unit->getCurrentLocationInCell(),HouseType::ENEMY);
            if(targetCell.x == -1 && targetCell.y == -1){
                return;
            }
            //attack
            m_AIAvatarManager->assignAttackOrderToAvatar(unit,targetCell);
            break;
        }
    }
    void updateOffensiveTroopAttackTarget(){
        for(auto i : m_offensiveGroup){
            if(i.size()>0){
                if (m_AIAvatarManager->ifAvatarHasNemesis(i.front())){
                    // find new target
                    glm::vec2 targetCell = m_Map->findEnemyInRange(
                        100, i.front()->getCurrentLocationInCell(),
                        HouseType::ENEMY);
                    if (targetCell.x == -1 && targetCell.y == -1) {
                        return;
                    }
                    // attack
                    for (auto j : i) {
                        m_AIAvatarManager->assignAttackOrderToAvatar(
                            j, targetCell);
                    }
                }
            }
        }
    }
};



#endif // PRACTICALTOOLSFORSIMPLEDESIGN_AIGROUPCOMMANDER_HPP
