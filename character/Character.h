
#ifndef DZ04_VEHICLE_H
#define DZ04_VEHICLE_H

#include "../game-world/MovingEntity.h"
#include "SteeringBehaviors.h"
#include "../graphics/opengl_helpers.h"
#include "../map/GraphEdge.h"
#include "costFunctions.h"

class GameWorld;

class Character : public MovingEntity {
private:
    GameWorld        * m_world;
    SteeringBehaviors* m_steeringBehavior;

    Vector2D<double> m_steeringForce;

    double m_timeElapsed;

    double m_detectionBoxLength;

    void renderAids();

    std::vector<Character*> m_antagonists;

    Character* m_leader;

    Vector2D<double> m_offset;

    Vector2D<double> m_destination;

public:

    Color m_color;

    ~Character() {
        delete m_steeringBehavior;
    }

    Character(GameWorld* m_world,
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

    const Character* m_interposeTargetA;

    const Character* m_interposeTargetB;

    Vector2D<double> getHeading() const { return m_heading; }

    Vector2D<double> getSide() const { return m_side; }

    GameWorld* getWorld() const { return m_world; }

    double getDetectionBoxLength() const { return m_detectionBoxLength; }

    const double calculateMaxSpeed() const;

    std::vector<Character*> getAntagonists() const { return m_antagonists; }

    void addAntagonist(Character* a) { m_antagonists.push_back(a); }

    void setLeaderAndOffset(Character* l, Vector2D<double> v) {
        m_leader = l;
        m_offset = v;
    }

    Character* getLeader() const { return m_leader; }

    Vector2D<double> getOffset() const { return m_offset; }

    void setDestination(Vector2D<double> dest) { m_destination = dest; }

    Vector2D<double> getDestination() const { return m_destination; }

    void interposeVehicles(const Character* a, const Character* b) {
        m_interposeTargetA = a;
        m_interposeTargetB = b;
    }

    void turnOnBehavior(SteeringBehaviors::behaviorType behavior) {
        behavior == SteeringBehaviors::none ? m_steeringBehavior->turnAllOff() : m_steeringBehavior->turnOn(behavior);
    }

    void setPath(Path* path) { m_steeringBehavior->setPath(path); }

    typedef double (*fptr)(const GraphEdge&);

    fptr getCostFunction() {
        return basicCost;
    }

    void update(double timeElapsed);

    void render();

};


#endif //DZ04_VEHICLE_H
