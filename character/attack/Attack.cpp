
#include "Attack.h"
#include "../../game-world/GameWorld.h"
#include "../../geometry/geometry.h"

#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__
#endif

Attack::Attack(Character* shooter,
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

    if (m_pos.squareDistanceTo(m_origin) >= m_range * m_range) {
        m_dead = true;
        return;
    }

    Character* closest = nullptr;
    double closestDist = std::numeric_limits<double>::infinity();

    auto characters = m_world->getCharacters();

    for (auto it = characters.begin(); it != characters.end(); ++it) {
        if ((*it)->getId() == m_shooter->getId()) continue;
        auto character = *it;
        if (distanceToLineSegment(m_pos, prevPos, character->getPos()) <
            character->getBoundingRadius()) {

            double dist = character->getPos().squareDistanceTo(m_origin);
            if (dist < closestDist) {
                closest     = character;
                closestDist = dist;
            }
        }
    }

    if (closest) {
        m_victim = closest;
        m_world->emit(Event(Event::attack, m_pos, this, m_victim, static_cast<void*>(&m_damage)));
        m_world->emit(Event(Event::attackImpacted, m_pos, this, m_victim, nullptr));
        m_world->emit(Event(Event::attackImpacted, m_pos, this, m_shooter, nullptr));
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
        glPointSize(3);
        glColor3f(1, 1, 1);
        glBegin(GL_POINTS);
        glVertex2d(m_pos.x, m_pos.y);
        glEnd();
    }
}

void Attack::countdown(double time) {
    m_timeTillDeath += time;

    if (m_timeTillDeath >= .5) {
        m_dead = true;
        // both shooter and victim might have died in the meantime.
        // @todo refactor to use smart pointers here instead of raw pointers, so setting to null isn't necessary
        // https://stackoverflow.com/questions/15730827/how-to-detect-if-a-pointer-was-deleted-and-securely-delete-it
        if (m_victim) {
            m_world->emit(Event(Event::attackEnded, m_pos, this, m_victim, nullptr));
        }
        if (m_shooter) {
            m_world->emit(Event(Event::attackEnded, m_pos, this, m_shooter, nullptr));
        }
    }
}

void Attack::notify(Event e) {
    if (e.type == Event::enemyKill) {
        if (e.sender == m_victim) m_victim   = nullptr;
        if (e.sender == m_shooter) m_shooter = nullptr;
    }
}

