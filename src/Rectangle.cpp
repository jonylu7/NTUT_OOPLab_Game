//
// Created by 盧威任 on 1/30/24.
//

#include "OpenGL/gl.h"
void draweRect(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    glLineWidth(30);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_POLYGON);
    glVertex2i(50,90);
    glVertex2i(100,90);
    glVertex2i(100,150);
    glVertex2i(50,150);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glFlush();
}