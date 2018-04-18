#ifndef DZ04_VISIBILITYTRAP_H
#define DZ04_VISIBILITYTRAP_H

#include "Trap.h"

class VisibilityTrap : public Trap {
public:
    VisibilityTrap(GameWorld* world, const Vector2D<double> &pos) : Trap(world, pos) {
        m_type  = Trap::visibility;
        m_color = Color(0.8, 0.0, 0.2);
    }
};


#endif //DZ04_VISIBILITYTRAP_H
