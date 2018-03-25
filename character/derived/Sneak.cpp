
#include "Sneak.h"

Sneak::Sneak(GameWorld* m_world,
             const Vector2D<double> &pos,
             const Vector2D<double> &scale,
             const Vector2D<double> &m_velocity,
             const Vector2D<double> &m_heading,
             const Vector2D<double> &m_side,
             double m_mass,
             double m_maxSpeed,
             double m_maxForce,
             double m_maxTurnRate) : Character(m_world,
                                               pos,
                                               scale,
                                               m_velocity,
                                               m_heading,
                                               m_side,
                                               m_mass,
                                               m_maxSpeed,
                                               m_maxForce,
                                               m_maxTurnRate) {}
