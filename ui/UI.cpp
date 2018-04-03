
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

    std::string text = "health: " + std::to_string(m_world->getPlayerHealth());

    Character* player = m_world->getPlayer();
    player->drawSprite(bounds.left + 30, bounds.top - sprite - 30);

    drawText(text.c_str(),
             bounds.left + 40 + globals::SPRITE_SIZE,
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

        std::string enemyHealth = "health: " + std::to_string(enemy->getHealth());

        enemy->drawSprite(bounds.right - 170, bounds.top - sprite - 30);

        drawText(enemyHealth.c_str(),
                 bounds.right - 170 + globals::SPRITE_SIZE,
                 bounds.top - 50,
                 Color(1, 1, 1));

    }
}
