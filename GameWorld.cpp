#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__

#include <GLUT/glut.h>
#include <iostream>

#endif


#include "GameWorld.h"

GameWorld::GameWorld(int m_width, int m_height) : m_width(m_width),
                                                  m_height(m_height), m_player(nullptr) {
    Vehicle* blue = new Vehicle(this,
                                 Vector2D<double>(300, 250),
                                 Vector2D<double>(1, 1),
                                 Vector2D<double>(0, 0),
                                 Vector2D<double>(0, 1),
                                 Vector2D<double>(1, 0),
                                 1,
                                 150,
                                 10,
                                 1);

    Vehicle* green = new Vehicle(this,
                                  Vector2D<double>(200, 300),
                                  Vector2D<double>(1, 1),
                                  Vector2D<double>(0, 0),
                                  Vector2D<double>(0, 1),
                                  Vector2D<double>(1, 0),
                                  1,
                                  150,
                                  10,
                                  1);

    Vehicle* red = new Vehicle(this,
                                 Vector2D<double>(100, 500),
                                 Vector2D<double>(1, 1),
                                 Vector2D<double>(0, 0),
                                 Vector2D<double>(0, 1),
                                 Vector2D<double>(1, 0),
                                 1,
                                 150,
                                 10,
                                 1);
    m_vehicles.push_back(blue);
    m_vehicles.push_back(green);
    m_vehicles.push_back(red);

    blue->m_color  = Vehicle::Color(0, 0, 1.0);
    green->m_color = Vehicle::Color(0, 1.0, 0);
    red->m_color  = Vehicle::Color(1.0, 0, 0);

    blue->turnOnBehavior(SteeringBehaviors::fAvoid_obs);
    green->turnOnBehavior(SteeringBehaviors::fAvoid_obs);
    red->turnOnBehavior(SteeringBehaviors::fAvoid_obs);

    m_player  = blue;
    m_player2 = green;

    red->turnOnBehavior(SteeringBehaviors::fInterpose);
    red->interposeVehicles(blue, green);

//    for (int i = 0; i < 10; i++) {
//        m_obstacles.push_back(new Obstacle(iRandomRange(20, m_width + 20),
//                                           iRandomRange(20, m_height + 20),
//                                           fRandomRange(30, 100)));
//    }
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

    if (m_player2 && button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        m_player2->turnOnBehavior(SteeringBehaviors::fArrive);
        m_player2->setDestination(Vector2D<double>(x, m_height - y));
    }
}
