
#include "SteeringBehaviors.h"
#include "Vehicle.h"
#include "geometry.h"
#include <iostream>

SteeringBehaviors::SteeringBehaviors(Vehicle *m_vehicle) : m_vehicle(m_vehicle),
                                                           m_steeringForce(Vector2D<double>(0.0, 0.0)),
                                                           m_wanderTarget(Vector2D<double>(0.0, 0.0)) {


    m_wanderRadius = 40;

    m_wanderJitter = 10;

    m_wanderDistance = 100;

    m_panicDistanceSq = 10000;
															   
	double theta = fRandomRange(-1, 1) * 2.0 * M_PI;  // range from -2pi to 2pi
    m_wanderTarget = Vector2D<double>(m_wanderRadius * cos(theta), m_wanderRadius * sin(theta));
}

Vector2D<double> SteeringBehaviors::calculate() {
    return wander();
}

Vector2D<double> SteeringBehaviors::seek(Vector2D<double> target) {
    Vector2D<double> desiredVelocity = (target - m_vehicle->getPos()).getNormalized() * m_vehicle->getMaxSpeed();
	 
    return desiredVelocity - m_vehicle->getVelocity();
}

Vector2D<double> SteeringBehaviors::flee(Vector2D<double> target) {
    if ((m_vehicle->getPos() - target).squareMagnitude() > m_panicDistanceSq) {
        return Vector2D<double>(0.0, 0.0);
    }

    Vector2D<double> desiredVelocity = (m_vehicle->getPos() - target).getNormalized() * m_vehicle->getMaxSpeed();

    return desiredVelocity - m_vehicle->getVelocity();
}

Vector2D<double> SteeringBehaviors::wander() {

    m_wanderTarget += Vector2D<double>(fRandomRange(-1, 1) * m_wanderJitter, fRandomRange(-1, 1) * m_wanderJitter);

    m_wanderTarget = m_wanderTarget.getNormalized();

    m_wanderTarget *= m_wanderRadius;

    Vector2D<double> targetLocal = m_wanderTarget + Vector2D<double>(m_wanderDistance, 0);

    Vector2D<double> targetWorld = pointToWorldSpace(targetLocal,
                                                     m_vehicle->getHeading(),
                                                     m_vehicle->getSide(),
                                                     m_vehicle->getPos());

    m_vehicle->m_wanderTarget = targetWorld;
    auto result = targetWorld - m_vehicle->getPos();

    return result;
}


