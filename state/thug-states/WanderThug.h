
#ifndef DZ04_WANDERTHUG_H
#define DZ04_WANDERTHUG_H


#include "../State.h"

class WanderThug : public State {
public:
    void enter(Character* stateMachine) override {
        std::cout << "entering wanderThug" << std::endl;
        State::enter(stateMachine);
    }

    void exit(Character* stateMachine) override {
        std::cout << "exiting wanderThug" << std::endl;
        State::exit(stateMachine);
    }

    void execute(Character* stateMachine) override {
        State::execute(stateMachine);
    }
};


#endif //DZ04_WANDERTHUG_H
