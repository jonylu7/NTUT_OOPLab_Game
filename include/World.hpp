//
// Created by 盧威任 on 2/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_WORLD_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_WORLD_HPP
#include "Cell.hpp"
#include "Component/Component.hpp"
#include <memory>
#include <vector>
typedef unsigned int CELL;
class WorldClass : public Component {
public:
    WorldClass(){};
    ~WorldClass(){};

    void Start() override{};
    void Update() override{};

private:
    CELL WorldWidth = 2;
    CELL WorldHeight = 2;
    std::vector<std::shared_ptr<CellClass>> Map;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_WORLD_HPP
