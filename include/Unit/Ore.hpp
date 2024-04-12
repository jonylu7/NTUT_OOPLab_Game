//
// Created by nudle on 2024/3/31.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ORE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ORE_HPP
#include "Avatar.hpp"
class Ore:public Avatar{
private:
    int m_oreRemain = 2000;
    std::shared_ptr<MapClass> m_Map;
public:
    std::shared_ptr<Util::Image> customizeImage() override{return std::make_unique<Util::Image>("../assets/sprites/Ore.png");}
    int getOreRemain(){return m_oreRemain;}
    void Start(glm::vec2 oreCell,std::shared_ptr<MapClass> map){
        m_Map=map;
        m_currentMode=UnitMode::MOVE;
        setCurrentCell(oreCell);
        setNextCell(oreCell);
        SetDrawable(customizeImage());
        m_Transform.scale={.03,.03};
        m_Transform.translation = getCurrentLocation();
        SetVisible(true);
        std::shared_ptr<TileClass> tileClass = m_Map->getTileByCellPosition(oreCell);
        tileClass->setBuildable(false);
    }
    void beingMined(int attack){m_oreRemain-=attack;}
    void aliveUpdate() override{
        this->Draw();
        if(getOreRemain()<=0){
            std::shared_ptr<TileClass> tileClass = m_Map->getTileByCellPosition(getCurrentCell());
            tileClass->setBuildable(true);
            m_currentMode=UnitMode::DEAD;
        }
    }

};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ORE_HPP
