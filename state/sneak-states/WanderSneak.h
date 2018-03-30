
#ifndef DZ04_WANDER_H
#define DZ04_WANDER_H


#include "../State.h"

class WanderSneak : public State {
public:
    void enter(Character* stateMachine) override;

    void exit(Character* stateMachine) override;

    void execute(Character* stateMachine) override;
};


#endif //DZ04_WANDER_H
