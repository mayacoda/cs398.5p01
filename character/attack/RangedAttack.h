
#ifndef DZ04_RANGEDATTACK_H
#define DZ04_RANGEDATTACK_H


#include "Attack.h"

class RangedAttack : public Attack {
public:
    RangedAttack(const Character* shooter, double range, double speed);

};


#endif //DZ04_RANGEDATTACK_H
