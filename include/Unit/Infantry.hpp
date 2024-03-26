//
// Created by nudle on 2024/3/22.
//
#include "Unit/Avatar.hpp"
#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_INFANTRY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_INFANTRY_HPP


class Infantry:public Avatar{
public:
    Infantry():Avatar(){
        //setHp(50);
        setMovementSpeed(4);
    }
private:
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_INFANTRY_HPP
