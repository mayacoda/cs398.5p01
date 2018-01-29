
#include "GameWorld.h"

GameWorld::GameWorld(int m_width, int m_height) : m_width(m_width),
                                                  m_height(m_height) {
    for (int i = 0; i < 5; i++) {
        m_vehicles.push_back(new Vehicle(this,
                                         Vector2D<double>(randomRange(10, m_width - 10),
                                                          randomRange(10, m_height - 10)),
                                         Vector2D<double>(1, 1),
                                         Vector2D<double>(0, 300),
                                         Vector2D<double>(0, 1),
                                         Vector2D<double>(1, 0),
                                         1,
                                         1000,
                                         5,
                                         1));
    }
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
