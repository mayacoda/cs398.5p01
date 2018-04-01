
#include "PursueRunner.h"
#include "FleeRunner.h"
#include "WanderRunner.h"
#include "MeleeAttackRunner.h"

PursueRunner::PursueRunner(Character* m_enemy) : m_enemy(m_enemy) {}

void PursueRunner::enter(Character* stateMachine) {
    std::cout << *stateMachine << "enter pursue runner" << std::endl;

    stateMachine->setTarget(m_enemy);
    stateMachine->turnOnBehavior(SteeringBehaviors::fSeek);
    State::enter(stateMachine);
}

void PursueRunner::exit(Character* stateMachine) {
    std::cout << *stateMachine << "exit pursue runner" << std::endl;

    stateMachine->setTarget(nullptr);
    stateMachine->turnOffBehavior(SteeringBehaviors::fSeek);
    State::exit(stateMachine);
}

void PursueRunner::execute(Character* stateMachine) {
    if (m_enemy->isDead()) {
        stateMachine->changeState(new WanderRunner());
        return;
    }

    if (stateMachine->getHealthRatio() < .25) {
        stateMachine->changeState(new FleeRunner(m_enemy));

    } else if (stateMachine->getHealth() > m_enemy->getHealth() &&
               stateMachine->closeEnoughToAttackMelee(m_enemy)) {

        stateMachine->attackMelee(m_enemy->getPos());

    } else if (stateMachine->getHealth() < m_enemy->getHealth() &&
               stateMachine->closeEnoughToAttackRanged(m_enemy)) {

        stateMachine->attackRanged(m_enemy->getPos());
    }

    State::execute(stateMachine);
}
