//
// Created by 盧威任 on 2/25/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TERRAIN_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TERRAIN_HPP
#include "Util/GameObject.hpp"
#include "Util/ImageArray.hpp"
#include "Core/Drawable.hpp"
class Terrain:public Util::GameObject{
public:
    Terrain(){
        SetDrawable(std::make_shared<Util::ImageArray>("../assets/sprites/Desert.png"));
        m_Transform.translation=glm::vec2(50,50);
        m_Transform.scale=glm::vec2(0.2F,0.2F);
    };
    ~Terrain(){};

    void Update() override{
    }

private:



};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TERRAIN_HPP
