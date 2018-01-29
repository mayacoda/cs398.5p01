#include <iostream>
#include "GameWorld.h"
#include <GLUT/glut.h>

int iWidth = 800;
int iHeight = 600;
GameWorld gameWorld(iWidth, iHeight);

double t = 0.0;
double dt = 1 / 60.0;

clock_t currentTime = clock();

void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    clock_t newTime = clock();
    double frameTime = ((double) newTime - currentTime) / CLOCKS_PER_SEC;
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
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(150, 150);
    glutInitWindowSize(iWidth, iHeight);
    glutCreateWindow("Steering Behavior");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}