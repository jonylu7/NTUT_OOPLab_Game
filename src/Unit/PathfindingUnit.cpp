//
// Created by nudle on 2024/3/15.
//
#include "Unit/PathfindingUnit.hpp"
void PathfindingUnit::UpdateNextCell(){
    switch (m_currentDir) {
    case MoveDirection::RIGHT:{
        m_nextCell={m_nextCell.x+1,m_nextCell.y};
        break;
    }
    case MoveDirection::LEFT:{
        m_nextCell={m_nextCell.x-1,m_nextCell.y};
        break;
    }
    case MoveDirection::UP:{
        m_nextCell={m_nextCell.x,m_nextCell.y+1};
        break;
    }
    case MoveDirection::DOWN:{
        m_nextCell={m_nextCell.x,m_nextCell.y-1};
        break;
    }
    case MoveDirection::UP_RIGHT:{
        m_nextCell={m_nextCell.x+1,m_nextCell.y+1};
        break;
    }
    case MoveDirection::DOWN_LEFT:{
        m_nextCell={m_nextCell.x-1,m_nextCell.y-1};
        break;
    }
    case MoveDirection::DOWN_RIGHT:{
        m_nextCell={m_nextCell.x+1,m_nextCell.y-1};
        break;
    }
    case MoveDirection::UP_LEFT:{
        m_nextCell={m_nextCell.x-1,m_nextCell.y+1};
        break;
    }
    case MoveDirection::IDLE:{
        printf("Direction debug didn't move\n");
        break;
    }
    }

}


bool PathfindingUnit::UpdateNextCell(int* times){
    switch (m_currentDir) {
    case MoveDirection::RIGHT:{
        m_nextCell={m_nextCell.x+1,m_nextCell.y};
        break;
    }
    case MoveDirection::LEFT:{
        m_nextCell={m_nextCell.x-1,m_nextCell.y};
        break;
    }
    case MoveDirection::UP:{
        m_nextCell={m_nextCell.x,m_nextCell.y+1};
        break;
    }
    case MoveDirection::DOWN:{
        m_nextCell={m_nextCell.x,m_nextCell.y-1};
        break;
    }
    case MoveDirection::UP_RIGHT:{
        m_nextCell={m_nextCell.x+1,m_nextCell.y+1};
        break;
    }
    case MoveDirection::DOWN_LEFT:{
        m_nextCell={m_nextCell.x-1,m_nextCell.y-1};
        break;
    }
    case MoveDirection::DOWN_RIGHT:{
        m_nextCell={m_nextCell.x+1,m_nextCell.y-1};
        break;
    }
    case MoveDirection::UP_LEFT:{
        m_nextCell={m_nextCell.x-1,m_nextCell.y+1};
        break;
    }
    case MoveDirection::IDLE:{
        printf("Direction debug didn't move\n");
        break;
    }
    }
    if(false){//not walkable
        times+=1;
        return true;    //Dir.pop_back
    }else{
        return false;
    }

}
void PathfindingUnit::findNextCellDir() {
    int targetCellX = m_targetCell.x;
    int targetCellY = m_targetCell.y;
    int currCellX=m_currentCell.x;
    int currCellY=m_currentCell.y;
    printf("(findNextCellDir)Cell now :{%.d,%.d}\n(find)Cell target : {%.d,%.d}\n",currCellX,currCellY,targetCellX,targetCellY);
    if (targetCellX == currCellX && targetCellY == currCellY) {
        m_currentDir = MoveDirection::IDLE;
        printf("(findNextCellDir)Current direction: IDLE\n");
    } else if (targetCellY == currCellY) {
        if (targetCellX > currCellX) {
            m_currentDir = MoveDirection::RIGHT;
            printf("(findNextCellDir)Current direction: RIGHT\n");
        } else if (targetCellX < currCellX) {
            m_currentDir = MoveDirection::LEFT;
            printf("(findNextCellDir)Current direction: LEFT\n");
        }
    } else if (targetCellX == currCellX) {
        if (targetCellY > currCellY) {
            m_currentDir = MoveDirection::UP;
            printf("(findNextCellDir)Current direction: UP\n");
        } else if (targetCellY < currCellY) {
            m_currentDir = MoveDirection::DOWN;
            printf("(findNextCellDir)Current direction: DOWN\n");
        }
    } else if (targetCellX > currCellX && targetCellY > currCellY) {
            m_currentDir = MoveDirection::UP_RIGHT;
            printf("(findNextCellDir)Current direction: UP_RIGHT\n");
    } else if (targetCellX < currCellX && targetCellY < currCellY) {
            m_currentDir = MoveDirection::DOWN_LEFT;
            printf("(findNextCellDir)Current direction: DOWN_LEFT\n");
        }
     else if (targetCellX < currCellX && targetCellY > currCellY) {
        m_currentDir = MoveDirection::UP_LEFT;
        printf("(findNextCellDir)Current direction: UP_LEFT\n");
    } else if (targetCellX > currCellX && targetCellY < currCellY) {
        m_currentDir = MoveDirection::DOWN_RIGHT;
        printf("(findNextCellDir)Current direction: DOWN_RIGHT\n");
    } else{
        m_currentDir = MoveDirection::IDLE;
        printf("(findNextCellDir)Direction debug didn't move\n");
    }
}
void PathfindingUnit::findNextCellDir(MoveDirection lastDir,int times){
    std::vector<MoveDirection> dictionary = {MoveDirection::UP,MoveDirection::UP_RIGHT,MoveDirection::RIGHT,MoveDirection::DOWN_RIGHT,MoveDirection::DOWN,MoveDirection::DOWN_LEFT,MoveDirection::LEFT,MoveDirection::UP_LEFT};
    int index=0;
    if(times!=0){
        while(dictionary[index]!=lastDir){
            index++;
        }
        if(index+times>dictionary.size()){
            times-=dictionary.size();
        }
        m_currentDir =dictionary[index+times];
        return;
    }

}

bool PathfindingUnit::walkTowardNextCell(){
    switch (m_currentDir) {
    case MoveDirection::RIGHT:{
        m_currentLocation={m_currentLocation.x+m_MovementSpeed,m_currentLocation.y};
        break;
    }
    case MoveDirection::LEFT:{
        m_currentLocation={m_currentLocation.x-m_MovementSpeed,m_currentLocation.y};
        break;
    }
    case MoveDirection::UP:{
        m_currentLocation={m_currentLocation.x,m_currentLocation.y+m_MovementSpeed};
        break;
    }
    case MoveDirection::DOWN:{
        m_currentLocation={m_currentLocation.x,m_currentLocation.y-m_MovementSpeed};
        break;
    }
    case MoveDirection::UP_RIGHT:{
        m_currentLocation={m_currentLocation.x+m_MovementSpeed/SPEED,m_currentLocation.y+m_MovementSpeed/SPEED};
        break;
    }
    case MoveDirection::DOWN_LEFT:{
        m_currentLocation={m_currentLocation.x-m_MovementSpeed/SPEED,m_currentLocation.y-m_MovementSpeed/SPEED};
        break;
    }
    case MoveDirection::DOWN_RIGHT:{
        m_currentLocation={m_currentLocation.x+m_MovementSpeed/SPEED,m_currentLocation.y-m_MovementSpeed/SPEED};
        break;
    }
    case MoveDirection::UP_LEFT:{
        m_currentLocation={m_currentLocation.x-m_MovementSpeed/SPEED,m_currentLocation.y+m_MovementSpeed/SPEED};
        break;
    }
    }
    if(moveDistance>=48){
        moveDistance=0;
        return true;
    }else
        moveDistance+=m_MovementSpeed;
        return false;
}