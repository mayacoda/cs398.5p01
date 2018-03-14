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
    red->m_color   = Vehicle::Color(1.0, 0, 0);

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

    if (m_player2 && button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        m_player2->turnOnBehavior(SteeringBehaviors::fArrive);
        m_player2->setDestination(Vector2D<double>(x, m_height - y));
    }
}

void setBehavior(const std::vector<Vehicle*> &vehicles, SteeringBehaviors::behaviorType behavior) {
    for (unsigned int i = 0; i < vehicles.size(); i++) {
        vehicles.at(i)->turnOnBehavior(behavior);
    }
}

void GameWorld::keyboardHandler(unsigned char key, int x, int y) {
    Vehicle* blue  = m_vehicles.at(0);
    Vehicle* green = m_vehicles.at(1);
    Vehicle* red   = m_vehicles.at(2);
    m_activeBehavior = static_cast<behaviors>((int) key - '0');
    m_player = nullptr;
    m_player2 = nullptr;

    setBehavior(m_vehicles, SteeringBehaviors::none);

    switch (m_activeBehavior) {
        case wander: // wander
            setBehavior(m_vehicles, SteeringBehaviors::fWander);
            setBehavior(m_vehicles, SteeringBehaviors::fAvoid_obs);

            break;
        case pathFollow: // path following
            setBehavior(m_vehicles, SteeringBehaviors::fFollow_path);

            break;
        case hide: // hide
            setBehavior(m_vehicles, SteeringBehaviors::fAvoid_obs);
            blue->addAntagonist(red);
            blue->addAntagonist(green);

            blue->turnOnBehavior(SteeringBehaviors::fHide);
            m_player = green;
            m_player2 = red;

            break;
        case offsetPursuit: // offset pursuit
            setBehavior(m_vehicles, SteeringBehaviors::fAvoid_obs);

            green->setLeaderAndOffset(blue, Vector2D<double> (-100., -100.));
            green->turnOnBehavior(SteeringBehaviors::fOffset_pursuit);
            red->setLeaderAndOffset(blue, Vector2D<double> (-100., 100.));
            red->turnOnBehavior(SteeringBehaviors::fOffset_pursuit);

            m_player = blue;

            break;
        case interpose: // interpose
            m_player = green;
            m_player2 = red;

            blue->interposeVehicles(green, red);
            blue->turnOnBehavior(SteeringBehaviors::fInterpose);

            break;
        default:
            m_activeBehavior = GameWorld::none;

            std::cout << "GameWorld::keyboardHandler: unrecognized behavior" << std::endl;
    }
}

