
#ifndef DZ04_FLEE_H
#define DZ04_FLEE_H


#include "../State.h"

class EvadeSneak : public State {
private:
    Character* m_target;
public:

    EvadeSneak(Character* target) : m_target(target) {};

    void enter(Character* stateMachine) override;

    void exit(Character* stateMachine) override;

    void execute(Character* stateMachine) override;
};


#endif //DZ04_FLEE_H
