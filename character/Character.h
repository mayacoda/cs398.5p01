
#ifndef DZ04_VEHICLE_H
#define DZ04_VEHICLE_H

#include "../game-world/MovingEntity.h"
#include "SteeringBehaviors.h"
#include "../graphics/opengl_helpers.h"
#include "../map/GraphEdge.h"
#include "costFunctions.h"

class GameWorld;

class State;

class Character : public MovingEntity {
private:
    /**
     * Steering Behaviors
     */
    Character* m_leader;
    Character* m_target;
    Vector2D<double>        m_offset;
    Vector2D<double>        m_destination;
    std::vector<Character*> m_antagonists;
    Vector2D<double>        m_steeringForce;

    /**
     * Rendering
     */
    void renderAids();

    /**
     * Updating
     */
    double m_timeElapsed;

protected:
    GameWorld* m_world;

    double m_antagonistDetectionDistance;
    double m_detectionBoxLength;
    double m_health           = 100;
    double m_distanceToAttack;
    double m_timeLastAttacked = 0;
    double m_attackTimeout;
    double m_attackRange;

    SteeringBehaviors* m_steeringBehavior;

public:
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
              double attackRange,
              double attackTimeout);

    /**
     * Game play
     */

    double getHealth() const { return m_health; }

    /**
     * Rendering
     */
    Color m_color;

    /**
     * Steering Behaviors
     */
    Vector2D<double> wanderTarget;

    const Character* interposeTargetA;

    const Character* interposeTargetB;

    Vector2D<double> getHeading() const { return m_heading; }

    Vector2D<double> getSide() const { return m_side; }

    GameWorld* getWorld() const { return m_world; }

    double getDetectionBoxLength() const { return m_detectionBoxLength; }

    virtual const double calculateMaxSpeed() const { return m_maxSpeed; };

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
        interposeTargetA = a;
        interposeTargetB = b;
    }

    void setTarget(Character* t) { m_target = t; }

    Character* getTarget() const { return m_target; }

    void setPath(Path* path) { m_steeringBehavior->setPath(path); }

    typedef double (* fptr)(const GraphEdge &);

    virtual fptr getCostFunction() {
        return basicCost;
    }

    void turnOnBehavior(SteeringBehaviors::behaviorType behavior) {
        behavior == SteeringBehaviors::none ? m_steeringBehavior->turnAllOff() : m_steeringBehavior->turnOn(behavior);
    }

    void turnOffBehavior(SteeringBehaviors::behaviorType behavior) {
        m_steeringBehavior->turnOff(behavior);
    }

    virtual void turnOnDefaultBehavior() {
        m_steeringBehavior->turnOn(SteeringBehaviors::fAvoid_obs);
    }

    bool closeEnoughToAttack(Character* enemy) {
        return enemy->getPos().distanceTo(m_pos) <= m_distanceToAttack;
    }

    /**
     * Actions
     */
    Character* seekEnemies() const;

    virtual void attackRanged(Vector2D<double> target);

    virtual void attackMelee(Vector2D<double> target);

    /**
     * State
     */
    State* currentState;

    void changeState(State* newState);

    bool hasEscaped();

    /**
     * Game Loop
     */

    void update(double timeElapsed) override;

    void render() const override;
};


#endif //DZ04_VEHICLE_H
