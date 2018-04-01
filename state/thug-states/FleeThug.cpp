
#include "FleeThug.h"
#include "WanderThug.h"

FleeThug::FleeThug(Character* m_enemy) : m_enemy(m_enemy) {}

void FleeThug::enter(Character* stateMachine) {
    std::cout << *stateMachine << "enter flee thug" << std::endl;

    stateMachine->setTarget(m_enemy);
    stateMachine->turnOnBehavior(SteeringBehaviors::fFlee);
    State::enter(stateMachine);
}

void FleeThug::exit(Character* stateMachine) {
    std::cout << *stateMachine << "exit flee thug" << std::endl;

    stateMachine->setTarget(nullptr);
    stateMachine->turnOffBehavior(SteeringBehaviors::fFlee);
    State::exit(stateMachine);
}

void FleeThug::execute(Character* stateMachine) {
    if (!m_enemy->closeEnoughToAttack(stateMachine)) {
        stateMachine->changeState(new WanderThug());
    }
    State::execute(stateMachine);
}
