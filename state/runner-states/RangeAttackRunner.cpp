
#include "RangeAttackRunner.h"
#include "WanderRunner.h"

RangeAttackRunner::RangeAttackRunner(Character* m_enemy) : m_enemy(m_enemy) {}

void RangeAttackRunner::execute(Character* stateMachine) {
    if (m_enemy->isDead()) {
        stateMachine->changeState(new WanderRunner());
        return;
    }

    if (stateMachine->getHealth() < m_enemy->getHealth() &&
        stateMachine->closeEnoughToAttackRanged(m_enemy)) {

        stateMachine->attackRanged(m_enemy->getPos());
    }
}
