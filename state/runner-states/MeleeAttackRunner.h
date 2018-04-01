
#ifndef DZ04_MELEEATTACKRUNNER_H
#define DZ04_MELEEATTACKRUNNER_H


#include "../State.h"

class MeleeAttackRunner : public State {
private:
    Character* m_enemy;

public:
    MeleeAttackRunner(Character* m_enemy);

    void execute(Character* stateMachine) override;
};


#endif //DZ04_MELEEATTACKRUNNER_H
