
#include "Vehicle.h"
#include <GLUT/glut.h>

Vehicle::~Vehicle() {

}

void Vehicle::update(double timeElapsed) {
    Vector2D<double> oldPos = m_pos;

    m_timeElapsed = timeElapsed;

    Vector2D<double> steeringForce = m_steeringBehavior->calculate();

    Vector2D<double> acceleration = steeringForce / m_mass;

    m_velocity += acceleration * timeElapsed;

    m_velocity.truncate(m_maxSpeed);

    if (m_velocity.squareMagnitude() > 0.00000001) {
        m_heading = m_velocity.normalize();

        m_side = m_heading.ortho();
    }

    // visualization stuff
}


void Vehicle::render() {
    glBegin(GL_TRIANGLES);
        glColor3f(1, 1, 0);
        glVertex2d(m_pos.x, m_pos.y);
        glVertex2d(m_pos.x + 10, m_pos.y);
        glVertex2d(m_pos.x, m_pos.y + 10);
    glEnd();

}

Vehicle::Vehicle(GameWorld *m_world,
                 const Vector2D<double> &pos,
                 const Vector2D<double> &scale,
                 const Vector2D<double> &m_velocity,
                 const Vector2D<double> &m_heading,
                 const Vector2D<double> &m_side,
                 double m_mass,
                 double m_maxSpeed,
                 double m_maxForce,
                 double m_maxTurnRate) : MovingEntity(pos, scale,
                                                      m_velocity,
                                                      m_heading,
                                                      m_side,
                                                      m_mass,
                                                      m_maxSpeed,
                                                      m_maxForce,
                                                      m_maxTurnRate),
                                         m_world(m_world) {

}
