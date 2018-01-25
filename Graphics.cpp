#import <GLUT/glut.h>


#include "Graphics.h"


int Graphics::init(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(m_width, m_height);
    glutCreateWindow("Steering Behavior");
    initialize();
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}

void Graphics::initialize() {
    glClearColor(0.8, 0.8, 0.8, 1.0);
}

void Graphics::reshape(int w, int h) {
    // on reshape and on startup, keep the viewport to be the entire size of the window
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // keep our logical coordinate system constant
    gluOrtho2D(0.0, 160.0, 0.0, 120.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graphics::render() {

    //clear all pixels with the specified clear color
    glClear(GL_COLOR_BUFFER_BIT);

    // swap the buffers
    glutSwapBuffers();

    glutPostRedisplay();

}

Graphics::Graphics(GameWorld *gameWorld, int width, int height) : m_gameWorld(gameWorld),
                                                                  m_width(width),
                                                                  m_height(height) {}

