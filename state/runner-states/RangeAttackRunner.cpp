
#include "RangeAttackRunner.h"
#include "WanderRunner.h"
#include "PursueRunner.h"

RangeAttackRunner::RangeAttackRunner(Character* m_enemy) : m_enemy(m_enemy) {}

void RangeAttackRunner::execute(Character* stateMachine) {
    if (m_enemy->isDead()) {
        stateMachine->changeState(new WanderRunner());

    } else if (stateMachine->getHealth() < m_enemy->getHealth() &&
        stateMachine->closeEnoughToAttackRanged(m_enemy)) {

        stateMachine->attackRanged(m_enemy->getPos());

    } else {
        stateMachine->changeState(new PursueRunner(m_enemy));
    }
}
