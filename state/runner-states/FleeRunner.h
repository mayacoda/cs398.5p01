
#ifndef DZ04_FLEERUNNER_H
#define DZ04_FLEERUNNER_H


#include "../State.h"

class FleeRunner : public State {
private:
    Character* m_enemy;
public:
    FleeRunner(Character* m_enemy);

    void enter(Character* stateMachine) override;

    void exit(Character* stateMachine) override;

    void execute(Character* stateMachine) override;

};


#endif //DZ04_FLEERUNNER_H
