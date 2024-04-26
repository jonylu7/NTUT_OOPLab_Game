//
// Created by 盧威任 on 4/25/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SPAWNING_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SPAWNING_HPP
#include "Unit/Avatar.hpp"
#include <unordered_map>
class Spawning {
public:
    void AppendUnit(std::shared_ptr<Avatar> newUnit) {
        m_UnitArray.push_back(newUnit);
        unitArrayAndLocation[newUnit] = newUnit->getCurrentCell();
    }

    void UpdateUnitArray() {
        for (auto unit : m_UnitArray) {
            unit->setSelected(true);
            unit->Update();
            if (unit->getnewDestionationIsSetted()) {
                setNewDestination(unit);
            }
        }
    }

    void setNewDestination(std::shared_ptr<Avatar> unit) {
        FindValidPathToDest m_wayPointUnit(m_Map);

        auto queue = m_wayPointUnit.findPath(unit->getCurrentCell(),
                                             unit->getDestinationCell());
        unit->setMovePath(queue);
        unit->setnewDestinationIsSetted(false);
    }

protected:
    void importmap(std::shared_ptr<MapClass> map) { m_Map = map; }
    std::vector<std::shared_ptr<Avatar>> m_UnitArray;
    std::unordered_map<std::shared_ptr<Avatar>, glm::vec2> unitArrayAndLocation;

private:
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SPAWNING_HPP
