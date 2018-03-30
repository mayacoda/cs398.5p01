
#include "Attack.h"

#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__
#endif

Attack::Attack(const Character* shooter,
               double maxSpeed,
               double range) : MovingEntity(shooter->getPos(),
                                            2,
                                            Vector2D<double>(1, 1),
                                            shooter->getHeading() * maxSpeed,
                                            shooter->getHeading(),
                                            shooter->getSide(),
                                            1,
                                            maxSpeed,
                                            1,
                                            1), m_range(range) {}

void Attack::update(double timeElapsed) {
    m_velocity = m_heading * m_maxSpeed;

    m_velocity.truncate(m_maxSpeed);

    m_pos += m_velocity * timeElapsed;

    //@todo test for impact
}

void Attack::render() const {
    // @todo different render based on if there was impact
    glPointSize(10);
    glColor3f(0, 0, 0);
    glBegin(GL_POINTS);
    glVertex2d(m_pos.x, m_pos.y);
    glEnd();
}
