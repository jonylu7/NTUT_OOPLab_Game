#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_ADVPowerPlants_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_ADVPowerPlants_HPP
#include "Mechanics/House.hpp"
#include "Structure.hpp"
class ADVPowerPlants : public Structure {
public:
    ADVPowerPlants(
        float electricPower = 200.F, float buildingTime = 25.F * CHEAT,
        float buildingCost = 500.F, float buildingHp = 700.F,
        HouseType house = HouseType::MY,
        std::shared_ptr<Health> health = std::make_shared<Health>(100, 0.7))
        : Structure(electricPower, buildingTime, buildingCost, buildingHp,
                    GameObjectID(UnitType::ADV_POWER_PLANT, house), health){
              //        SetDrawable(
              //            std::make_unique<Util::Image>("../assets/sprites/PowerPlants.png"));
          };
    ADVPowerPlants(HouseType house)
        : Structure(200.F, 25.F * CHEAT, 500.F,700.F,
                    GameObjectID(UnitType::ADV_POWER_PLANT, house)){};
    void SetSpriteSheet() override {
        m_StructureSpriteSheet->Start(
            "../assets/sprites/ADVPowerPlants_SpriteSheet.png", 72, 72, 13, 0);
        m_RelativeOccupiedArea = {{0, 0}, {0, 1}, {0, 2},
                                  {1, 0}, {1, 1}, {1, 2}};
    }
    void SetObjectLocation(glm::vec2 location) override {
        location = MapUtil::PositionStickToGrid(location);
        m_ObjectLocation = location;
        m_DrawLocation = {location.x + 1.5 * CELL_SIZE.x,
                          location.y + 1.5 * CELL_SIZE.y};
        m_Transform.translation = m_DrawLocation;
    }
};

#endif
