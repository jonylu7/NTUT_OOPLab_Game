//
// Created by nudle on 2024/3/28.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_RUNNER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_RUNNER_HPP
#include "Avatar.hpp"
#define ATTACK_RANGE 7

class Runner : public Avatar{
private:
    bool b_beingChase= false;

    std::shared_ptr<Avatar> m_hunter;
    glm::vec2 lastTargetCell;
    std::vector<MoveDirection> dictionary = {
        MoveDirection::UP,    MoveDirection::UP_RIGHT,
        MoveDirection::RIGHT, MoveDirection::DOWN_RIGHT,
        MoveDirection::DOWN,  MoveDirection::DOWN_LEFT,
        MoveDirection::LEFT,  MoveDirection::UP_LEFT};
    enum class runMode{REASONABLE,LIDL_RANDOM,FULL_RANDOM};
    int edgeCount=0;
public:
    void setBeingChase(std::shared_ptr<Avatar> hunter){
        b_beingChase=true;
        m_hunter=hunter;
        lastTargetCell=getCurrentCell();
    }
    std::shared_ptr<Util::Image> customizeImage()override{ return std::make_unique<Util::Image>("../assets/sprites/Runner.png");}
    void customizeUpdate() override{
        if(b_beingChase && m_hunter->getUnitMode()==UnitMode::ALIVE){
            glm::vec2 hunterCell = m_hunter->getCurrentCell();
            if(getDistance(hunterCell)<=ATTACK_RANGE-1 && lastTargetCell==getCurrentCell()){
                edgeCount=0;
                MoveDirection Dir = oppositeDir(getDirByRelativeCells(getCurrentCell(),hunterCell),runMode::LIDL_RANDOM);
                DEBUG_printCurrentMoveDirection(Dir);
                glm::vec2 nextCell = getNextCellByCurrentPlus3(Dir,getCurrentCell(),3,1);
                while(nextCell.x<0 || nextCell.y<0){
                    edgeCount+=rand() %2+1;
                    Dir=findNewDir(Dir,edgeCount);
                    DEBUG_printCurrentMoveDirection(Dir);
                    nextCell = getNextCellByCurrentPlus3(Dir,getCurrentCell(),1,3);
                }
                lastTargetCell=nextCell;
                setNewDestination(nextCell);

            }
        }else{
            b_beingChase=false;
        }
    }
    MoveDirection findNewDir(MoveDirection Dir,int edgeCount){
        for(int i=0;i<8;i++){
            if(dictionary[i]==Dir){
                int index = (i+edgeCount)%8;
                if(index<0){
                    index+=8;
                }
                return dictionary[index];
            }
        }
    }

    MoveDirection oppositeDir(MoveDirection Dir,runMode mode){
        switch (mode) {
        case (runMode::REASONABLE):{
            for(int i=0;i<8;i++){
                if(dictionary[i]==Dir){
                    if(i+3>7){
                        return dictionary[i+3-7];
                    }else{
                        return dictionary[i+3];
                    }
                }
            }
        }
        case runMode::LIDL_RANDOM:{
            for(int i=0;i<8;i++){
                if(dictionary[i]==Dir){
                    int index = i+3-7+rand()%3-1;
                    if(index<0){
                        return dictionary[index+8];
                    }else{
                        return dictionary[index];
                    }
                }
            }
        }
        case runMode::FULL_RANDOM:{
            return dictionary[rand()%8+0];
        }
        }
    }
    glm::vec2 getNextCellByCurrentPlus3(MoveDirection currentdir,
                                                    glm::vec2 currentcell,int n,int m) {
        switch (currentdir) {
        case MoveDirection::RIGHT: {
            currentcell = {currentcell.x + n, currentcell.y};
            break;
        }
        case MoveDirection::LEFT: {
            currentcell = {currentcell.x - n, currentcell.y};
            break;
        }
        case MoveDirection::UP: {
            currentcell = {currentcell.x, currentcell.y + n};
            break;
        }
        case MoveDirection::DOWN: {
            currentcell = {currentcell.x, currentcell.y - n};
            break;
        }
        case MoveDirection::UP_RIGHT: {
            currentcell = {currentcell.x + m, currentcell.y + m};
            break;
        }
        case MoveDirection::DOWN_LEFT: {
            currentcell = {currentcell.x - m, currentcell.y - m};
            break;
        }
        case MoveDirection::DOWN_RIGHT: {
            currentcell = {currentcell.x + m, currentcell.y - m};
            break;
        }
        case MoveDirection::UP_LEFT: {
            currentcell = {currentcell.x - m, currentcell.y + m};
            break;
        }
        case MoveDirection::IDLE: {
            printf("Direction debug didn't move\n");
            break;
        }
        }
        return currentcell;
    }

};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_RUNNER_HPP
