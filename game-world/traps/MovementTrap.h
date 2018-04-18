
#ifndef DZ04_MOVEMENTTRAP_H
#define DZ04_MOVEMENTTRAP_H


#include "Trap.h"

class MovementTrap : public Trap {

public:
    MovementTrap(GameWorld* world, const Vector2D<double> &pos) : Trap(world, pos) {
        m_type  = Trap::movement;
        m_color = Color(0, 0.2, 0.8);
    };

};


#endif //DZ04_MOVEMENTTRAP_H
