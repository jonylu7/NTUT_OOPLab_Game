//
// Created by 盧威任 on 1/30/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
#include "Selectable.hpp"
#include "Util/GameObject.hpp"
#include "glm/glm.hpp"

class Infantry :public Util::GameObject{

public:
    enum class updateMode{Uncreated,MovingToDestination,Standing,Attacking};
    Infantry(){};
    ~Infantry(){};

    void Update(const Util::Transform &transform = Util::Transform()) override;
    void Start()override{
    };
    updateMode GetCurrentUpdateMode()const {return m_CurrentState;};
    void SetCurrentUpdateMode(updateMode mode){m_CurrentState=mode;};
    void SetObjectLocation(glm::vec2 location){
        Destination=location;
    }
private:
    updateMode m_CurrentState=updateMode::Uncreated;
    glm::vec2 Destination;
    float SpeedPerFrame=1.F;

};



#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_HPP
