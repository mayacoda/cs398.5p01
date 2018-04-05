
#include "UI.h"

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

    std::string text = "health: " + std::to_string(static_cast<long double>(m_world->getPlayerHealth()));

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

    std::string enemiesLeft = "enemies: " + std::to_string(static_cast<long double>(m_world->getCharacters().size() - 1));

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

        std::string enemyHealth = "health: " + std::to_string(static_cast<long double>(enemy->getHealth()));

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

    drawText("Game Over", bounds.right - width / 2 - 35, bounds.top - height / 2, Color(1, 1, 1));

    glutSwapBuffers();
    glFlush();
}

void UI::renderWinScreen(int width, int height) const {
    GameWorld::Boundaries bounds = m_world->getClippingBoundaries();
    glClearColor(0.1, 0.1, 0.1, 1.0);

    int xCenter = bounds.left + (width / 2);
    int yCenter = bounds.top - (height / 2);

    m_world->getPlayer()->drawSprite(xCenter - globals::SPRITE_SIZE / 2, yCenter - 50);
    drawText("You won!", xCenter - 35, yCenter, Color(1, 1, 1));

    glutSwapBuffers();
    glFlush();
}


void UI::renderLoading(int width, int height) const {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    GameWorld::Boundaries bounds = m_world->getClippingBoundaries();

    drawText("Loading...", bounds.right - width / 2 - 50, bounds.top - height / 2, Color(1, 1, 1));

    glutSwapBuffers();
    glFlush();
}