#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_PowerPlants_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_PowerPlants_HPP

#include "Structure.hpp"

class PowerPlants : public Structure {
public:
    PowerPlants(float electricPower = 100.F, float buildingTime = 15.F * CHEAT,
                float buildingCost = 300.F, float buildingHp = 400.F,
                HouseType housetype = HouseType::ME,
                std::shared_ptr<Health> health = std::make_shared<Health>(100,
                                                                          0.5))
        : Structure(electricPower, buildingTime, buildingCost, buildingHp,
                    GameObjectID(UnitType::POWER_PLANT, housetype), health){

          };
    PowerPlants(HouseType housetype,
                std::shared_ptr<Health> health = std::make_shared<Health>(100,
                                                                          0.7))
        : Structure(100.F, 15.F * CHEAT, 300.F, 400.F,
                    GameObjectID(UnitType::POWER_PLANT, housetype), health){};
    void SetSpriteSheet() override {
        m_StructureSpriteSheet->Start(
            "../assets/sprites/PowerPlants_SpriteSheet.png", 48, 48, 13, 0);
        m_RelativeOccupiedArea = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        m_SpriteSheetAnimation->initSpriteSheetAnimation(m_StructureSpriteSheet,
                                                         true, 0);
    }
    void SetObjectLocation(glm::vec2 location) override {
        location = MapUtil::PositionStickToGrid(location);
        m_ObjectLocation = location;
        m_DrawLocation = {location.x + 1 * CELL_SIZE.x,
                          location.y + 1 * CELL_SIZE.y};
        m_Transform.translation = m_DrawLocation;
    }
};

#endif
