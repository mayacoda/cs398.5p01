
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

    double m_panicDistanceSq = 10000;

public:

    double m_wanderRadius = 100;

    double m_wanderJitter = 20;

    double m_wanderDistance = 200;

    explicit SteeringBehaviors(Vehicle *m_vehicle);

    Vector2D<double> calculate();

    Vector2D<double> seek(Vector2D<double> target);

    Vector2D<double> flee(Vector2D<double> target);

    Vector2D<double> wander();

};


#endif //DZ04_STEERINGBEHAVIOR_H
