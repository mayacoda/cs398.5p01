
#ifndef DZ04_VEHICLE_H
#define DZ04_VEHICLE_H


#include "MovingEntity.h"
#include "SteeringBehaviors.h"

class GameWorld;

class Vehicle : public MovingEntity {
private:
    GameWorld *m_world;
    SteeringBehaviors *m_steeringBehavior;

    Vector2D<float> m_steeringForce;

    double m_timeElapsed;

public:
	~Vehicle() {};

    Vehicle(GameWorld *m_world,
            const Vector2D<float> &pos,
            const Vector2D<float> &scale,
            const Vector2D<float> &m_velocity,
            const Vector2D<float> &m_heading,
            const Vector2D<float> &m_side,
            double m_mass,
            double m_maxSpeed,
            double m_maxForce,
            double m_maxTurnRate);

    Vector2D<float> m_wanderTarget;

    Vector2D<float> getPos() { return m_pos; }

    Vector2D<float> getHeading() { return m_heading; }

    Vector2D<float> getSide() { return m_side; }

    const double getMaxSpeed() { return m_maxSpeed; }

    void update(double timeElapsed) override;

    void render() override;
};


#endif //DZ04_VEHICLE_H
