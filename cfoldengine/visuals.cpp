#include "visuals.h"

double rotate_y = 0;
double rotate_x = 0;

void display() {
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double w = glutGet(GLUT_WINDOW_WIDTH) / 300.0;
    double h = glutGet(GLUT_WINDOW_HEIGHT) / 300.0;
    glOrtho(-1 * w, 1 * w, -1 * h, 1 * h, 10, -10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Rotate when user changes rotate_x and rotate_y
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    glBegin(GL_LINES);
    glVertex3d(0.0f, 0.0f, 0.0f);
    glVertex3d(50.0f, 50.0f, 50.0f);
    glEnd();

    glFlush();
    glutSwapBuffers();
}


void specialKeys(int key, int x, int y) {
    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;

    //  Left arrow - decrease rotation by 5 degree
    if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;

    if (key == GLUT_KEY_UP)
        rotate_x += 5;

    if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;

    //  Request display update
    glutPostRedisplay();
}