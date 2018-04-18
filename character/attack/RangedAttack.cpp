
#include "RangedAttack.h"

RangedAttack::RangedAttack(Character* shooter, double range, double speed) : Attack(shooter,
                                                                                    speed,
                                                                                    range,
                                                                                    5) {}
