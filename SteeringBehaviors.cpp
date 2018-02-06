
#include "SteeringBehaviors.h"
#include "Vehicle.h"
#include "geometry.h"

SteeringBehaviors::SteeringBehaviors(Vehicle *m_vehicle) : m_vehicle(m_vehicle),
                                                           m_steeringForce(Vector2D<float>(0.0, 0.0)),
                                                           m_wanderTarget(Vector2D<float>(0.0, 0.0)) {


    double theta = fRandomRange(-1, 1) * 2.0 * M_PI;  // range from -2pi to 2pi
    m_wanderTarget = Vector2D<float>(m_wanderRadius * cos(theta), m_wanderRadius * sin(theta));
}

Vector2D<float> SteeringBehaviors::calculate() {
    return wander();
}

Vector2D<float> SteeringBehaviors::seek(Vector2D<float> target) {
    Vector2D<float> desiredVelocity = (target - m_vehicle->getPos()).getNormalized() * m_vehicle->getMaxSpeed();

    return desiredVelocity - m_vehicle->getVelocity();
}

Vector2D<float> SteeringBehaviors::flee(Vector2D<float> target) {
    if ((m_vehicle->getPos() - target).squareMagnitude() > m_panicDistanceSq) {
        return {0.0, 0.0};
    }

    Vector2D<float> desiredVelocity = (m_vehicle->getPos() - target).getNormalized() * m_vehicle->getMaxSpeed();

    return desiredVelocity - m_vehicle->getVelocity();
}

Vector2D<float> SteeringBehaviors::wander() {
    m_wanderTarget += Vector2D<float>(fRandomRange(-1, 1) * m_wanderJitter, fRandomRange(-1, 1) * m_wanderJitter);

    m_wanderTarget = m_wanderTarget.getNormalized();

    m_wanderTarget *= m_wanderRadius;

    Vector2D<float> targetLocal = m_wanderTarget + Vector2D<float>(m_wanderDistance, 0);

    Vector2D<float> targetWorld = pointToWorldSpace(targetLocal,
                                                     m_vehicle->getHeading(),
                                                     m_vehicle->getSide(),
                                                     m_vehicle->getPos());

    m_vehicle->m_wanderTarget = targetWorld;
    auto result = targetWorld - m_vehicle->getPos();

    // to make the movement more dynamic, otherwise wandering is very slow
    return result * 100.0;
}


