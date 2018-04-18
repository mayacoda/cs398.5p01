
#ifndef DZ04_PROJECTILE_H
#define DZ04_PROJECTILE_H


#include "../../game-world/MovingEntity.h"
#include "../Character.h"

class GameWorld;

class Attack : public MovingEntity {
protected:
    Character* m_shooter;
    Character* m_victim;
    Vector2D<double> m_origin;
    GameWorld* m_world;

    double m_timeTillDeath;
    double m_damage;
    double m_range;

    bool   m_impacted;
    bool   m_dead;

    void countdown(double time);

public:
    Attack(Character* shooter, double maxSpeed, double range, double damage);

    void update(double timeElapsed) override;

    void render() const override;

    bool isDead() const { return m_dead; }

    void notify(Event e) override;
};


#endif //DZ04_PROJECTILE_H
