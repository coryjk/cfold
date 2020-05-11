// cfoldvisual.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "visuals.h"
#include "lattice/lattice.h"

using namespace std;

int main(int argc, char* argv[]) {
    //  Initialize GLUT and process user parameters
    glutInit(&argc, argv);

    //  Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create window
    glutCreateWindow("Awesome Cube");

    glutReshapeWindow(1000, 800);

    //  Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);

    // Callback functions
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    //  Pass control to GLUT for events
    glutMainLoop();

    //  Return to OS
    return 0;
}
