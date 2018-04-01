
#ifndef DZ04_WANDERRUNNER_H
#define DZ04_WANDERRUNNER_H


#include "../WanderState.h"

class WanderRunner : public WanderState {

public:
    void execute(Character* stateMachine) override;

    void enter(Character* stateMachine) override;

    void exit(Character* stateMachine) override;
};


#endif //DZ04_WANDERRUNNER_H
