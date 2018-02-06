
#include "GameWorld.h"

GameWorld::GameWorld(int m_width, int m_height) : m_width(m_width),
                                                  m_height(m_height) {
        m_vehicles.push_back(new Vehicle(this,
                                         Vector2D<double>(100, 100),
                                         Vector2D<double>(1, 1),
                                         Vector2D<double>(0, 0),
                                         Vector2D<double>(0, 1),
                                         Vector2D<double>(1, 0),
                                         1,
                                         50,
                                         10,
                                         1));
}

void GameWorld::update(double timeElapsed) {
    // check if paused

    // smooth frame rate

    // update all vehicles
	for(unsigned int i = 0; i < m_vehicles.size(); i++) {
		m_vehicles.at(i)->update(timeElapsed);
    }
}

/**
 * Is assumed to be in GLUT display function context
 */
void GameWorld::render() {

	for(unsigned int i = 0; i < m_vehicles.size(); i++) {
		m_vehicles.at(i)->render();
    }
}

void GameWorld::setDimensions(int width, int height) {
    m_width = width;
    m_height = height;
}
