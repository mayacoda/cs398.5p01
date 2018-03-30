
#ifndef DZ04_NOSTATE_H
#define DZ04_NOSTATE_H


#include "../State.h"
#include "../../geometry/Vector2D.h"

class StandSneak : public State {
private:
    Vector2D<double> m_dest;

public:

    StandSneak(Vector2D<double> dest) : m_dest(dest) {};

    void enter(Character* stateMachine) override;

    void exit(Character* stateMachine) override;

    void execute(Character* stateMachine) override;
};


#endif //DZ04_NOSTATE_H
