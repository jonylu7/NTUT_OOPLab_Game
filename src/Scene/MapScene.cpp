//
// Created by 盧威任 on 2/15/24.
//
#include "Scene/MapScene.hpp"
#include "DrawOverlays.hpp"
#include <iostream>
void MapScene::Start() {
    // m_Map->Init(204, 161);
    m_Map->Init(
        MapBinReader::readBin("../assets/map/green-belt/map.bin", 98, 98), 98,
        98);
}

void MapScene::Update() {
    m_SceneCamera.Update();
    Util::Transform trans;
    trans.scale = {1, 1};
    trans.translation = {0, 0};
    m_Map->Draw(trans, 0);
}
