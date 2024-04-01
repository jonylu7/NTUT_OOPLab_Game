//
// Created by 盧威任 on 2/15/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MAPSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MAPSCENE_HPP
#include "Scene/Scene.hpp"
#include "Util/BGM.hpp"
class MapScene : public Scene {
public:
    MapScene(){};
    ~MapScene(){};

    void Start() override;
    void Update() override;
    void End(){};

private:
    SpriteSheet m_SpriteSheet;
    DrawOverlays m_testdraw;
    Grid testGrid;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MAP_HPP
