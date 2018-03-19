
#ifndef DZ04_VEHICLE_H
#define DZ04_VEHICLE_H

#include "MovingEntity.h"
#include "SteeringBehaviors.h"
#include "opengl_helpers.h"

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

    Vehicle* m_leader;

    Vector2D<double> m_offset;

    Vector2D<double> m_destination;

public:

    Color m_color;

    ~Vehicle() {
        delete m_steeringBehavior;
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

    const Vehicle* m_interposeTargetA;

    const Vehicle* m_interposeTargetB;

    Vector2D<double> getHeading() const { return m_heading; }

    Vector2D<double> getSide() const { return m_side; }

    GameWorld* getWorld() const { return m_world; }

    double getDetectionBoxLength() const { return m_detectionBoxLength; }

    const double getMaxSpeed() const { return m_maxSpeed; }

    std::vector<Vehicle*> getAntagonists() const { return m_antagonists; }

    void addAntagonist(Vehicle* a) { m_antagonists.push_back(a); }

    void setLeaderAndOffset(Vehicle* l, Vector2D<double> v) {
        m_leader = l;
        m_offset = v;
    }

    Vehicle* getLeader() const { return m_leader; }

    Vector2D<double> getOffset() const { return m_offset; }

    void setDestination(Vector2D<double> dest) { m_destination = dest; }

    Vector2D<double> getDestination() const { return m_destination; }

    void interposeVehicles(const Vehicle* a, const Vehicle* b) {
        m_interposeTargetA = a;
        m_interposeTargetB = b;
    }

    void turnOnBehavior(SteeringBehaviors::behaviorType behavior) {
        behavior == SteeringBehaviors::none ? m_steeringBehavior->turnAllOff() : m_steeringBehavior->turnOn(behavior);
    }

    void update(double timeElapsed);

    void render();

    void setPath(Path* path) { m_steeringBehavior->setPath(path); }
};


#endif //DZ04_VEHICLE_H
