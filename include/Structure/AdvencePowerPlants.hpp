#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_ADVPowerPlants_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_ADVPowerPlants_HPP
#include "Mechanics/House.hpp"
#include "Structure.hpp"
class ADVPowerPlants : public Structure {
public:
    ADVPowerPlants(float electricPower = 200.F,
                   float buildingTime = 25.F * CHEAT,
                   float buildingCost = 500.F, float buildingHp = 700.F,
                   HouseType house = HouseType::NONE)
        : Structure(electricPower, buildingTime, buildingCost, buildingHp,
                    GameObjectID(unitType::ADV_POWER_PLANT, house)){
              //        SetDrawable(
              //            std::make_unique<Util::Image>("../assets/sprites/PowerPlants.png"));
          };
    void SetSpriteSheet() override {
        m_StructureSpriteSheet->Start(
            "../assets/sprites/ADVPowerPlants_SpriteSheet.png", 72, 72, 13, 0);
        m_relativeOccupiedArea = {{0, 0}, {0, 1}, {0, 2},
                                  {1, 0}, {1, 1}, {1, 2}};
    }
    void SetObjectLocation(glm::vec2 location) override {
        location = MapUtil::PositionStickToGrid(location);
        ObjectLocation = location;
        DrawLocation = {location.x + 1.5 * CELL_SIZE.x,
                        location.y + 1.5 * CELL_SIZE.y};
        m_Transform.translation = DrawLocation;
    }
};

#endif
