
#ifndef DZ04_SNEAK_H
#define DZ04_SNEAK_H


#include "../Character.h"

class Sneak: public Character {
public:
    Sneak(GameWorld* m_world,
          const Vector2D<double> &pos,
          const Vector2D<double> &scale,
          const Vector2D<double> &m_velocity,
          const Vector2D<double> &m_heading,
          const Vector2D<double> &m_side,
          double m_mass,
          double m_maxSpeed,
          double m_maxForce,
          double m_maxTurnRate);

};


#endif //DZ04_SNEAK_H
