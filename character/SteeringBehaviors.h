
#ifndef DZ04_STEERINGBEHAVIOR_H
#define DZ04_STEERINGBEHAVIOR_H


#include <vector>
#include "../geometry/Vector2D.h"
#include "../map/Path.h"

class Character;

class SteeringBehaviors {
private:
    Character* m_vehicle;

    Vector2D<double> m_steeringForce;

    Vector2D<double> m_wanderTarget;

    double m_panicDistanceSq;

    double m_followPathDistanceSq;

    int m_flags;

public:
    enum behaviorType {
        none            = 0x00000,
        fSeek           = 0x00002,
        fFlee           = 0x00004,
        fArrive         = 0x00008,
        fWander         = 0x00010,
        fFollow_path    = 0x00020,
        fAvoid_obs      = 0x00040,
        fHide           = 0x00080,
        fOffset_pursuit = 0x00100,
        fInterpose      = 0x00200,
        fEvade          = 0x00400,
        fPursue         = 0x00800
    };

    Path* m_path;

    double m_wanderRadius;

    double m_wanderJitter;

    double m_wanderDistance;

    explicit SteeringBehaviors(Character* m_vehicle);

    void turnOn(behaviorType behavior) {
        m_flags |= behavior;
    }

    void turnOff(behaviorType behavior) {
        m_flags ^= behavior;
    }

    void turnAllOff() {
        m_flags = none;
    }

    bool isOn(behaviorType behavior) {
        return (m_flags & behavior) != 0;
    }

    void setPath(Path* p) { m_path = p; }

    Vector2D<double> calculate();

    Vector2D<double> seek(Vector2D<double> target);

    Vector2D<double> flee(Vector2D<double> target);

    Vector2D<double> evade(const Character* agent);

    Vector2D<double> arrive(Vector2D<double>);

    Vector2D<double> offsetPursuit(const Character* leader, Vector2D<double> offset);

    Vector2D<double> wander();

    Vector2D<double> followPath();

    Vector2D<double> avoidObstacles();

    Vector2D<double> hide();

    Vector2D<double> getHidingPosition(Vector2D<double> obsPos, double obsRadius, Vector2D<double> hunterPos);

    Vector2D<double> interpose(const Character* a, const Character* b);

    Vector2D<double> pursue(const Character* target);
};


#endif //DZ04_STEERINGBEHAVIOR_H
