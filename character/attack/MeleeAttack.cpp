
#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(const Character* shooter, double range, double speed) : Attack(shooter,
                                                                          speed,
                                                                          range,
                                                                          10) {}
