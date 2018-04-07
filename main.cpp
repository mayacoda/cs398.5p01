#include <iostream>
#include <ctime>
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

bool gameStarted = false;
bool gameEnded   = false;
bool gameWon     = false;
bool gameLoading = false;

int winWidth  = 800;
int winHeight = 460;

int       worldWidth  = 3200;
int       worldHeight = 2560;
GameWorld gameWorld(worldWidth, worldHeight);
UI        ui(&gameWorld);

double t  = 0.0;
double dt = 0.0166666666666667;

clock_t currentTime;

Bounds<int> characters[3];

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

void showCharacterSelection() {
    int x = winWidth / 2 - 70;
    int y = winHeight - 100;

    drawText("Select a character", x, y, Color(1, 1, 1));

    drawSpriteWithMask(Thug::getSpritePath(),
                       Thug::getMaskPath(),
                       characters[GameWorld::thugClass].left,
                       characters[GameWorld::thugClass].bottom);
    drawText("Thug",
             characters[GameWorld::thugClass].left - 10,
             characters[GameWorld::thugClass].bottom - 20,
             Color(1, 1, 1));

    drawSpriteWithMask(Sneak::getSpritePath(),
                       Sneak::getMaskPath(),
                       characters[GameWorld::sneakClass].left,
                       characters[GameWorld::sneakClass].bottom);
    drawText("Sneak",
             characters[GameWorld::sneakClass].left - 10,
             characters[GameWorld::sneakClass].bottom - 20,
             Color(1, 1, 1));

    drawSpriteWithMask(Runner::getSpritePath(),
                       Runner::getMaskPath(),
                       characters[GameWorld::runnerClass].left,
                       characters[GameWorld::runnerClass].bottom);
    drawText("Runner",
             characters[GameWorld::runnerClass].left - 10,
             characters[GameWorld::runnerClass].bottom - 20,
             Color(1, 1, 1));


    glutSwapBuffers();
    glFlush();
}

void chooseCharacter(int x, int y) {
    // check which character is underneath the coordinates (if any)
    int i;
    for (i = 0; i < 3; i++) {
        if (characters[i].isInBounds(x, y)) break;
    }

    if (i == 3) return;

    if (globals::debug) std::cout << "chose character: " << i << std::endl;
    // indicate to game world that it should begin
    gameWorld.selectCharacter(static_cast<GameWorld::characterClass> (i));

    gameStarted = true;
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!gameStarted) {
        showCharacterSelection();
        return;
    }

    if (gameWon) {
        ui.renderWinScreen(winWidth, winHeight);
        return;
    }

    if (gameEnded) {
        ui.renderGameOver(winWidth, winHeight);
        return;
    }

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
    if (gameStarted && !gameEnded) {
        gameWorld.clickHandler(b, s, x, y);

    } else if (!gameEnded && b == GLUT_LEFT_BUTTON && s == GLUT_UP) {
        // choose character clicked on (if any) and initialize game
        chooseCharacter(x, y);
    }
}

void keyboardHandler(unsigned char key, int x, int y) {
    gameWorld.keyboardHandler(key, x, y);
}

void passiveMouseMotionHandler(int x, int y) {
    gameWorld.passiveMouseMotionHandler(x, y);
}

void endGame(bool won) {
    gameEnded = true;
    gameWon   = won;
}

int main(int argc, char** argv) {
    // seed random numbers only once
    srand(static_cast<unsigned int>(time(nullptr)));

    currentTime = clock();

    int top    = winHeight / 2 + globals::SPRITE_SIZE / 2;
    int bottom = winHeight / 2 - globals::SPRITE_SIZE / 2;
    characters[GameWorld::thugClass]   = Bounds<int>(top,
                                                     bottom,
                                                     winWidth * 0.25 - globals::SPRITE_SIZE / 2,
                                                     winWidth * 0.25 + globals::SPRITE_SIZE / 2);
    characters[GameWorld::sneakClass]  = Bounds<int>(top,
                                                     bottom,
                                                     winWidth * 0.5 - globals::SPRITE_SIZE / 2,
                                                     winWidth * 0.5 + globals::SPRITE_SIZE / 2);
    characters[GameWorld::runnerClass] = Bounds<int>(top,
                                                     bottom,
                                                     winWidth * 0.75 - globals::SPRITE_SIZE / 2,
                                                     winWidth * 0.75 + globals::SPRITE_SIZE / 2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(150, 150);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Survival Game");

    glutMouseFunc(clickHandler);
    glutKeyboardFunc(keyboardHandler);
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