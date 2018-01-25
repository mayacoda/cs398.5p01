
#include "GameWorld.h"

GameWorld::GameWorld(int m_width, int m_height) : m_width(m_width),
                                                  m_height(m_height) {
    for (int i = 0; i < 5; i++) {
        m_vehicles.push_back(new Vehicle(this,
                                         Vector2D<double>(randomRange(10, m_width - 10),
                                                          randomRange(10, m_height - 10)),
                                         Vector2D<double>(1, 1),
                                         Vector2D<double>(0, 0),
                                         Vector2D<double>(0, 0),
                                         Vector2D<double>(0, 0),
                                         1,
                                         5,
                                         5,
                                         1));
    }
}

void GameWorld::update() {
    // check if paused

    // smooth frame rate

    // update all vehicles
}

/**
 * Is assumed to be in GLUT display function context
 */
void GameWorld::render() {

    for (unsigned int i=0; i<m_vehicles.size(); ++i) {
        m_vehicles[i]->render();
    }
}