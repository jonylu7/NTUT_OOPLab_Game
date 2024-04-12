//
// Created by nudle on 2024/3/31.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TRUCK_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TRUCK_HPP
#include "Avatar.hpp"
#include "Ore.hpp"
#include "Player.hpp"
class Truck:public Avatar{
public:
    enum class truckMode{
        MOVE_TO_ORE,MINE,WAIT_FOR_NEXT_POINT,RETURN_TO_REFINERY
    };
private:
    std::shared_ptr<Ore> m_targetOre;
    std::shared_ptr<Ore> m_lastTargetOre;
    glm::vec2 m_SpawnPoint;
    truckMode m_currentTruckMode=truckMode::WAIT_FOR_NEXT_POINT;
    std::shared_ptr<Player> m_Player;
    int m_cargoQuantity=0;
    glm::vec2 lastTargetCell;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime;
public:
    Truck():Avatar(){m_LastTime=std::chrono::high_resolution_clock::now();}
    void importPlayer(std::shared_ptr<Player> player){m_Player=player;}
    truckMode getCurrentTruckMode(){return m_currentTruckMode;}
    void customizeStart() override{
        m_SpawnPoint=getCurrentCell();
        m_Transform.scale={0.1,0.1};
        m_currentMode = UnitMode::MOVE_ATTACK;
    }
    void setTargetOre(std::shared_ptr<Ore> target){m_targetOre=target;/*m_currentTruckMode=truckMode::MOVE_TO_ORE;*/} //Read from Map???
    std::shared_ptr<Util::Image> customizeImage()override{ return std::make_unique<Util::Image>("../assets/sprites/Truck.png");}
    void customizeUpdate() override{
        std::chrono::time_point<std::chrono::high_resolution_clock> m_currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> Elapsed = m_currentTime - m_LastTime;
        switch (m_currentTruckMode) {
        case truckMode::MOVE_TO_ORE:{
            if(m_targetOre.get() == nullptr){
                return;
            }
            glm::vec2 targetCell = m_targetOre->getCurrentCell();
            if(getDistance(targetCell)>1 && lastTargetCell!=m_targetOre->getCurrentCell()){
                setNewDestination(m_targetOre->getCurrentCell());
                lastTargetCell=m_targetOre->getCurrentCell();
            }
            else if(getDistance(targetCell)<=1 ){
                setNewDestination(getCurrentCell());
                m_lastTargetOre=m_targetOre;
                m_currentTruckMode=truckMode::MINE;
            }
            break;
        }
        case truckMode::MINE:{
            if(Elapsed.count()>=1){
                mine(m_targetOre);
                m_LastTime=m_currentTime;
            }
            break;
            //if currentCell == spawnpoint :(orerefinery) add money,truck->setCurrentTruckMode=MOVE_TO_ORE
        }
        case truckMode::RETURN_TO_REFINERY:{
            setNewDestination(m_SpawnPoint);
            if(getCurrentCell()==m_SpawnPoint){
                m_Player->addCurrency(m_cargoQuantity);
                m_currentTruckMode=truckMode::MOVE_TO_ORE;
            }
            break;
        }
        case truckMode::WAIT_FOR_NEXT_POINT:{
            if(m_lastTargetOre!=m_targetOre){
                m_currentTruckMode=truckMode::MOVE_TO_ORE;
            }
            break;
        }
        }
    }

    void mine(std::shared_ptr<Ore> attackTarget){
        if(attackTarget->getUnitMode()==UnitMode::DEAD){
            m_currentTruckMode=truckMode::WAIT_FOR_NEXT_POINT;
        }else{
            attackTarget->beingMined(20);
            m_cargoQuantity+=20;
            if(m_cargoQuantity>=100){
                m_currentTruckMode=truckMode::RETURN_TO_REFINERY;
            }
        }
    };
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TRUCK_HPP
