#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__

#include <GLUT/glut.h>
#include <iostream>

#endif


#include "GameWorld.h"

GameWorld::GameWorld(int m_width, int m_height) : m_width(m_width),
                                                  m_height(m_height), m_player(nullptr) {
    Vehicle* first = new Vehicle(this,
                                 Vector2D<double>(300, 250),
                                 Vector2D<double>(1, 1),
                                 Vector2D<double>(0, 0),
                                 Vector2D<double>(0, 1),
                                 Vector2D<double>(1, 0),
                                 1,
                                 50,
                                 10,
                                 1);

    Vehicle* second = new Vehicle(this,
                                  Vector2D<double>(200, 300),
                                  Vector2D<double>(1, 1),
                                  Vector2D<double>(0, 0),
                                  Vector2D<double>(0, 1),
                                  Vector2D<double>(1, 0),
                                  1,
                                  50,
                                  10,
                                  1);

    Vehicle* third = new Vehicle(this,
                                 Vector2D<double>(100, 500),
                                 Vector2D<double>(1, 1),
                                 Vector2D<double>(0, 0),
                                 Vector2D<double>(0, 1),
                                 Vector2D<double>(1, 0),
                                 1,
                                 50,
                                 10,
                                 1);
    m_vehicles.push_back(first);
    m_vehicles.push_back(second);
    m_vehicles.push_back(third);

    first->m_color  = Vehicle::Color(0, 0, 1.0);
    second->m_color = Vehicle::Color(0, 1.0, 0);
    third->m_color  = Vehicle::Color(1.0, 0, 0);

    second->setLeaderAndOffset(first, Vector2D<double>(60., 60));
    third->setLeaderAndOffset(first, Vector2D<double>(-60., -60.));

    first->turnOnBehavior(SteeringBehaviors::fAvoid_obs);

    second->turnOnBehavior(SteeringBehaviors::fOffset_pursuit);
    second->turnOnBehavior(SteeringBehaviors::fAvoid_obs);

    third->turnOnBehavior(SteeringBehaviors::fOffset_pursuit);
    third->turnOnBehavior(SteeringBehaviors::fAvoid_obs);

    m_player = first;

    for (int i = 0; i < 10; i++) {
        m_obstacles.push_back(new Obstacle(iRandomRange(20, m_width + 20),
                                           iRandomRange(20, m_height + 20),
                                           fRandomRange(30, 100)));
    }
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

    if (m_player && button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        m_player->turnOnBehavior(SteeringBehaviors::fArrive);
        m_player->setDestination(Vector2D<double>(x, m_height - y));
    }
}
