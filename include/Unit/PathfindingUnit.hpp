//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP

#include "Tile.hpp"
#include "Map.hpp"
#include "Line.hpp"
#include "Grid.hpp"
#include "glm/glm.hpp"
#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"

class PathfindingUnit:public Util::GameObject{
protected:
    enum class UnitMode{
        ATTACK,MOVE,WAIT
    };
    enum class MoveDirection{
        UP,UP_RIGHT,UP_LEFT,RIGHT,LEFT,DOWN_RIGHT,DOWN_LEFT,DOWN,IDLE
    };
    Util::Transform m_emptyTrans;
    Line m_line;
    Grid m_grid;
    std::vector<Line> m_lineVector;
    float defaultZIndex=15;
private:
    glm::vec2 m_targetCell;
    glm::vec2 m_nextCell;
    glm::vec2 m_currentCell;
    glm::vec2 m_currentLocation;

    MoveDirection m_currentDir=MoveDirection::IDLE;
    UnitMode m_currentMode=UnitMode::WAIT;

    float m_Hp=100.F;
    float m_MovementSpeed=1.F;
    float m_Armor=5.f;

    int moveDistance = 0;
public:
    PathfindingUnit(){
        m_Transform.scale={1,1};
        m_ZIndex=defaultZIndex;
    };
    virtual ~PathfindingUnit(){};

    void setTargetCell(int x,int y){
        this->m_targetCell={glm::vec2(x,y)};
        }
    glm::vec2 getTargetCell(){return m_targetCell;}

    void setCurrentCell(glm::vec2 cell){
        this->m_currentCell=glm::vec2(cell);
        glm::vec2 temp =MapClass::CellCoordToGlobal(m_currentCell);
        m_currentLocation={temp.x+CELL_SIZE.x/2,temp.y+CELL_SIZE.y/2};
    }
    glm::vec2 getCurrentCell(){return m_currentCell;}

    void setNextCell(glm::vec2 cell){this->m_nextCell=glm::vec2(cell);}
    glm::vec2 getNextCell(){return m_nextCell;}

    glm::vec2 getCurrentLocation(){return m_currentLocation;}

    void setMovementSpeed(int speed){this->m_MovementSpeed=speed;}


    void findNextCellDir();
    void UpdateNextCell();

    void walkTowardNextCell();

    void NextCell(){
        this->m_currentCell=m_nextCell;
        UpdateNextCell();
    };

    virtual void Start(){}
    virtual void Update(){
        Walk();
        m_Transform.translation=getCurrentLocation();
        Draw();
    }
    virtual void Walk(){
        walkTowardNextCell();
        if(moveDistance>=48){
            NextCell();
            moveDistance = 0;
        }
    }

};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PATHFINDINGUNIT_HPP
