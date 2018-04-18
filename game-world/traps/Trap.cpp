
#include "Trap.h"
#include "../../helpers/globals.h"
#include "../../graphics/opengl_helpers.h"
#include "../GameWorld.h"

Trap::Trap(GameWorld* world, const Vector2D<double> &pos) : BaseGameEntity(globals::trap, pos, 5),
                                                            m_world(world),
                                                            m_activationSqDistance(10000),
                                                            m_isAttached(false),
                                                            m_isDead(false),
                                                            m_duration(10),
                                                            m_color() {
}

void Trap::update(double timeElapsed) {
    if (!m_isAttached) {
        auto      chars = m_world->getCharacters();
        for (auto it    = chars.begin(); it != chars.end(); ++it) {
            if ((*it)->getPos().squareDistanceTo(m_pos) < m_activationSqDistance) {
                m_expirationTime = time(nullptr) + m_duration;
                m_victim         = *it;
                m_isAttached     = true;

                m_world->emit(Event(Event::trapAttach, m_pos, this, m_victim, (void*) &m_type));
            }
        }
    } else {
        if (m_expirationTime <= time(nullptr)) {
            m_isDead = true;
            m_world->emit(Event(Event::trapExpire, m_pos, this, m_victim, (void*) &m_type));

        }
    }
}

void Trap::render() const {
    if (!m_isAttached) {
        glColor3f(m_color.r, m_color.g, m_color.b);
        drawCircle(m_boundingRadius, m_pos);
    } else {
        glLineWidth(3);
        glColor3f(m_color.r, m_color.g, m_color.b);
        double elapsedPercentage = (m_expirationTime - time(nullptr)) / m_duration;
        drawPercentageOfCircle(m_victim->getBoundingRadius() + 5, elapsedPercentage, m_victim->getPos());
        glLineWidth(1);
    }
}

