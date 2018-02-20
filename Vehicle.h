
#ifndef DZ04_VEHICLE_H
#define DZ04_VEHICLE_H

#include "MovingEntity.h"
#include "SteeringBehaviors.h"

class GameWorld;

class Vehicle : public MovingEntity {
private:
    GameWorld        * m_world;
    SteeringBehaviors* m_steeringBehavior;

    Vector2D<double> m_steeringForce;

    double m_timeElapsed;

    double m_detectionBoxLength;

    void renderAids();

    std::vector<Vehicle*> m_antagonists;

public:

    struct Color {
        float r;
        float g;
        float b;

        Color(float r, float g, float b) : r(r), g(g), b(b) {}
    };

    Color m_color;

    ~Vehicle() {
        delete &m_world;
        delete &m_steeringBehavior;
    }

    Vehicle(GameWorld* m_world,
            const Vector2D<double> &pos,
            const Vector2D<double> &scale,
            const Vector2D<double> &m_velocity,
            const Vector2D<double> &m_heading,
            const Vector2D<double> &m_side,
            double m_mass,
            double m_maxSpeed,
            double m_maxForce,
            double m_maxTurnRate);

    Vector2D<double> m_wanderTarget;

    Vector2D<double> getHeading() { return m_heading; }

    Vector2D<double> getSide() { return m_side; }

    GameWorld* getWorld() { return m_world; }

    double getDetectionBoxLength() { return m_detectionBoxLength; }

    const double getMaxSpeed() { return m_maxSpeed; }

    std::vector<Vehicle*> getAntagonists() { return m_antagonists; }

    void addAntagonist(Vehicle* a) { m_antagonists.push_back(a); }

    void turnOnBehavior(SteeringBehaviors::behaviorType behavior) {
        m_steeringBehavior->turnOn(behavior);
    }

    void update(double timeElapsed);

    void render();
};


#endif //DZ04_VEHICLE_H
