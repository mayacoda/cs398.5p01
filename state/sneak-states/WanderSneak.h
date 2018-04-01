
#ifndef DZ04_WANDER_H
#define DZ04_WANDER_H


#include "../State.h"
#include "../WanderState.h"

class WanderSneak : public WanderState {
public:
    void execute(Character* stateMachine) override;
};


#endif //DZ04_WANDER_H
