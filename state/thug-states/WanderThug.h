
#ifndef DZ04_WANDERTHUG_H
#define DZ04_WANDERTHUG_H


#include "../State.h"
#include "../WanderState.h"

class WanderThug : public WanderState {
public:

    void execute(Character* stateMachine) override;

    void enter(Character* stateMachine) override;

    void exit(Character* stateMachine) override;
};


#endif //DZ04_WANDERTHUG_H
