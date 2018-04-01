
#include "AttackThug.h"
#include "WanderThug.h"
#include "FleeThug.h"
#include "PursueThug.h"

AttackThug::AttackThug(Character* m_enemy) : m_enemy(m_enemy) {}

void AttackThug::execute(Character* stateMachine) {
    // opponent has been defeated
    if (m_enemy->isDead()) {
        stateMachine->changeState(new WanderThug());

    } else if (stateMachine->getHealthRatio() <= .25) {

        stateMachine->changeState(new FleeThug(m_enemy));
    } else {

        if (!stateMachine->closeEnoughToAttack(m_enemy)) {
            stateMachine->changeState(new PursueThug(m_enemy));
        } else {
            stateMachine->attackMelee(m_enemy->getPos());
        }
    }

    State::execute(stateMachine);
}
