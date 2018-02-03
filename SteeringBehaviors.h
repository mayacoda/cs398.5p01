
#ifndef DZ04_STEERINGBEHAVIOR_H
#define DZ04_STEERINGBEHAVIOR_H


#include <vector>
#include "Vector2D.h"

class Vehicle;

class SteeringBehaviors {
private:
    Vehicle* m_vehicle;

    Vector2D<double> m_steeringForce;

    Vector2D<double> m_wanderTarget;

    double m_panicDistanceSq;

public:

    double m_wanderRadius;

    double m_wanderJitter;

    double m_wanderDistance;

    explicit SteeringBehaviors(Vehicle *m_vehicle);

    Vector2D<double> calculate();

    Vector2D<double> seek(Vector2D<double> target);

    Vector2D<double> flee(Vector2D<double> target);

    Vector2D<double> wander();

};


#endif //DZ04_STEERINGBEHAVIOR_H
