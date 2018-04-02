
#include "RangedAttack.h"

RangedAttack::RangedAttack(const Character* shooter, double range, double speed) : Attack(shooter,
                                                                                          speed,
                                                                                          range,
                                                                                          5) {}
