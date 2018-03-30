#include <vector>

#include "SteeringBehaviors.h"
#include "Character.h"
#include "../geometry/geometry.h"
#include "../game-world/GameWorld.h"

SteeringBehaviors::SteeringBehaviors(Character* m_vehicle) : m_vehicle(m_vehicle),
                                                           m_steeringForce(Vector2D<double>(0.0, 0.0)),
                                                           m_wanderTarget(Vector2D<double>(0.0, 0.0)),
                                                           m_flags(0),
                                                           m_path() {


    m_wanderRadius = 10;

    m_wanderJitter = 1;

    m_wanderDistance = 200;

    m_panicDistanceSq = 10000;

    m_followPathDistanceSq = 1024;

    double theta = fRandomRange(-1, 1) * 2.0 * M_PI;  // range from -2pi to 2pi
    m_wanderTarget = Vector2D<double>(m_wanderRadius * cos(theta), m_wanderRadius * sin(theta));
}

Vector2D<double> SteeringBehaviors::calculate() {
    m_steeringForce.zero();

    if (isOn(fWander)) {
        m_steeringForce += wander();
    }

    if (isOn(fFollow_path)) {
        m_steeringForce += followPath();
    }

    if (isOn(fHide)) {
        m_steeringForce += hide();
    }

    if (isOn(fOffset_pursuit) && m_vehicle->getLeader()) {
        m_steeringForce += offsetPursuit(m_vehicle->getLeader(), m_vehicle->getOffset());
    }

    if (isOn(fArrive)) {
        m_steeringForce += arrive(m_vehicle->getDestination());
    }

    if (isOn(fAvoid_obs)) {
        m_steeringForce += avoidObstacles();
    }

    if (isOn(fInterpose)) {
        m_steeringForce += interpose(m_vehicle->interposeTargetA, m_vehicle->interposeTargetB);
    }

    if (isOn(fFlee) && m_vehicle->getTarget()) {
        m_steeringForce += flee(m_vehicle->getTarget()->getPos());
    }

    if (isOn(fSeek) && m_vehicle->getTarget()) {
        m_steeringForce += seek(m_vehicle->getTarget()->getPos());
    }

    if (isOn(fEvade) && m_vehicle->getTarget()) {
        m_steeringForce += evade(m_vehicle->getTarget());
    }

    return m_steeringForce;
}

Vector2D<double> SteeringBehaviors::seek(Vector2D<double> target) {
    Vector2D<double> desiredVelocity = (target - m_vehicle->getPos()).getNormalized() * m_vehicle->calculateMaxSpeed();

    return desiredVelocity - m_vehicle->getVelocity();
}

Vector2D<double> SteeringBehaviors::flee(Vector2D<double> target) {
    if ((m_vehicle->getPos() - target).squareMagnitude() > m_panicDistanceSq) {
        return Vector2D<double>(0.0, 0.0);
    }

    Vector2D<double> desiredVelocity = (m_vehicle->getPos() - target).getNormalized() * m_vehicle->calculateMaxSpeed();

    return desiredVelocity - m_vehicle->getVelocity();
}


Vector2D<double> SteeringBehaviors::arrive(Vector2D<double> target) {
    Vector2D<double> toTarget = target - m_vehicle->getPos();
    double           dist     = toTarget.magnitude();

    if (dist > 0) {
        const double deceleration = 3.0;

        double speed = dist / deceleration;

        speed = min(speed, m_vehicle->calculateMaxSpeed());

        Vector2D<double> desiredVelocity = toTarget * (speed / dist);

        return desiredVelocity - m_vehicle->getVelocity();
    }

    // turn off arriving behavior if already arrived and stopped at destination
    if (m_vehicle->getSpeed() < 0.0001) turnOff(fArrive);

    return Vector2D<double>(0, 0);

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

    m_vehicle->wanderTarget = targetWorld;
    Vector2D<double> result = targetWorld - m_vehicle->getPos();

    return result;
}

Vector2D<double> SteeringBehaviors::followPath() {
    if ((m_vehicle->getPos() - m_path->getCurrentPoint()).squareMagnitude() < m_followPathDistanceSq && !m_path->isLastPoint()) {

        m_path->setNextPoint();
    }

    if (!m_path->isLastPoint()) {
        return seek(m_path->getCurrentPoint());
    } else {
        return arrive(m_path->getCurrentPoint());
    }
}

Vector2D<double> SteeringBehaviors::avoidObstacles() {
    Vector2D<double> steeringForce = Vector2D<double>();

    double boxLength = m_vehicle->getDetectionBoxLength() +
                       (m_vehicle->getSpeed() / m_vehicle->calculateMaxSpeed()) *
                       m_vehicle->getDetectionBoxLength();

    std::vector<Obstacle*> allObstacles = m_vehicle->getWorld()->getObstacles();

    std::vector<Obstacle*>::iterator iterator = allObstacles.begin();
    Obstacle* o;
    Obstacle* closestObs                      = nullptr;
    double           closestX = std::numeric_limits<double>::infinity();
    Vector2D<double> localPosOfClosest;

    while (iterator != allObstacles.end()) {
        o = *iterator++;

        // filter by box length
        if (o->getPos().distanceTo(m_vehicle->getPos()) > boxLength) {
            // go on to the next obstacle
            continue;
        }

        Vector2D<double> obsLocal = pointToLocalSpace(o->getPos(),
                                                      m_vehicle->getHeading(),
                                                      m_vehicle->getSide(),
                                                      m_vehicle->getPos());

        // filter by x-coordinate
        if (obsLocal.x < 0) {
            // go on to the next obstacle
            continue;
        }

        // filter by intersection of detection box
        if (abs(obsLocal.y) - o->getBoundingRadius() > m_vehicle->getBoundingRadius()) {
            continue;
        }

        if (obsLocal.x < closestX) {
            closestObs        = o;
            localPosOfClosest = obsLocal;
            closestX          = obsLocal.x;
        }
    }

    if (closestObs) {
//        double multiplier = 1.0 + (boxLength - localPosOfClosest.x) / boxLength;
        double multiplier = 1.0;

        steeringForce.y = (closestObs->getBoundingRadius() - localPosOfClosest.y) * multiplier;

        double breakingWeight = 0.2;

        steeringForce.x = (closestObs->getBoundingRadius() - localPosOfClosest.x) * breakingWeight;

        return vectorToWorldSpace(steeringForce, m_vehicle->getHeading(), m_vehicle->getSide());
    }

    return Vector2D<double>();
}

Vector2D<double> SteeringBehaviors::hide() {
    Character* hunter = nullptr;
    double closestAntagonistDistance = std::numeric_limits<double>::infinity();

    // find the closest antagonist
    for (unsigned int i = 0; i < m_vehicle->getAntagonists().size(); i++) {
        Character* a = m_vehicle->getAntagonists().at(i);

        double distanceToA = m_vehicle->getPos().distanceTo(a->getPos());
        if (distanceToA < closestAntagonistDistance) {
            closestAntagonistDistance = distanceToA;
            hunter                    = a;
        }
    }


    if (hunter) {
        double           closestHidingSpotDistance = std::numeric_limits<double>::infinity();
        Vector2D<double> bestHidingSpot;

        const std::vector<Obstacle*>           &obstacles = m_vehicle->getWorld()->getObstacles();
        std::vector<Obstacle*>::const_iterator curObs     = obstacles.begin();
        std::vector<Obstacle*>::const_iterator closestObs;


        while (curObs != obstacles.end()) {
            Vector2D<double> hidingSpot = getHidingPosition((*curObs)->getPos(),
                                                            (*curObs)->getBoundingRadius(),
                                                            hunter->getPos());

            double dist = hidingSpot.distanceTo(m_vehicle->getPos());

            if (dist < closestHidingSpotDistance) {
                closestHidingSpotDistance = dist;
                bestHidingSpot            = hidingSpot;
                closestObs                = curObs;
            }

            ++curObs;
        }

        if (closestHidingSpotDistance == std::numeric_limits<double>::infinity()) {
            return evade(hunter);
        }

        return arrive(bestHidingSpot);
    }

    return Vector2D<double>();
}

Vector2D<double>
SteeringBehaviors::getHidingPosition(Vector2D<double> obsPos, double obsRadius, Vector2D<double> hunterPos) {
    double distAway = obsRadius + 30.0;

    Vector2D<double> toObstacle = (obsPos - hunterPos).getNormalized();

    const Vector2D<double> &d = toObstacle * distAway;

    return Vector2D<double>(d.x + obsPos.x, d.y + obsPos.y);
}

Vector2D<double> SteeringBehaviors::evade(const Character* agent) {
    Vector2D<double> toPursuer = agent->getPos() - m_vehicle->getPos();

    double lookAheadTime = toPursuer.magnitude() / (m_vehicle->calculateMaxSpeed() + agent->getSpeed());

    return flee(agent->getPos() + agent->getVelocity() * lookAheadTime);
}

Vector2D<double> SteeringBehaviors::offsetPursuit(const Character* leader, const Vector2D<double> offset) {
    Vector2D<double> worldOffsetPos = pointToWorldSpace(offset,
                                                        leader->getHeading(),
                                                        leader->getSide(),
                                                        leader->getPos());

    Vector2D<double> toOffset = worldOffsetPos - m_vehicle->getPos();

    double lookAheadTime = toOffset.magnitude() / (m_vehicle->calculateMaxSpeed() + leader->getSpeed());

    return arrive(worldOffsetPos + leader->getVelocity() * lookAheadTime);
}

Vector2D<double> SteeringBehaviors::interpose(const Character* a, const Character* b) {
    Vector2D<double> midpoint = (a->getPos() + b->getPos()) / 2.0;

    const double           timeToMidpoint = m_vehicle->getPos().distanceTo(midpoint) / m_vehicle->getSpeed();
    Vector2D<double> aPos           = a->getPos() + a->getVelocity() * timeToMidpoint;
    Vector2D<double> bPos           = b->getPos() + b->getVelocity() * timeToMidpoint;

    midpoint = (aPos + bPos) / 2.0;

    return arrive(midpoint);
}


