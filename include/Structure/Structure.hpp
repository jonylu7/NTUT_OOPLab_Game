//
// Created by 盧威任 on 1/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#include "Avatar/AttackAndDamage.hpp"
#include "Display/Image.hpp"
#include "Display/SpriteSheet.hpp"
#include "Display/SpriteSheetAnimation.hpp"
#include "HighLight.h"
#include "Mechanics/GameObjectID.hpp"
#include "Selectable.hpp"
#include "Structure/StructureOrder.hpp"

#include "Unit/Health.hpp"
#include "Unit/IHealthable.hpp"

#include "Util/GameObject.hpp"
#include "Util/Input.hpp"
#include "Util/TransformUtils.hpp"
#include "glm/glm.hpp"
#define DEFAULT_ZINDEX 15
#define CHEAT 0.01F
#define INTERVAL 50

class Structure : public Util::GameObject,
                  public Selectable,
                  public StructureOrder,
                  public IHealthable {

public:
    Structure()
        : m_ElectricPower(0.F),
          m_BuildingTime(0.F),
          m_BuildingCost(0.F),
          Selectable(),
          m_ID(GameObjectID(UnitType::NONE, HouseType::NONE)) {}

    Structure(float electricPower, float buildingTime, float buildingCost,
              float buildingHp, GameObjectID id, std::shared_ptr<Health> health)
        : m_ElectricPower(electricPower),
          m_BuildingTime(buildingTime),
          m_BuildingCost(buildingCost),
          Selectable(),
          m_ID(id),
          m_Health(health) {
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
    virtual void SetSpriteSheet() {
        m_StructureSpriteSheet->Start(
            "../assets/sprites/Barracks_SpriteSheet.png", 48, 48, 13, 0);
        m_SpriteSheetAnimation->initSpriteSheetAnimation(m_StructureSpriteSheet,
                                                         false, 0);
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

    std::shared_ptr<Health> getHealth() override { return m_Health; }
    void setHealth(std::shared_ptr<Health> health) override {
        m_Health = health;
    }

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
        std::make_shared<Util::SpriteSheetAnimation>(m_StructureSpriteSheet,
                                                     false, 1);
    glm::vec2 m_DrawLocation = {m_ObjectLocation.x + CELL_SIZE.x,
                                m_ObjectLocation.y + CELL_SIZE.y};
    glm::vec2 m_ObjectLocation = {100, 100};
    std::vector<glm::vec2> m_RelativeOccupiedArea = {{0, 0}};
    
    // health
    std::shared_ptr<Health> m_Health = std::make_shared<Health>();
    // attack and damage
    std::shared_ptr<AttackAndDamage> m_AttackAndDamage =
        std::make_shared<AttackAndDamage>();
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
