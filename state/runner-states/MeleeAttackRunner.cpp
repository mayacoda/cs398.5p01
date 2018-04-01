
#include "MeleeAttackRunner.h"
#include "WanderRunner.h"

MeleeAttackRunner::MeleeAttackRunner(Character* m_enemy) : m_enemy(m_enemy) {}

void MeleeAttackRunner::execute(Character* stateMachine) {
    if (m_enemy->isDead()) {
        stateMachine->changeState(new WanderRunner());
        return;
    }

    if (stateMachine->getHealth() > m_enemy->getHealth() &&
        stateMachine->closeEnoughToAttackMelee(m_enemy)) {

        stateMachine->attackMelee(m_enemy->getPos());

    }
}
