//
// Created by 盧威任 on 1/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#include "HighLight.h"
#include "Mechanics//GameObjectID.hpp"
#include "Selectable.hpp"
#include "SpriteSheet.hpp"

#include "Unit/AttackAndDamageUnit.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/SpriteSheetAnimation.hpp"
#include "Util/TransformUtils.hpp"
#include "glm/glm.hpp"
#define DEFAULT_ZINDEX 15
#define CHEAT 0.01F
#define INTERVAL 50

class Structure : public Util::GameObject,
                  public Selectable,
                  public AttackAndDamageUnit {

public:
    enum class updateMode { Invisidable, Moveable, Fixed };
    Structure()
        : electricPower(100.F),
          buildingTime(100.F),
          buildingCost(100.F),
          m_ID(GameObjectID(unitType::null, HouseType::NONE)) {
        m_CurrentState = updateMode::Invisidable;
    };

    Structure(float electricPower, float buildingTime, float buildingCost,
              float buildingHp, GameObjectID id)
        : electricPower(electricPower),
          buildingTime(buildingTime),
          buildingCost(buildingCost),
          m_ID(id) {
        m_Transform.scale = {1, 1};
        // this->SetZIndex(DEFAULT_ZINDEX);
    };

    ~Structure(){};

    void Update() override;
    virtual void updateFixed();
    virtual void updateMoveable();
    virtual void updateInvinsible() { this->SetAttachVisible(false); }

    virtual void whenSelected() { this->SetAttachVisible(getSelected()); }

    void Start() override;
    virtual void SetSpriteSheet() {
        m_StructureSpriteSheet->Start(
            "../assets/sprites/Barracks_SpriteSheet.png", 48, 48, 13, 0);
    }
    updateMode GetCurrentUpdateMode() const { return m_CurrentState; };
    void SetCurrentUpdateMode(updateMode mode) { m_CurrentState = mode; };
    virtual void SetObjectLocation(glm::vec2 location);

    glm::vec2 GetObjectLocation() { return this->ObjectLocation; }
    glm::vec2 GetTranScale() { return m_Transform.scale; };
    virtual void SetAttachVisible(bool visible);
    glm::vec2 GetDrawLocation() { return DrawLocation; };
    void SetID(GameObjectID id) { m_ID = id; };
    
    virtual void attachmentUpdate();
    bool getConstructed() {
        if (m_CurrentState == updateMode::Fixed) {
            return true;
        } else {
            return false;
        }
    }

    float GetElectricPower() { return this->electricPower; }
    float GetBuildingTime() { return this->buildingTime; }
    float GetBuildingCost() { return this->buildingCost; }
    GameObjectID GetID() { return m_ID; }

    glm::vec2 GlobalCoordToCellCoord(glm::vec2 globalCoord) {
        return glm::vec2(int(globalCoord[0] / CELL_SIZE.x),
                         int(globalCoord[1] / CELL_SIZE.y));
    }

    glm::vec2 GetObjectCell() { return GlobalCoordToCellCoord(ObjectLocation); }
    std::vector<glm::vec2> GetAbsoluteOccupiedArea();
    bool ifBuildable();
    void SetOccupiedAreaUnbuildable();
    void SetRelativeOccupiedArea(std::vector<glm::vec2> Area) {
        m_relativeOccupiedArea = Area;
    }

protected:
    updateMode m_CurrentState = updateMode::Invisidable;
    float electricPower;
    float buildingTime;
    float buildingCost;
    float buildingIncome = 0.F;
    HighLight m_HighLight;
    GameObjectID m_ID;

protected:
    std::shared_ptr<SpriteSheet> m_StructureSpriteSheet =
        std::make_shared<SpriteSheet>();
    std::shared_ptr<Util::SpriteSheetAnimation> m_SpriteSheetAnimation =
        std::make_shared<Util::SpriteSheetAnimation>();
    glm::vec2 DrawLocation = {ObjectLocation.x + CELL_SIZE.x,
                              ObjectLocation.y + CELL_SIZE.y};
    glm::vec2 ObjectLocation = {100, 100};
    std::vector<glm::vec2> m_relativeOccupiedArea = {{0, 0}};
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
