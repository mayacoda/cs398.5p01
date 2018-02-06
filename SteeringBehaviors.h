
#ifndef DZ04_STEERINGBEHAVIOR_H
#define DZ04_STEERINGBEHAVIOR_H


#include <vector>
#include "Vector2D.h"

class Vehicle;

class SteeringBehaviors {
private:
    Vehicle* m_vehicle;

    Vector2D<float> m_steeringForce;

    Vector2D<float> m_wanderTarget;

    double m_panicDistanceSq = 10000;

public:

    double m_wanderRadius = 100;

    double m_wanderJitter = 20;

    double m_wanderDistance = 200;

    explicit SteeringBehaviors(Vehicle *m_vehicle);

    Vector2D<float> calculate();

    Vector2D<float> seek(Vector2D<float> target);

    Vector2D<float> flee(Vector2D<float> target);

    Vector2D<float> wander();

};


#endif //DZ04_STEERINGBEHAVIOR_H
