
#ifndef DZ04_VEHICLE_H
#define DZ04_VEHICLE_H


#include "MovingEntity.h"
#include "SteeringBehaviors.h"

class GameWorld;

class Vehicle : public MovingEntity {
private:
    GameWorld *m_world;
    SteeringBehaviors *m_steeringBehavior;

    double m_timeElapsed;

public:
    virtual ~Vehicle();

    Vehicle(GameWorld *m_world,
            const Vector2D<double> &pos,
            const Vector2D<double> &scale,
            const Vector2D<double> &m_velocity,
            const Vector2D<double> &m_heading,
            const Vector2D<double> &m_side,
            double m_mass,
            double m_maxSpeed,
            double m_maxForce,
            double m_maxTurnRate);

    void update(double timeElapsed) override;

    void render() override;
};


#endif //DZ04_VEHICLE_H
