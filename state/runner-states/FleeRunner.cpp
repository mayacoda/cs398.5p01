
#include "FleeRunner.h"
#include "WanderRunner.h"

FleeRunner::FleeRunner(Character* m_enemy) : m_enemy(m_enemy) {}

void FleeRunner::enter(Character* stateMachine) {
    stateMachine->setTarget(m_enemy);

    stateMachine->turnOnBehavior(SteeringBehaviors::fFlee);
    std::cout << *stateMachine << "enter flee runner" << std::endl;

    State::enter(stateMachine);
}

void FleeRunner::exit(Character* stateMachine) {
    stateMachine->setTarget(nullptr);
    stateMachine->turnOffBehavior(SteeringBehaviors::fFlee);
    std::cout << *stateMachine << "exit flee runner" << std::endl;

    State::exit(stateMachine);
}

void FleeRunner::execute(Character* stateMachine) {
    if (!m_enemy->canDetect(stateMachine)) {
        stateMachine->changeState(new WanderRunner());
    }

    State::execute(stateMachine);
}
