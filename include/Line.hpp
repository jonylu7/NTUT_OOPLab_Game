//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_LINE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_LINE_HPP
#include "glm/glm.hpp"
class Line {
public:
    Line(){};
    ~Line(){};
    Line(glm::vec2 lineFrom, glm::vec2 lineTo, glm::vec3 color) {
        this->lineFrom = lineFrom;
        this->lineTo = lineTo;
        this->color = color;
    }

    Line(glm::vec2 lineFrom, glm::vec2 lineTo) {
        this->lineFrom = lineFrom;
        this->lineTo = lineTo;
        this->color = glm::vec3(1, 1, 1);
    }

    glm::vec2 getlineFrom() { return lineFrom; };
    glm::vec2 getlineTo() { return lineTo; };
    glm::vec3 getColor() { return color; };

private:
    glm::vec2 lineFrom;
    glm::vec2 lineTo;
    glm::vec3 color;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_LINE_HPP
