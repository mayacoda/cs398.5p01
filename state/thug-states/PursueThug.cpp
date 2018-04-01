
#include "PursueThug.h"
#include "AttackThug.h"

PursueThug::PursueThug(Character* m_enemy) : m_enemy(m_enemy) {}

void PursueThug::enter(Character* stateMachine) {
    std::cout << *stateMachine << "enter pursue thug" << std::endl;

    stateMachine->setTarget(m_enemy);
    stateMachine->turnOnBehavior(SteeringBehaviors::fSeek);
    State::enter(stateMachine);
}

void PursueThug::exit(Character* stateMachine) {
    std::cout << *stateMachine << "exit pursue thug" << std::endl;

    stateMachine->setTarget(nullptr);
    stateMachine->turnOffBehavior(SteeringBehaviors::fSeek);
    State::exit(stateMachine);
}

void PursueThug::execute(Character* stateMachine) {
    if (stateMachine->closeEnoughToAttackMelee(m_enemy)) {
        stateMachine->changeState(new AttackThug(m_enemy));
    }
    State::execute(stateMachine);
}
