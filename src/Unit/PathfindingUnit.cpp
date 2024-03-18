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
    }
    }
}
void PathfindingUnit::findNextCellDir() {
    int targetCellX = m_targetCell.x;
    int targetCellY = m_targetCell.y;
    int currCellX=m_currentCell.x;
    int currCellY=m_currentCell.y;
    printf("(find)Cell now :{%.d,%.d}\n(find)Cell target : {%.d,%.d}\n",currCellX,currCellY,targetCellX,targetCellY);
    if (targetCellX == currCellX && targetCellY == currCellY) {
        m_currentDir = MoveDirection::IDLE;
        printf("Current direction: IDLE\n");
    } else if (targetCellY == currCellY) {
        if (targetCellX > currCellX) {
            m_currentDir = MoveDirection::RIGHT;
            printf("Current direction: RIGHT\n");
        } else if (targetCellX < currCellX) {
            m_currentDir = MoveDirection::LEFT;
            printf("Current direction: LEFT\n");
        }
    } else if (targetCellX == currCellX) {
        if (targetCellY > currCellY) {
            m_currentDir = MoveDirection::UP;
            printf("Current direction: UP\n");
        } else if (targetCellY < currCellY) {
            m_currentDir = MoveDirection::DOWN;
            printf("Current direction: DOWN\n");
        }
    } else if (abs(targetCellX - currCellX) == abs(targetCellY - currCellY)) {
        if (targetCellX > currCellX && targetCellY > currCellY) {
            m_currentDir = MoveDirection::UP_RIGHT;
            printf("Current direction: UP_RIGHT\n");
        } else if (targetCellX < currCellX && targetCellY < currCellY) {
            m_currentDir = MoveDirection::DOWN_LEFT;
            printf("Current direction: DOWN_LEFT\n");
        }
    } else if (targetCellX < currCellX && targetCellY > currCellY) {
        m_currentDir = MoveDirection::UP_LEFT;
        printf("Current direction: UP_LEFT\n");
    } else if (targetCellX > currCellX && targetCellY < currCellY) {
        m_currentDir = MoveDirection::DOWN_RIGHT;
        printf("Current direction: DOWN_RIGHT\n");
    }else if(abs(targetCellX - currCellX)>abs(targetCellY - currCellY)){
        if (targetCellX > currCellX && targetCellY > currCellY) {
            m_currentDir = MoveDirection::RIGHT;
            printf("Current direction: RIGHT\n");
        } else if (targetCellX < currCellX && targetCellY < currCellY) {
            m_currentDir = MoveDirection::LEFT;
            printf("Current direction: LEFT\n");
        }
    }else if(abs(targetCellX - currCellX)<abs(targetCellY - currCellY)){
        if (targetCellX > currCellX && targetCellY > currCellY) {
            m_currentDir = MoveDirection::UP;
            printf("Current direction: UP\n");
        } else if (targetCellX < currCellX && targetCellY < currCellY) {
            m_currentDir = MoveDirection::DOWN;
            printf("Current direction: DOWN\n");
        }
    }
    else{
        printf("(find)Direction debug didn't move\n");
    }
}
void PathfindingUnit::walkTowardNextCell(){
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
        m_currentLocation={m_currentLocation.x+m_MovementSpeed,m_currentLocation.y+m_MovementSpeed};
        break;
    }
    case MoveDirection::DOWN_LEFT:{
        m_currentLocation={m_currentLocation.x-m_MovementSpeed,m_currentLocation.y-m_MovementSpeed};
        break;
    }
    case MoveDirection::DOWN_RIGHT:{
        m_currentLocation={m_currentLocation.x+m_MovementSpeed,m_currentLocation.y-m_MovementSpeed};
        break;
    }
    case MoveDirection::UP_LEFT:{
        m_currentLocation={m_currentLocation.x-m_MovementSpeed,m_currentLocation.y+m_MovementSpeed};
        break;
    }
    }
    moveDistance+=m_MovementSpeed;
}