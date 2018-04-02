
#ifndef DZ04_VEHICLE_H
#define DZ04_VEHICLE_H

#include "../game-world/MovingEntity.h"
#include "SteeringBehaviors.h"
#include "../graphics/opengl_helpers.h"
#include "../map/GraphEdge.h"
#include "costFunctions.h"

class GameWorld;

class Attack;

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
     * Updating
     */
    double m_timeElapsed;

protected:
    GameWorld* m_world;

    double m_antagonistDetectionDistance;
    double m_distanceToAttackRanged;
    double m_distanceToAttackMelee;
    double m_detectionBoxLength;
    double m_timeLastAttacked;
    double m_attackTimeout;
    double m_attackRange;
    double m_health;

    bool m_dead;
    bool m_autonomousTurning;

    /**
    * Rendering
    */
    void renderAids() const;

    SteeringBehaviors* m_steeringBehavior;

public:
    ~Character() {
        delete m_steeringBehavior;
        delete currentState;
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
              double meleeAttackDistance,
              double rangedAttackDistance,
              double attackTimeout);


    /**
     * Game play
     */

    double getHealth() const { return m_health; }

    double getHealthRatio() const { return m_health / 100.; }

    Character* seekEnemies() const;

    virtual void attackRanged(Vector2D<double> target);

    virtual void attackMelee(Vector2D<double> target);

    void takeDamage(double damage) {
        m_health -= damage;
        std::cout << "[" << getId() << "] health is: " << m_health << std::endl;

        if (m_health <= 0) {
            m_dead = true;
        }
    }

    bool closeEnoughToAttackMelee(Character* enemy) {
        return m_distanceToAttackMelee > 0 &&
               enemy->getPos().squareDistanceTo(m_pos) <= m_distanceToAttackMelee * m_distanceToAttackMelee;
    }

    bool closeEnoughToAttackRanged(Character* enemy) {
        return m_distanceToAttackRanged > 0 &&
               enemy->getPos().squareDistanceTo(m_pos) <= m_distanceToAttackRanged * m_distanceToAttackRanged;
    }

    bool closeEnoughToAttack(Character* enemy) {
        return closeEnoughToAttackRanged(enemy) || closeEnoughToAttackMelee(enemy);
    }


    bool isDead() const { return m_dead; }

    bool canDetect(Character* enemy);

    bool hasEscaped();

    void setAutonomousTurning(bool turn) { m_autonomousTurning = turn; }

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

    void turnToFace(Vector2D<double> target);

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

    virtual costFn getCostFunction() {
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

    /**
     * State
     */
    State* currentState;

    void changeState(State* newState);

    /**
     * Game Loop
     */

    void update(double timeElapsed) override;

    void render() const override;
};


#endif //DZ04_VEHICLE_H
