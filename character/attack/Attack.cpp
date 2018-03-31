
#include "Attack.h"
#include "../../game-world/GameWorld.h"
#include "../../geometry/geometry.h"

#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__
#endif

Attack::Attack(const Character* shooter,
               double maxSpeed,
               double range,
               double damage) : MovingEntity(shooter->getPos(),
                                             2,
                                             Vector2D<double>(1, 1),
                                             shooter->getHeading() * maxSpeed,
                                             shooter->getHeading(),
                                             shooter->getSide(),
                                             1,
                                             maxSpeed,
                                             1,
                                             1),
                                m_range(range),
                                m_shooter(shooter),
                                m_impacted(false),
                                m_dead(false),
                                m_damage(damage),
                                m_timeTillDeath(0) {

    m_world  = shooter->getWorld();
    m_origin = shooter->getPos();
}

void Attack::update(double timeElapsed) {
    m_velocity = m_heading * m_maxSpeed;

    m_velocity.truncate(m_maxSpeed);

    Vector2D<double> prevPos = m_pos;

    m_pos += m_velocity * timeElapsed;

    if (m_impacted) {
        countdown(timeElapsed);
        return;
    };

    Character* closest = nullptr;
    double closestDist = std::numeric_limits<double>::infinity();

    auto characters = m_world->getCharacters();

    for (auto it = characters.begin(); it != characters.end(); ++it) {
        if ((*it)->getId() == m_shooter->getId()) continue;
        auto character = *it;
        if (distanceToLineSegment(m_pos, prevPos, character->getPos()) <
            character->getBoundingRadius()) {
            double dist = character->getPos().distanceTo(m_origin);
            if (dist < closestDist) {
                closest     = character;
                closestDist = dist;
            }
        }
    }

    if (closest) {
        closest->dealDamage(m_damage);
        m_impacted = true;
    }
}

void Attack::render() const {
    if (m_impacted && !m_dead) {
        glPointSize(10);
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
        glVertex2d(m_pos.x, m_pos.y);
        glEnd();

    } else {
        glPointSize(2);
        glColor3f(0, 0, 0);
        glBegin(GL_POINTS);
        glVertex2d(m_pos.x, m_pos.y);
        glEnd();
    }
}

void Attack::countdown(double time) {
    m_timeTillDeath += time;

    if (m_timeTillDeath >= .5) {
        m_dead = true;
    }
}
