//
// Created by 盧威任 on 1/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#include "GameObjectID.hpp"
#include "HighLight.h"

#include "Selectable.hpp"

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/TransformUtils.hpp"
#include "glm/glm.hpp"
#define DEFAULT_ZINDEX 15
#define CHEAT 0.1F

class Structure : public Util::GameObject, public Selectable {

public:
    enum class updateMode { Invisidable, Moveable, Fixed };
    Structure()
        : electricPower(100.F),
          buildingTime(100.F),
          buildingCost(100.F),
          buildingHp(100.F),
          m_ID(GameObjectID(unitType::null, HouseType::NONE)) {
        m_CurrentState = updateMode::Invisidable;
    };

    Structure(float electricPower, float buildingTime, float buildingCost,
              float buildingHp, GameObjectID id)
        : electricPower(electricPower),
          buildingTime(buildingTime),
          buildingCost(buildingCost),
          buildingHp(buildingHp),
          m_ID(id) {
        m_Transform.scale = {1, 1};
        // this->SetZIndex(DEFAULT_ZINDEX);
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
    glm::vec2 GetObjectLocation() { return this->ObjectLocation; }
    glm::vec2 GetTranScale() { return m_Transform.scale; };
    virtual void SetAttachVisible(bool visible);
    glm::vec2 GetDrawLocation() { return DrawLocation; };
    void SetID(GameObjectID id) { m_ID = id; };

    static glm::vec2 ChangeToCell(glm::vec2 location);
    void onSelected();
    virtual void attachmentUpdate(); // this function now will update
                                     // attachment's location and draw as
                                     // well
    bool getBuilt() {
        if (m_CurrentState == updateMode::Fixed) {
            return true;
        } else {
            return false;
        }
    }
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
    virtual float GetBuildingIncome() { return buildingIncome; };
    void SetBuildingIncome(float income) { buildingIncome = income; }
    float GetBuildingHp();
    GameObjectID GetID() { return m_ID; }

//    void importMap(std::shared_ptr<MapClass> map){m_Map=map;}
private:
    updateMode m_CurrentState = updateMode::Invisidable;
    glm::vec2 ObjectLocation = {100, 100};
    glm::vec2 DrawLocation = {ObjectLocation.x + CELL_SIZE.x,
                              ObjectLocation.y + CELL_SIZE.y};
    float electricPower;
    float buildingTime;
    float buildingCost;
    float buildingHp;
    float buildingIncome = 0.F;
    HighLight m_HighLight;
    GameObjectID m_ID;

protected:
//    std::shared_ptr<MapClass> m_Map;
    bool b_selectingNewWayPoint = false;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
