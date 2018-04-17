#include <iostream>
#include "game-world/GameWorld.h"
#include "character/derived/Thug.h"
#include "character/derived/Sneak.h"
#include "character/derived/Runner.h"
#include "ui/Bounds.h"
#include "ui/UI.h"


#ifdef _WIN32
#include <GL\glut.h>
#include <Windows.h>
#define TIME_CORRECTION 1.0
#elif __APPLE__

#define TIME_CORRECTION 0.1 // make slower
#endif

GameWorld::gameState state         = GameWorld::menu;
bool                 fullScreen    = false;
Bounds<int>          currentWindow = Bounds<int>(610, 150, 150, 950);

int winWidth  = 800;
int winHeight = 460;

int       worldWidth  = 3200;
int       worldHeight = 2560;
GameWorld gameWorld(worldWidth, worldHeight);
UI        ui(&gameWorld);

double t  = 0.0;
double dt = 0.0166666666666667;

clock_t currentTime;

void setClippingPlane() {
    Vector2D<double> playerPos = gameWorld.getPlayerPos();
    int              x1, x2, y1, y2;

    x1 = static_cast<int>(playerPos.x - winWidth / 2);
    x2 = static_cast<int>(playerPos.x + winWidth / 2);
    y1 = static_cast<int>(playerPos.y - winHeight / 2);
    y2 = static_cast<int>(playerPos.y + winHeight / 2);

    if (x1 <= 0) {
        x1 = 0;
        x2 = winWidth;
    }
    if (x2 >= worldWidth) {
        x1 = worldWidth - winWidth;
        x2 = worldWidth;
    }
    if (y1 <= 0) {
        y1 = 0;
        y2 = winHeight;
    }
    if (y2 >= worldHeight) {
        y1 = worldHeight - winHeight;
        y2 = worldHeight;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(x1, x2, y1, y2, -1, 1);

    gameWorld.setClippingBoundaries(x1, x2, y1, y2);
}

void gameLoop() {
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

    ui.renderHUD();

    glutSwapBuffers();
    glFlush();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (state) {
        case GameWorld::play:
            gameLoop();
            break;
        case GameWorld::menu:
            ui.renderMenu(winWidth, winHeight);
            break;
        case GameWorld::select:
            ui.renderCharacterSelection(winWidth, winHeight);
            break;
        case GameWorld::over:
            ui.renderGameOver(winWidth, winHeight);
            break;
        case GameWorld::win:
            ui.renderWinScreen(winWidth, winHeight);
            break;
        case GameWorld::exit:
            exit(0);
    }
}

void timer(int val) {
    glutPostRedisplay();
    glutTimerFunc(0, timer, 0);
}

void reshape(GLint width, GLint height) {
    winWidth  = width;
    winHeight = height;

    glViewport(0, 0, winWidth, winHeight);
    setClippingPlane();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
}

void clickHandler(int b, int s, int x, int y) {
    if (state == GameWorld::play) {
        gameWorld.clickHandler(b, s, x, y);

    } else if (b == GLUT_LEFT_BUTTON && s == GLUT_UP) {
        switch (state) {
            case GameWorld::menu:
                state = ui.chooseMenuOption(x, y);
                break;
            case GameWorld::select:
                state = ui.chooseCharacter(x, y);
                break;
            case GameWorld::over:
            case GameWorld::win:
                state = GameWorld::menu;
                break;
        }
    }
}

void keyboardHandler(unsigned char key, int x, int y) {
    gameWorld.keyboardHandler(key, x, y);
}

void specialHandler(int key, int x, int y) {
    if (key == GLUT_KEY_F1) {
        fullScreen = !fullScreen;
        if (fullScreen) {
            int left      = glutGet(GLUT_WINDOW_X);
            int top       = glutGet(GLUT_WINDOW_Y);
            int right     = left + glutGet(GLUT_WINDOW_WIDTH);
            int bottom    = top - glutGet(GLUT_WINDOW_HEIGHT);
            currentWindow = Bounds<int>(top, bottom, left, right);
            glutFullScreen();
        } else {
            glutReshapeWindow(currentWindow.right - currentWindow.left, currentWindow.top - currentWindow.bottom);
            glutPositionWindow(currentWindow.left, currentWindow.top);
        }
    }
}

void passiveMouseMotionHandler(int x, int y) {
    gameWorld.passiveMouseMotionHandler(x, y);
}

void endGame(bool won) {
    if (won) {
        state = GameWorld::win;
    } else {
        state = GameWorld::over;
    }
}

int main(int argc, char** argv) {
    // seed random numbers only once
    srand(static_cast<unsigned int>(time(nullptr)));

    currentTime = clock();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(150, 150);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Survival Game");

    glutMouseFunc(clickHandler);
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(specialHandler);
    glutPassiveMotionFunc(passiveMouseMotionHandler);

    glClearColor(0.1, 0.1, 0.1, 1.0);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    gameWorld.setEndGameCallback(endGame);

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}