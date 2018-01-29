
#include "Vehicle.h"
#include <GLUT/glut.h>
#include "GameWorld.h"

Vehicle::~Vehicle() = default;

void Vehicle::update(double timeElapsed) {
    Vector2D<double> oldPos = m_pos;

    m_timeElapsed = timeElapsed;

    Vector2D<double> steeringForce = m_steeringBehavior->calculate();

    Vector2D<double> acceleration = steeringForce / m_mass;

    m_velocity += acceleration * timeElapsed;

    m_velocity.truncate(m_maxSpeed);

    m_pos += m_velocity * timeElapsed;

    m_pos.wrapAround(m_world->getWidth(), m_world->getHeight());

    if (m_velocity.squareMagnitude() > 0.00000001) {
        m_heading = m_velocity.normalize();

        m_side = m_heading.ortho();
    }
}


void Vehicle::render() {

    // angle between the direction in which the vehicle is rotated
    // and the positive x-axis
    double angle = r2d(m_heading.angle(Vector2D<double>(1, 0)));

    glPushMatrix();

    glTranslated(m_pos.x, m_pos.y, 0.0);
    glRotated(angle, 0.0, 0.0, 1.0);

    glColor3f(0.5, 0.2, 0);
    glBegin(GL_TRIANGLES);
        glVertex2d(-10, 15);
        glVertex2d(-10, -15);
        glVertex2d(20, 0.0);
    glEnd();

    glPopMatrix();

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
