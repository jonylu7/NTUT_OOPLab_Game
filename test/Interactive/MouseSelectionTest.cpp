//
// Created by 盧威任 on 2/6/24.
//

#include "GLUT/glut.h"

struct Position
{
    Position() : x(0), y(0) {}
    float x, y;
};

Position start, finish;
void mouse( int button, int state, int x, int y )
{
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        start.x = finish.x = x;
        start.y = finish.y = y;
    }
    if( button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        finish.x=x;
        finish.y=y;
    }
    glutPostRedisplay();
}

void motion( int x, int y )
{
    finish.x = x;
    finish.y = y;
    glutPostRedisplay();
}

void display()
{
    glClearColor( 0, 0, 0, 1 );
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    glOrtho( 0, w, h, 0, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glPushMatrix();
    glColor3f(1,1,0);
    glBegin(GL_QUADS);
    glVertex2f(start.x,start.y);
    glVertex2f(finish.x,start.y);
    glVertex2f(finish.x,finish.y);
    glVertex2f(start.x,finish.y);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);
    glutCreateWindow("GLUT");
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}