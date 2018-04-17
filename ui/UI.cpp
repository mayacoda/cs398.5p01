
#include "UI.h"
#include "../character/derived/Thug.h"
#include "../character/derived/Sneak.h"
#include "../character/derived/Runner.h"

UI::UI(GameWorld* m_world) : m_world(m_world) {}

void UI::renderHUD() const {
    GameWorld::Boundaries bounds = m_world->getClippingBoundaries();
    int                   sprite = globals::SPRITE_SIZE;

    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(bounds.left + 20, bounds.top - 20);
    glVertex2f(bounds.left + 20, bounds.top - sprite - 40);
    glVertex2f(bounds.left + 180, bounds.top - sprite - 40);
    glVertex2f(bounds.left + 180, bounds.top - 20);
    glEnd();

    std::string text = "health: " + toString(m_world->getPlayerHealth());

    Character* player = m_world->getPlayer();
    player->drawSprite(bounds.left + 30, bounds.top - sprite - 30);

    drawText(text.c_str(),
             bounds.left + 40 + globals::SPRITE_SIZE,
             bounds.top - 50,
             Color(1, 1, 1));

    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(bounds.left + 200, bounds.top - 20);
    glVertex2f(bounds.left + 200, bounds.top - sprite - 40);
    glVertex2f(bounds.left + 320, bounds.top - sprite - 40);
    glVertex2f(bounds.left + 320, bounds.top - 20);
    glEnd();


    std::string enemiesLeft = "enemies: " + toString(m_world->getCharacters().size() - 1);

    drawText(enemiesLeft.c_str(),
             bounds.left + 215,
             bounds.top - 50,
             Color(1, 1, 1));

    if (Character* enemy = m_world->getEnemy()) {

        glColor3f(0.7, 0.1, 0.1);
        glBegin(GL_POLYGON);
        glVertex2f(bounds.right - 20, bounds.top - 20);
        glVertex2f(bounds.right - 20, bounds.top - sprite - 40);
        glVertex2f(bounds.right - 180, bounds.top - sprite - 40);
        glVertex2f(bounds.right - 180, bounds.top - 20);
        glEnd();

        std::string enemyHealth = "health: " + toString(enemy->getHealth());

        enemy->drawSprite(bounds.right - 170, bounds.top - sprite - 30);

        drawText(enemyHealth.c_str(),
                 bounds.right - 170 + globals::SPRITE_SIZE,
                 bounds.top - 50,
                 Color(1, 1, 1));

    }
}

void UI::renderGameOver(int width, int height) const {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    GameWorld::Boundaries bounds = m_world->getClippingBoundaries();


    int xCenter = bounds.left + (width / 2);
    int yCenter = bounds.top - (height / 2);


    drawText("Game Over", xCenter - 35, yCenter, Color(1, 1, 1));
    drawText("<click to continue>", xCenter - 65, yCenter - 40, Color(1, 1, 1));

    glutSwapBuffers();
    glFlush();
}

void UI::renderWinScreen(int width, int height) const {
    GameWorld::Boundaries bounds = m_world->getClippingBoundaries();
    glClearColor(0.1, 0.1, 0.1, 1.0);

    int xCenter = bounds.left + (width / 2);
    int yCenter = bounds.top - (height / 2);

    m_world->getPlayer()->drawSprite(xCenter - globals::SPRITE_SIZE / 2, yCenter + globals::SPRITE_SIZE);
    drawText("You won!", xCenter - 35, yCenter, Color(1, 1, 1));
    drawText("<click to continue>", xCenter - 65, yCenter - 40, Color(1, 1, 1));

    glutSwapBuffers();
    glFlush();
}

void UI::renderCharacterSelection(int width, int height) const {
    GameWorld::Boundaries bounds = m_world->getClippingBoundaries();
    calculateCharacterPositions(width, height);

    int x = bounds.left + (width / 2) - 70;
    int y = bounds.top - 100;

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

void UI::calculateCharacterPositions(int width, int height) const {
    GameWorld::Boundaries bounds = m_world->getClippingBoundaries();

    int w1 = bounds.left + width * 0.25;
    int w2 = bounds.left + width * 0.5;
    int w3 = bounds.left + width * 0.75;


    int top    = bounds.top - (height / 2) + (globals::SPRITE_SIZE / 2);
    int bottom = bounds.top - (height / 2) - (globals::SPRITE_SIZE / 2);
    characters[GameWorld::thugClass]   = Bounds<int>(top,
                                                     bottom,
                                                     w1 - globals::SPRITE_SIZE / 2,
                                                     w1 + globals::SPRITE_SIZE / 2);
    characters[GameWorld::sneakClass]  = Bounds<int>(top,
                                                     bottom,
                                                     w2 - globals::SPRITE_SIZE / 2,
                                                     w2 + globals::SPRITE_SIZE / 2);
    characters[GameWorld::runnerClass] = Bounds<int>(top,
                                                     bottom,
                                                     w3 - globals::SPRITE_SIZE / 2,
                                                     w3 + globals::SPRITE_SIZE / 2);
}

void UI::renderMenu(int width, int height) const {
    calculateMenuPositions(width, height);

    GameWorld::Boundaries bounds = m_world->getClippingBoundaries();
    glClearColor(0.1, 0.1, 0.1, 1.0);

    int xCenter = bounds.left + (width / 2);

    glColor3f(1, 1, 1);
    Bounds<int> newGame = menuOptions[0];
    glBegin(GL_POLYGON);
    glVertex2f(newGame.left, newGame.top);
    glVertex2f(newGame.left, newGame.bottom);
    glVertex2f(newGame.right, newGame.bottom);
    glVertex2f(newGame.right, newGame.top);
    glEnd();
    drawText("New Game", xCenter - 43, newGame.bottom + 15, Color(0, 0, 0));


    glColor3f(1, 1, 1);
    Bounds<int> exit = menuOptions[1];
    glBegin(GL_POLYGON);
    glVertex2f(exit.left, exit.top);
    glVertex2f(exit.left, exit.bottom);
    glVertex2f(exit.right, exit.bottom);
    glVertex2f(exit.right, exit.top);
    glEnd();
    drawText("Exit", xCenter - 15, exit.bottom + 15, Color(0, 0, 0));

    glutSwapBuffers();
    glFlush();
}

GameWorld::gameState UI::chooseCharacter(int x, int y) const {
    GameWorld::Boundaries bounds = m_world->getClippingBoundaries();

    x = bounds.left + x;
    y = bounds.top - y;

    // check which character is underneath the coordinates (if any)
    int i;
    for (i = 0; i < 3; i++) {
        if (characters[i].isInBounds(x, y)) break;
    }

    if (i == 3) return GameWorld::select;

    if (globals::debug) std::cout << "chose character: " << i << std::endl;
    m_world->selectCharacter(static_cast<GameWorld::characterClass> (i));

    return GameWorld::play;
}

GameWorld::gameState UI::chooseMenuOption(int x, int y) const {
    GameWorld::Boundaries bounds = m_world->getClippingBoundaries();

    x = bounds.left + x;
    y = bounds.top - y;

    if (menuOptions[0].isInBounds(x, y)) return GameWorld::select;

    if (menuOptions[1].isInBounds(x, y)) return GameWorld::exit;

    return GameWorld::menu;
}

void UI::calculateMenuPositions(int width, int height) const {
    GameWorld::Boundaries bounds = m_world->getClippingBoundaries();

    int xCenter = bounds.left + (width / 2);
    int yCenter = bounds.top - (height / 2);

    menuOptions[0].setBounds(yCenter + 30, yCenter - 15, xCenter - 60, xCenter + 60);
    menuOptions[1].setBounds(yCenter - 30, yCenter - 75, xCenter - 60, xCenter + 60);
}
