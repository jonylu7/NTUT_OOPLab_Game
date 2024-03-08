//
// Created by 盧威任 on 1/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#include "Util/GameObject.hpp"
#include "Util/Input.hpp"
#include "Util/TransformUtils.hpp"
#include "glm/glm.hpp"
#include "HighLight.h"
#include "Util/Image.hpp"
#include "Map.hpp"
#define CELL 48.F
#define DEFAULT_ZINDEX 15

class Structure : public Util::GameObject {

public:
    enum class updateMode { Invisidable, Moveable, Fixed };
    Structure():
          electricPower(100.F),buildingTime(100.F),
          buildingCost(100.F),buildingHp(100.F){
        m_CurrentState=updateMode::Invisidable;
    };
    Structure(float electricPower,float buildingTime,
                float buildingCost,float buildingHp):
                electricPower(electricPower),buildingTime(buildingTime),
                buildingCost(buildingCost),buildingHp(buildingHp){
        m_Transform.scale={1,1};
        //this->SetZIndex(DEFAULT_ZINDEX);
    };
    ~Structure(){};

    void Update() override;
    virtual void updateFixed();
    virtual void updateMoveable();
    virtual void updateInvinsible();


    void Start() override;
    updateMode GetCurrentUpdateMode() const { return m_CurrentState; };
    void SetCurrentUpdateMode(updateMode mode) { m_CurrentState = mode; };
    virtual void SetObjectLocation(glm::vec2 location);
    glm::vec2 GetObjectLocation(){return this->ObjectLocation; }
    glm::vec2 GetTranScale(){return m_Transform.scale;};

    glm::vec2 ChangeToCell(glm::vec2 location);
    virtual void onSelected(bool selected);
    virtual void SetAttachVisible(bool visible);

    /*
    void SetElectricPower(float electricPower);
    void SetBuildingTime(float buildingTime);
    void SetBuildingCost(float buildingCost);
    void SetBuildingHp(float buildingHp);
    void DecreaseElectricPower(float Power);
    void IncreaseBuildingTime(float Time);
    void DecreaseBuildingCost(float Cost);
    */

    void DecreaseHp(float Hp);

    float GetElectricPower();
    float GetBuildingTime();
    float GetBuildingCost();
    float GetBuildingHp();

private:
    updateMode m_CurrentState = updateMode::Invisidable;
    glm::vec2 ObjectLocation={100,100};
    float electricPower;
    float buildingTime;
    float buildingCost;
    float buildingHp;
    HighLight m_HighLight;
    bool b_select= false;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
