//
// Created by nudle on 2024/3/28.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_HUNTER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_HUNTER_HPP
#include "Avatar.hpp"
#include "Runner.hpp"

#define ATTACK_RANGE 7

class Hunter:public Avatar{
private:
    std::shared_ptr<Runner> m_target;
    glm::vec2 lastTargetCell;

public:
    void setTarget(std::shared_ptr<Runner> target){
        m_target=target;
    }
    std::shared_ptr<Util::Image> customizeImage()override{ return std::make_unique<Util::Image>("../assets/sprites/Hunter.png");}
    void customizeUpdate() override{
        glm::vec2 targetCell = m_target->getCurrentCell();
        if(getDistance(targetCell)>ATTACK_RANGE-1 && lastTargetCell!=m_target->getCurrentCell()){
//            glm::vec2 nextCell = getNextCellByCurrent(getDirByRelativeCells(getCurrentCell(),targetCell),getCurrentCell());
            setNewDestination(m_target->getCurrentCell());
            lastTargetCell=m_target->getCurrentCell();
//            setNewDestination(nextCell);
        }
        else if(getDistance(targetCell)<ATTACK_RANGE-1 ){
            setNewDestination(getCurrentCell());
            lastTargetCell=getCurrentCell();
            attack(m_target);
        }
    }
    void attack(std::shared_ptr<Avatar> attackTarget){};
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_HUNTER_HPP
