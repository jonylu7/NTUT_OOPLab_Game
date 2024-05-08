//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
#include "UnitManager.hpp"
#include <memory>
class Player {
public:
    Player() {}
    ~Player() {}

    void Start(std::shared_ptr<MapClass> map) {
        m_Map = map;
        m_UnitManager->Start(m_Map, HouseType::ME);
    }
    void Update() { m_UnitManager->Update(); }

public:
    void setTotalCurrency(int value) { m_TotalCurrency = value; }
    void addTotalCurrency(int value) { m_TotalCurrency += value; };

    void setFixedPower(int value) { m_FixedPower = value; }
    void addFixedPower(int value) { m_FixedPower += value; }

    int getTotalCurrency() { return m_TotalCurrency; }
    int getMaxTroopSize() { return m_MaxTroopSize; }

    int getTotalPower() {
        int totalPower = 0;
        std::vector<std::shared_ptr<Structure>> *builtstructure =
            m_UnitManager->getStructureManager()
                ->getStructureArray()
                ->getBuiltStructureArray();

        for (auto i : *builtstructure) {
            if (i->getHouseType() == HouseType::ME) {
                totalPower += i->getElectricPower();
            }
        }
        return totalPower;
    }

public:
    std::shared_ptr<UnitManager> getUnitManager() { return m_UnitManager; }
    void setUnitManager(std::shared_ptr<UnitManager> unitmanager) {
        m_UnitManager = unitmanager;
    }

    House getHouse() { return m_House; }
    void setHouse(House house) { m_House = house; }

protected:
    House m_House;
    int m_MaxTroopSize = 200;
    int m_FixedPower = 0;
    int m_TotalCurrency = 0;
    std::shared_ptr<UnitManager> m_UnitManager =
        std::make_shared<UnitManager>();
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_PLAYER_HPP
