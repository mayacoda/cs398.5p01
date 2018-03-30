
#ifndef DZ04_STATE_H
#define DZ04_STATE_H

#include "../character/Character.h"

class State {
public:
    State() {};

    virtual ~State() {};

    virtual void enter(Character *stateMachine) {};

    virtual void exit(Character *stateMachine) {
        delete stateMachine->currentState;
    };

    virtual void execute(Character* stateMachine) {};
};


#endif //DZ04_STATE_H
