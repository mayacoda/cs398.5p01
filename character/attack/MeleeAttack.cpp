
#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(Character* shooter, double range, double speed) : Attack(shooter,
                                                                                  speed,
                                                                                  range,
                                                                                  10) {}
