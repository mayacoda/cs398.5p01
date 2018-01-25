#include <iostream>
#include "GameWorld.h"
#include <GLUT/glut.h>

void render();

void reshape(int, int);

void loop(int);

int iWidth = 800;
int iHeight = 600;
GameWorld gameWorld(iWidth, iHeight);

double t = 0.0;
double dt = 1 / 60.0;

clock_t currentTime = clock();

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(iWidth, iHeight);
    glutCreateWindow("Steering Behavior");

    // maybe replace this behavior with lambda expressions
    // https://msdn.microsoft.com/en-us/library/dd293608.aspx
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, loop, 0);

    // using GLUT for the main gameloop
    glutMainLoop();
    return 0;
}


void render() {

    glClearColor(0.8, 0.8, 0.8, 1);  // (In fact, this is the default.)
    glClear(GL_COLOR_BUFFER_BIT);

    // listen to inputs from the user
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
}

void loop(int val) {
    glutPostRedisplay();

    glutTimerFunc(16, loop, 0);
}

void reshape(int w, int h) {
    // on reshape and on startup, keep the viewport to be the entire size of the window
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, w, 0.0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


