#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__

#include <GLUT/glut.h>
#endif

#include <iostream>
#include "GameWorld.h"
#include "../map/AStar.h"

GameWorld::GameWorld(int m_width, int m_height) : m_width(m_width),
                                                  m_height(m_height),
                                                  m_player(nullptr) {

    m_map = new Map(m_width, m_height);

    m_player = new Character(this,
                               Vector2D<double>(155, 155),
                               Vector2D<double>(1, 1),
                               Vector2D<double>(0, 0),
                               Vector2D<double>(0, 1),
                               Vector2D<double>(1, 0),
                               1,
                               50,
                               10,
                               1);
    m_player->m_color = Color(1.0, 1.0, 1.0);
    m_vehicles.push_back(m_player);
}

void GameWorld::update(double timeElapsed) {
    // check if paused

    // smooth frame rate

    // update all vehicles
    for (unsigned int i = 0; i < m_vehicles.size(); i++) {
        m_vehicles.at(i)->update(timeElapsed);
    }

    for (unsigned int i = 0; i < m_obstacles.size(); i++) {
        m_obstacles.at(i)->update(timeElapsed);
    }
}

/**
 * Is assumed to be in GLUT display function context
 */
void GameWorld::render() {

    m_map->render();

    for (unsigned int i = 0; i < m_vehicles.size(); i++) {
        m_vehicles.at(i)->render();
    }

    for (unsigned int i = 0; i < m_obstacles.size(); i++) {
        m_obstacles.at(i)->render();
    }

}

void GameWorld::setDimensions(int width, int height) {
    m_width  = width;
    m_height = height;
}

void GameWorld::clickHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        auto goal = m_map->getNodeByPosition(Vector2D<double>(m_Boundaries.left + x, m_Boundaries.top - y));
        auto start = m_map->getNodeByPosition(m_player->getPos());

        if (!goal->isTraversable()) return;

        Path* p = AStar::shortestPath(m_map->getGraph(), start, goal, m_player->getCostFunction());

        m_player->setPath(p);
        m_player->turnOnBehavior(SteeringBehaviors::fFollow_path);
    }
}

void setBehavior(const std::vector<Character*> &vehicles, SteeringBehaviors::behaviorType behavior) {
    for (unsigned int i = 0; i < vehicles.size(); i++) {
        vehicles.at(i)->turnOnBehavior(behavior);
    }
}

void GameWorld::keyboardHandler(unsigned char key, int x, int y) {}

void GameWorld::setClippingBoundaries(int left, int right, int bottom, int top) {
    m_Boundaries = Boundaries(left, right, bottom, top);
}
