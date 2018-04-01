
#ifndef DZ04_WANDERSTATE_H
#define DZ04_WANDERSTATE_H


#include "State.h"

class WanderState : public State {
public:
    void enter(Character* stateMachine) override;

    void exit(Character* stateMachine) override;
};


#endif //DZ04_WANDERSTATE_H
