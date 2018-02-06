
#ifndef DZ04_MOVINGENTITY_H
#define DZ04_MOVINGENTITY_H


#include "BaseGameEntity.h"

class MovingEntity : public BaseGameEntity {
protected:
    Vector2D<float> m_velocity;
    Vector2D<float> m_heading;
    Vector2D<float> m_side;

    double m_mass;
    double m_maxSpeed;
    double m_maxForce;
    double m_maxTurnRate;


public:
    ~MovingEntity() override = default;

    MovingEntity(const Vector2D<float> &pos,
                 const Vector2D<float> &scale,
                 const Vector2D<float> &m_velocity,
                 const Vector2D<float> &m_heading,
                 const Vector2D<float> &m_side,
                 double m_mass,
                 double m_maxSpeed,
                 double m_maxForce,
                 double m_maxTurnRate) : BaseGameEntity(pos, scale),
                                         m_velocity(m_velocity),
                                         m_heading(m_heading),
                                         m_side(m_side),
                                         m_mass(m_mass),
                                         m_maxSpeed(m_maxSpeed),
                                         m_maxForce(m_maxForce),
                                         m_maxTurnRate(m_maxTurnRate) {}

    Vector2D<float> getVelocity() const { return m_velocity; };
};


#endif //DZ04_MOVINGENTITY_H
