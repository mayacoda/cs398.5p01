
#ifndef DZ04_PURSUERUNNER_H
#define DZ04_PURSUERUNNER_H


#include "../State.h"

class PursueRunner : public State {
private:
    Character* m_enemy;
public:
    PursueRunner(Character* m_enemy);

    void enter(Character* stateMachine) override;

    void exit(Character* stateMachine) override;

    void execute(Character* stateMachine) override;
};


#endif //DZ04_PURSUERUNNER_H
