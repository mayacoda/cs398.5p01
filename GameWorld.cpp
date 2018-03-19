#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__

#include <GLUT/glut.h>
#include <iostream>

#endif


#include "GameWorld.h"
#include "MapHelpers.h"
#include "AStar.h"

GameWorld::GameWorld(int m_width, int m_height) : m_width(m_width),
                                                  m_height(m_height),
                                                  m_player(nullptr) {

    map = new Map(m_width, m_height);

    m_player = new Vehicle(this,
                               Vector2D<double>(155, 155),
                               Vector2D<double>(1, 1),
                               Vector2D<double>(0, 0),
                               Vector2D<double>(0, 1),
                               Vector2D<double>(1, 0),
                               1,
                               20,
                               10,
                               1);
    m_player->m_color = Color(.8, .1, .3);
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

    map->render();

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
        auto node = map->getNodeByPosition(Vector2D<double>(x, m_height - y));
        auto start = map->getNodeByPosition(m_player->getPos());

        node->makeBlack();
        Path* p = AStar::shortestPath(map->getGraph(), start, node);

        m_player->setPath(p);
        m_player->turnOnBehavior(SteeringBehaviors::fFollow_path);
    }
}

void setBehavior(const std::vector<Vehicle*> &vehicles, SteeringBehaviors::behaviorType behavior) {
    for (unsigned int i = 0; i < vehicles.size(); i++) {
        vehicles.at(i)->turnOnBehavior(behavior);
    }
}

void GameWorld::keyboardHandler(unsigned char key, int x, int y) {}

