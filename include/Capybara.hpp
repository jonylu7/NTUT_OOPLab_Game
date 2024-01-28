//
// Created by 盧威任 on 1/28/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_CAPYBARA_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_CAPYBARA_HPP

#include "Util/GameObject.hpp"

class Capybara:public Util::GameObject{
private:

public:
void Update(const Util::Transform &transform = Util::Transform()) override;
void Start()override{};


};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CAPYBARA_HPP
