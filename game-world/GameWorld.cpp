#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__

#include <GLUT/glut.h>

#endif

#include <iostream>
#include "GameWorld.h"
#include "../map/AStar.h"
#include "../character/derived/Sneak.h"
#include "../character/derived/Thug.h"
#include "../character/derived/Runner.h"
#include "traps/VisibilityTrap.h"
#include "traps/MovementTrap.h"
#include "../geometry/geometry.h"

GameWorld::GameWorld(int m_width, int m_height) : m_width(m_width),
                                                  m_height(m_height),
                                                  m_player(nullptr) {

    m_map = new Map(m_width, m_height);

    m_enemy = nullptr;

    m_eventHub = new EventHub();

    auto obstacles = m_map->getObstacles();

    for (auto it = obstacles.begin(); it != obstacles.end(); ++it) {
        m_obstacles.push_back(new Obstacle((*it)->getPos(), (*it)->getBoundingRadius()));
    }
}

void GameWorld::update(double timeElapsed) {
    auto c = m_characters.begin();

    while (c != m_characters.end()) {
        if ((*c)->isDead()) {

            if ((*c)->getId() == m_player->getId()) {
                // player has died, end game
                callEndGameCallback(false);
                return;
            }

            if (m_enemy && (*c)->getId() == m_enemy->getId()) {
                m_enemy = nullptr;
            }

            m_eventHub->removeEntityFromList(*c);
            delete *c;
            c = m_characters.erase(c);
        } else {
            (*c)->update(timeElapsed);
            ++c;
        }
    }

    if (m_characters.size() == 1) {
        // if there is only one player, show win screen
        callEndGameCallback(true);
    }

    auto t = m_traps.begin();
    while (t != m_traps.end()) {
        if ((*t)->isDead()) {

            m_eventHub->removeEntityFromList(*t);
            delete *t;
            t = m_traps.erase(t);
        } else {
            (*t)->update(timeElapsed);
            ++t;
        }
    }

    auto it = m_projectiles.begin();

    while (it != m_projectiles.end()) {
        if ((*it)->isDead()) {

            m_eventHub->removeEntityFromList(*it);
            delete *it;
            it = m_projectiles.erase(it);
        } else {
            (*it)->update(timeElapsed);
            ++it;
        }
    }
}

/**
 * Is assumed to be in GLUT display function context
 */
void GameWorld::render() {

    m_map->render();

    for (unsigned int i = 0; i < m_characters.size(); i++) {
        m_characters.at(i)->render();
    }

    for (unsigned int i = 0; i < m_traps.size(); i++) {
        m_traps.at(i)->render();
    }

    if (globals::debug) {
        for (unsigned int i = 0; i < m_obstacles.size(); i++) {
            m_obstacles.at(i)->render();
        }
    }


    for (unsigned int i = 0; i < m_projectiles.size(); i++) {
        m_projectiles.at(i)->render();
    }

    glPushMatrix();
    glTranslatef(m_Boundaries.left + 10, m_Boundaries.bottom + 10, 0);
    glScalef(0.05, 0.05, 1);
    m_map->render();
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(m_Boundaries.left, m_Boundaries.bottom);
    glVertex2f(m_Boundaries.left, m_Boundaries.top);
    glVertex2f(m_Boundaries.right, m_Boundaries.top);
    glVertex2f(m_Boundaries.right, m_Boundaries.bottom);
    glEnd();

    glPointSize(2);
    glBegin(GL_POINTS);
    for (unsigned int i = 0; i < m_characters.size(); i++) {
        Character* c = m_characters.at(i);
        Vector2D<double> pos = c->getPos();
        glColor3f(1, 0, 0);
        if (c->isPlayerControlled()) glColor3f(0.1, 0.1, 0.1);
        glVertex2d(pos.x, pos.y);
    }
    glEnd();

    glPopMatrix();
}

Vector2D<double> GameWorld::windowPointToWorldSpace(int x, int y) const {
    return Vector2D<double>(m_Boundaries.left + x, m_Boundaries.top - y);
}


Character* GameWorld::characterAtWindowPoint(int x, int y) const {
    Vector2D<double> pos = windowPointToWorldSpace(x, y);

    for (auto it = m_characters.begin(); it != m_characters.end(); ++it) {
        if ((*it)->isInBounds(pos)) return *it;
    }

    return nullptr;
}

void GameWorld::clickHandler(int button, int state, int x, int y) {
    const Vector2D<double> &pos = windowPointToWorldSpace(x, y);

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {

    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        auto goal = m_map->getNodeByPosition(pos);
        if (!goal->isTraversable()) return;

        auto start = m_map->getNodeByPosition(m_player->getPos());

        Path* p = AStar::shortestPath(m_map->getGraph(), start, goal, m_player->getCostFunction());

        m_player->setPath(p);
        m_player->turnOnBehavior(SteeringBehaviors::fFollow_path);
    }
}

void GameWorld::keyboardHandler(unsigned char key, int x, int y) {
    Vector2D<double> pos = windowPointToWorldSpace(x, y);
    if (key == ' ' && m_player) {
        if (m_player->closeEnoughToAttackMelee(pos)) {
            m_player->attackMelee(pos);
        } else if (m_player->closeEnoughToAttackRanged(pos)) {
            m_player->attackRanged(pos);
        }
    }
}

void GameWorld::passiveMouseMotionHandler(int x, int y) {
    if (!m_player) return;
    const Vector2D<double> &pos = windowPointToWorldSpace(x, y);
    m_player->turnToFace(pos);

    Character* enemy = characterAtWindowPoint(x, y);
    m_enemy = enemy && enemy->getId() != m_player->getId() ? enemy : nullptr;
}

void GameWorld::setClippingBoundaries(int left, int right, int bottom, int top) {
    m_Boundaries = Boundaries(left, right, bottom, top);
}

Vector2D<double> GameWorld::randomTraversableLocation() const {
    MapNode* node;
    Vector2D<double> vec;

    do {
        int x = iRandomRange(0, m_width);
        int y = iRandomRange(0, m_height);
        vec  = Vector2D<double>(x, y);
        node = getNodeByPosition(vec);

    } while (!node->isTraversable());

    return vec;
}

void GameWorld::initializeWorld() {
    // get rid of characters from a previous run if necessary
    m_characters.clear();
    m_eventHub->clear();

    for (int i = 0; i < 2; i++) {
        Character* sneak = new Sneak(this,
                                     randomTraversableLocation(),
                                     Vector2D<double>(1, 1),
                                     Vector2D<double>(0, 0),
                                     Vector2D<double>(0, 1),
                                     Vector2D<double>(1, 0));

        Character* thug = new Thug(this,
                                   randomTraversableLocation(),
                                   Vector2D<double>(1, 1),
                                   Vector2D<double>(0, 0),
                                   Vector2D<double>(0, 1),
                                   Vector2D<double>(1, 0));

        Character* runner = new Runner(this,
                                       randomTraversableLocation(),
                                       Vector2D<double>(1, 1),
                                       Vector2D<double>(0, 0),
                                       Vector2D<double>(0, 1),
                                       Vector2D<double>(1, 0));

        m_characters.push_back(sneak);
        m_characters.push_back(thug);
        m_characters.push_back(runner);

        m_eventHub->addEntityToList(sneak);
        m_eventHub->addEntityToList(thug);
        m_eventHub->addEntityToList(runner);
    }

    for (int i = 0; i < 5; i++) {
        Trap* t = new VisibilityTrap(this, randomTraversableLocation());
        m_traps.push_back(t);
        m_eventHub->addEntityToList(t);
    }

    for (int i = 0; i < 5; i++) {
        Trap* t = new MovementTrap(this, randomTraversableLocation());
        m_traps.push_back(t);
        m_eventHub->addEntityToList(t);
    }
}


void GameWorld::selectCharacter(GameWorld::characterClass aClass) {
    initializeWorld();

    switch (aClass) {
        case runnerClass:
            m_player = new Runner(this,
                                  randomTraversableLocation(),
                                  Vector2D<double>(1, 1),
                                  Vector2D<double>(0, 0),
                                  Vector2D<double>(0, 1),
                                  Vector2D<double>(1, 0));
            break;
        case thugClass:
            m_player = new Thug(this,
                                randomTraversableLocation(),
                                Vector2D<double>(1, 1),
                                Vector2D<double>(0, 0),
                                Vector2D<double>(0, 1),
                                Vector2D<double>(1, 0));
            break;
        case sneakClass:
            m_player = new Sneak(this,
                                 randomTraversableLocation(),
                                 Vector2D<double>(1, 1),
                                 Vector2D<double>(0, 0),
                                 Vector2D<double>(0, 1),
                                 Vector2D<double>(1, 0));
            break;
    }

    m_player->setAutonomousTurning(true);
    m_player->turnOnBehavior(SteeringBehaviors::fAvoid_obs);
    m_characters.push_back(m_player);
    m_eventHub->addEntityToList(m_player);

    // turn on bots
    for (auto it = m_characters.begin(); it != m_characters.end(); ++it) {
        // if the bot is controlled by the player, don't turn on default behavior
        if ((*it)->getId() != m_player->getId()) {
            (*it)->turnOnDefaultBehavior();
        }

        // for every characters, add all other characters as antagonists
        for (auto en = m_characters.begin(); en != m_characters.end(); ++en) {
            if ((*it)->getId() != (*en)->getId()) {
                (*it)->addAntagonist(*en);
            }
        }
    }
}

Obstacle* GameWorld::firstObsBetweenPoints(Vector2D<double> a, Vector2D<double> b) {
    for (auto it = m_obstacles.begin(); it != m_obstacles.end(); ++it) {
        const Vector2D<double> &point = (*it)->getPos();
        double                 d      = distanceSqToLineSegment(b, a, point);
        double                 radius = (*it)->getBoundingRadius();
        if (d < (radius * radius)) {
            return *it;
        }
    }

    return nullptr;
}
