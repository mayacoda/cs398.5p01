
#include "GameWorld.h"

GameWorld::GameWorld(int m_width, int m_height) : m_width(m_width),
                                                  m_height(m_height) {
        m_vehicles.push_back(new Vehicle(this,
                                         Vector2D<float>(100, 100),
                                         Vector2D<float>(1, 1),
                                         Vector2D<float>(0, 0),
                                         Vector2D<float>(0, 1),
                                         Vector2D<float>(1, 0),
                                         1,
                                         1000,
                                         1000,
                                         1));
}

void GameWorld::update(double timeElapsed) {
    // check if paused

    // smooth frame rate

    // update all vehicles
    for (auto &m_vehicle : m_vehicles) {
        m_vehicle->update(timeElapsed);
    }
}

/**
 * Is assumed to be in GLUT display function context
 */
void GameWorld::render() {

    for (auto &m_vehicle : m_vehicles) {
        m_vehicle->render();
    }
}

void GameWorld::setDimensions(int width, int height) {
    m_width = width;
    m_height = height;
}
