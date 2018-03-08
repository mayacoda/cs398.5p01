#include <iostream>
#include "GameWorld.h"
#include <ctime>


#ifdef _WIN32
#include <GL\glut.h>
#include <Windows.h>
#define TIME_CORRECTION 1.0
#elif __APPLE__
#include <GLUT/glut.h>
#define TIME_CORRECTION 0.02 // make slower
#endif


int iWidth = 1680;
int iHeight = 1050;
GameWorld gameWorld(iWidth, iHeight);

double t = 0.0;
double dt = 0.0166666666666667;

clock_t currentTime = clock();

void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    clock_t newTime = clock();
    double frameTime = ((double) newTime - currentTime) / (CLOCKS_PER_SEC * TIME_CORRECTION);
    currentTime = newTime;

    while (frameTime > 0.0) {
        double deltaTime = min(frameTime, dt);
        frameTime -= deltaTime;
        gameWorld.update(deltaTime);
        t += deltaTime;
    }
    gameWorld.render();

    glutSwapBuffers();
    glFlush();
}

void timer(int val) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void reshape(GLint width, GLint height) {
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    gameWorld.setDimensions(width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
}

void clickHandler(int b, int s, int x, int y) {
    gameWorld.clickHandler(b, s, x, y);
}

int main(int argc, char **argv) {
    // seed random numbers only once
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(150, 150);
    glutInitWindowSize(iWidth, iHeight);
    glutCreateWindow("Steering Behavior");

    glutMouseFunc(clickHandler);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}