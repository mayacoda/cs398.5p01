
#ifndef DZ04_MELEEATTACK_H
#define DZ04_MELEEATTACK_H


#include "Attack.h"

class MeleeAttack : public Attack {
public:
    MeleeAttack(const Character* shooter, double range, double speed);
};


#endif //DZ04_MELEEATTACK_H
