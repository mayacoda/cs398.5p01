#include <iostream>
#include "game-world/GameWorld.h"


#ifdef _WIN32
#include <GL\glut.h>
#include <Windows.h>
#define TIME_CORRECTION 1.0
#elif __APPLE__

#define TIME_CORRECTION 0.1 // make slower
#endif


int winWidth  = 800;
int winHeight = 460;

int       worldWidth  = 1600;
int       worldHeight = 1280;
GameWorld gameWorld(worldWidth, worldHeight);

double t  = 0.0;
double dt = 0.0166666666666667;

clock_t currentTime;

void setClippingPlane();

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    setClippingPlane();

    clock_t newTime   = clock();
    double  frameTime = ((double) newTime - currentTime) / (CLOCKS_PER_SEC * TIME_CORRECTION);
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

void setClippingPlane() {
    Vector2D<double> playerPos = gameWorld.getPlayerPos();
    int x1, x2, y1, y2;

    x1 = static_cast<int>(playerPos.x - winWidth / 2);
    x2 = static_cast<int>(playerPos.x + winWidth / 2);
    y1 = static_cast<int>(playerPos.y - winHeight / 2);
    y2 = static_cast<int>(playerPos.y + winHeight / 2);

    if (x1 <= 0) { x1 = 0; x2 = winWidth; }
    if (x2 >= worldWidth) { x1 = worldWidth - winWidth; x2 = worldWidth; }
    if (y1 <= 0) { y1 = 0; y2 = winHeight; }
    if (y2 >= worldHeight) { y1 = worldHeight - winHeight; y2 = worldHeight; }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(x1, x2, y1, y2, -1, 1);

    gameWorld.setClippingBoundaries(x1, x2, y1, y2);
}

void reshape(GLint width, GLint height) {
    winWidth = width;
    winHeight = height;

    glViewport(0, 0, winWidth, winHeight);
    setClippingPlane();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
}

void clickHandler(int b, int s, int x, int y) {
    gameWorld.clickHandler(b, s, x, y);
}

void keyboardHandler(unsigned char key, int x, int y) {
    gameWorld.keyboardHandler(key, x, y);
}

int main(int argc, char** argv) {
    // seed random numbers only once
    srand(static_cast<unsigned int>(time(nullptr)));

    currentTime = clock();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(150, 150);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Steering Behavior");

    glutMouseFunc(clickHandler);
    glutKeyboardFunc(keyboardHandler);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}