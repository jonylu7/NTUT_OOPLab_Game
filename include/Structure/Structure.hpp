//
// Created by 盧威任 on 1/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#include "Display/SpriteSheet.hpp"
#include "HighLight.h"
#include "Mechanics//GameObjectID.hpp"
#include "Selectable.hpp"

#include "Avatar/AttackAndDamageUnit.hpp"
#include "Display/Image.hpp"
#include "Display/SpriteSheetAnimation.hpp"
#include "Structure/StructureOrder.hpp"
#include "Util/GameObject.hpp"
#include "Util/Input.hpp"
#include "Util/TransformUtils.hpp"
#include "glm/glm.hpp"
#define DEFAULT_ZINDEX 15
#define CHEAT 0.01
#define INTERVAL 50

class Structure : public Util::GameObject,
                  public Selectable,
                  public StructureOrder,
                  public AttackAndDamageUnit {

public:
    Structure()
        : m_ElectricPower(0.F),
          m_BuildingTime(0.F),
          m_BuildingCost(0.F),
          Selectable(),
          m_ID(GameObjectID(UnitType::NONE, HouseType::NONE)) {
        m_LivingStatus = LivingStatus::NOT_BORN_YET;
    };

    Structure(float electricPower, float buildingTime, float buildingCost,
              float buildingHp, GameObjectID id)
        : m_ElectricPower(electricPower),
          m_BuildingTime(buildingTime),
          m_BuildingCost(buildingCost),
          Selectable(),
          m_ID(id) {
        m_Transform.scale = {1, 1};
        // this->SetZIndex(DEFAULT_ZINDEX);
    };

    ~Structure(){};

    void Update() override;
    virtual void updateFixed();
    virtual void updateMoveable();
    virtual void updateInvinsible() { this->SetAttachVisible(false); }

    virtual void whenSelected() override { this->SetAttachVisible(b_Selected); }

    void Start() override;
    virtual void Start(glm::vec2 location);
    virtual void SetSpriteSheet() {
        m_StructureSpriteSheet->Start(
            "../assets/sprites/Barracks_SpriteSheet.png", 48, 48, 13, 0);
    }

    virtual void SetObjectLocation(glm::vec2 location);

    glm::vec2 GetObjectLocation() { return this->m_ObjectLocation; }
    virtual void SetAttachVisible(bool visible);
    glm::vec2 GetDrawLocation() { return m_DrawLocation; };
    void SetID(GameObjectID id) { m_ID = id; };

    virtual void attachmentUpdate();

    float getElectricPower() { return this->m_ElectricPower; }
    float getBuildingTime() { return this->m_BuildingTime; }
    float getBuildingCost() { return this->m_BuildingCost; }
    HouseType getHouseType(){return  this->m_ID.getHouseType();}

    glm::vec2 GlobalCoordToCellCoord(glm::vec2 globalCoord) {
        return glm::vec2(int(globalCoord[0] / CELL_SIZE.x),
                         int(globalCoord[1] / CELL_SIZE.y));
    }

    glm::vec2 GetObjectCell() {
        return GlobalCoordToCellCoord(m_ObjectLocation);
    }
    std::vector<glm::vec2> GetAbsoluteOccupiedArea();
    void SetRelativeOccupiedArea(std::vector<glm::vec2> Area) {
        m_RelativeOccupiedArea = Area;
    }

    GameObjectID getID() { return m_ID; }

protected:
    float m_ElectricPower;
    float m_BuildingTime;
    float m_BuildingCost;
    float m_BuildingIncome = 0.F;
    HighLight m_HighLight;
    GameObjectID m_ID;

protected:
    std::shared_ptr<SpriteSheet> m_StructureSpriteSheet =
        std::make_shared<SpriteSheet>();
    std::shared_ptr<Util::SpriteSheetAnimation> m_SpriteSheetAnimation =
        std::make_shared<Util::SpriteSheetAnimation>();
    glm::vec2 m_DrawLocation = {m_ObjectLocation.x + CELL_SIZE.x,
                                m_ObjectLocation.y + CELL_SIZE.y};
    glm::vec2 m_ObjectLocation = {100, 100};
    std::vector<glm::vec2> m_RelativeOccupiedArea = {{0, 0}};
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
