
#ifndef DZ04_PROJECTILE_H
#define DZ04_PROJECTILE_H


#include "../../game-world/MovingEntity.h"
#include "../Character.h"

class Attack: public MovingEntity {
protected:
    double m_range;
public:
    Attack(const Character* shooter, double maxSpeed, double range);

    void update(double timeElapsed) override;

    void render() const override;
};


#endif //DZ04_PROJECTILE_H
