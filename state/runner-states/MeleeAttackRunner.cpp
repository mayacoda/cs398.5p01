
#include "MeleeAttackRunner.h"
#include "WanderRunner.h"
#include "PursueRunner.h"

MeleeAttackRunner::MeleeAttackRunner(Character* m_enemy) : m_enemy(m_enemy) {}

void MeleeAttackRunner::execute(Character* stateMachine) {
    if (m_enemy->isDead()) {
        stateMachine->changeState(new WanderRunner());

    } else if (stateMachine->closeEnoughToAttackMelee(m_enemy)) {

        stateMachine->attackMelee(m_enemy->getPos());

    } else {
        stateMachine->changeState(new PursueRunner(m_enemy));
    }
}

void MeleeAttackRunner::enter(Character* stateMachine) {
    if (globals::debug) std::cout << *stateMachine << "enter melee attack runner " << *m_enemy << std::endl;
    State::enter(stateMachine);
}

void MeleeAttackRunner::exit(Character* stateMachine) {
    if (globals::debug) std::cout << *stateMachine << "exit melee attack runner " << *m_enemy << std::endl;
    State::exit(stateMachine);
}
