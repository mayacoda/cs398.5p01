
#include "GameWorld.h"

GameWorld::GameWorld(int m_width, int m_height) : m_width(m_width),
                                                  m_height(m_height) {
    Vehicle* protagonist = new Vehicle(this,
                                       Vector2D<double>(300, 250),
                                       Vector2D<double>(1, 1),
                                       Vector2D<double>(0, 0),
                                       Vector2D<double>(0, 1),
                                       Vector2D<double>(1, 0),
                                       1,
                                       50,
                                       10,
                                       1);
    m_vehicles.push_back(protagonist);

    Vehicle* antagonist = new Vehicle(this,
                                       Vector2D<double>(200, 300),
                                       Vector2D<double>(1, 1),
                                       Vector2D<double>(0, 0),
                                       Vector2D<double>(0, 1),
                                       Vector2D<double>(1, 0),
                                       1,
                                       50,
                                       10,
                                       1);

    Vehicle* antagonist2 = new Vehicle(this,
                                      Vector2D<double>(100, 500),
                                      Vector2D<double>(1, 1),
                                      Vector2D<double>(0, 0),
                                      Vector2D<double>(0, 1),
                                      Vector2D<double>(1, 0),
                                      1,
                                      50,
                                      10,
                                      1);


    m_vehicles.push_back(antagonist);
    m_vehicles.push_back(antagonist2);
    protagonist->addAntagonist(antagonist);
    protagonist->addAntagonist(antagonist2);
    antagonist->m_color = Vehicle::Color(1.0, 0, 0);
    antagonist2->m_color = Vehicle::Color(1.0, 0, 0);


    antagonist->turnOnBehavior(SteeringBehaviors::fWander);
    antagonist2->turnOnBehavior(SteeringBehaviors::fWander);
    antagonist->turnOnBehavior(SteeringBehaviors::fAvoid_obs);
    antagonist2->turnOnBehavior(SteeringBehaviors::fAvoid_obs);

    protagonist->turnOnBehavior(SteeringBehaviors::fHide);
    protagonist->turnOnBehavior(SteeringBehaviors::fAvoid_obs);


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
