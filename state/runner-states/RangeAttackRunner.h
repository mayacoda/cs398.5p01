
#ifndef DZ04_RANGEATTACKRUNNER_H
#define DZ04_RANGEATTACKRUNNER_H


#include "../State.h"

class RangeAttackRunner : public State {
private:
    Character* m_enemy;
public:
    RangeAttackRunner(Character* m_enemy);

    void execute(Character* stateMachine) override;

    void enter(Character* stateMachine) override;

    void exit(Character* stateMachine) override;

};


#endif //DZ04_RANGEATTACKRUNNER_H
