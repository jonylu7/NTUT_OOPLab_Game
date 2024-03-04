//
// Created by 盧威任 on 1/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#include "Util/GameObject.hpp"
#include "Util/Input.hpp"
#include "Util/TransformUtils.hpp"
#include "glm/glm.hpp"


class Structure : public Util::GameObject {

public:
    enum class updateMode { Invisidable, Moveable, Fixed };
    Structure():
          electricPower(100.F),buildingTime(100.F),
          buildingCost(100.F),buildingHp(100.F){};
    Structure(float electricPower,float buildingTime,
                float buildingCost,float buildingHp):
                electricPower(electricPower),buildingTime(buildingTime),
                buildingCost(buildingCost),buildingHp(buildingHp){m_Transform.scale={0.2,0.2};};
    ~Structure(){};

    void Update(const Util::Transform &transform = Util::Transform()) override;

    void Start() override{};
    updateMode GetCurrentUpdateMode() const { return m_CurrentState; };
    void SetCurrentUpdateMode(updateMode mode) { m_CurrentState = mode; };
    void SetObjectLocation(glm::vec2 location);
    glm::vec2 GetObjectLocation(){return this->ObjectLocation; }
    //virtual glm::vec2 GetWayPointLocation(){return {0,0};};
    //void SetTransformation(glm::vec2 newTrans);
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
    glm::vec2 ObjectLocation={0,0};
    float electricPower;
    float buildingTime;
    float buildingCost;
    float buildingHp;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
