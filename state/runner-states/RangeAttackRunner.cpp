
#include "RangeAttackRunner.h"
#include "WanderRunner.h"
#include "PursueRunner.h"

RangeAttackRunner::RangeAttackRunner(Character* m_enemy) : m_enemy(m_enemy) {}

void RangeAttackRunner::enter(Character* stateMachine) {
    std::cout << *stateMachine << "enter range attack runner " << *m_enemy << std::endl;
    State::enter(stateMachine);
}

void RangeAttackRunner::exit(Character* stateMachine) {
    std::cout << *stateMachine << "exit range attack runner " << *m_enemy << std::endl;
    State::exit(stateMachine);
}

void RangeAttackRunner::execute(Character* stateMachine) {
    if (m_enemy->isDead()) {
        stateMachine->changeState(new WanderRunner());

    } else if (stateMachine->closeEnoughToAttackRanged(m_enemy)) {

        stateMachine->attackRanged(m_enemy->getPos());

    } else {
        stateMachine->changeState(new PursueRunner(m_enemy));
    }
}
