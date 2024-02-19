//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_COMPONENT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_COMPONENT_HPP

class Component {
public:
    Component(){};
    virtual ~Component(){};
    virtual void Start() = 0;
    virtual void Update() = 0;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_COMPONENT_HPP
