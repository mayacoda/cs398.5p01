#include <iostream>
#include "GameWorld.h"


#ifdef _WIN32
#include <GL\glut.h>
#include <Windows.h>
#define TIME_CORRECTION 1.0
#elif __APPLE__

#include <GLUT/glut.h>

#define TIME_CORRECTION 0.05 // make slower
#endif


int       iWidth  = 1680;
int       iHeight = 1050;
GameWorld gameWorld(iWidth, iHeight);

double t  = 0.0;
double dt = 0.0166666666666667;

clock_t currentTime = clock();

void drawGUI();

void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGUI();

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

void keyboardHandler(unsigned char key, int x, int y) {
    gameWorld.keyboardHandler(key, x, y);
}

void drawText(char* text, float x, float y, bool makeRed) {
    char* c;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.0, 0.0, 0.0);
    glScalef(0.125, 0.125, 1);
    if (makeRed) {
        std::cout << "making red" << std::endl;
        glColor3f(1.0, 0.3, 0.3);
    }
    for (c = text; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void drawGUI() {
    int yOffset = 50;
    drawText("Press 1-5 to activate behaviors", 50, gameWorld.getHeight() - yOffset, false);

    drawText("1. Wander", 50, gameWorld.getHeight() - yOffset - 20,
             gameWorld.getActiveBehavior() == GameWorld::wander);

    drawText("2. Follow Path", 50, gameWorld.getHeight() - yOffset - 40,
             gameWorld.getActiveBehavior() == GameWorld::pathFollow);

    drawText("3. Hide (click to move green, right click for red, blue hides)", 50, gameWorld.getHeight() - yOffset - 60,
             gameWorld.getActiveBehavior() == GameWorld::hide);

    drawText("4. Offset Pursuit (click to move blue, green and red follow)", 50, gameWorld.getHeight() - yOffset - 80,
             gameWorld.getActiveBehavior() == GameWorld::offsetPursuit);

    drawText("5. Interpose (click to move green, right click for red, blue interposes)", 50, gameWorld.getHeight() - yOffset - 100,
             gameWorld.getActiveBehavior() == GameWorld::interpose);
}

int main(int argc, char** argv) {
    // seed random numbers only once
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(150, 150);
    glutInitWindowSize(iWidth, iHeight);
    glutCreateWindow("Steering Behavior");

    glutMouseFunc(clickHandler);
    glutKeyboardFunc(keyboardHandler);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}