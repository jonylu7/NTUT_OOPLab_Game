//
// Created by 盧威任 on 2/11/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_CELL_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_CELL_HPP
#include <GL/glew.h>
#include "Util/Input.hpp"
class CellClass{
public:
    CellClass(){};
    ~CellClass(){};
    void Draw(){
        float x=Util::Input::GetCursorPosition().x;
        float y=Util::Input::GetCursorPosition().y;
        glLineWidth(1.);
        glColor3b(1,1,1);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+10,y);
        glVertex2f(x+10,y+10);
        glVertex2f(x,y+10);
        glEnd();
    }
private:
    /*
     * 1. terrain type
     * 2. overlay item
     * 3. occupied by ... stuff
     * 4. Width and Height
     * 5.
     */

};


#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CELL_HPP


