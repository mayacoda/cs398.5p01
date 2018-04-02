
#include "EvadeSneak.h"
#include "../../character/Character.h"
#include "WanderSneak.h"
#include "StandSneak.h"

void EvadeSneak::enter(Character* stateMachine) {
    std::cout << *stateMachine << "enter evade sneak" << std::endl;

    stateMachine->setTarget(m_target);
    stateMachine->turnOnBehavior(SteeringBehaviors::fEvade);
}

void EvadeSneak::exit(Character* stateMachine) {
    std::cout << *stateMachine << "exit evade sneak" << std::endl;

    stateMachine->setTarget(nullptr);
    stateMachine->turnOffBehavior(SteeringBehaviors::fEvade);

    State::exit(stateMachine);
}

void EvadeSneak::execute(Character* stateMachine) {

    if (stateMachine->hasEscaped()) {

        stateMachine->changeState(new WanderSneak());
    }

    State::execute(stateMachine);
}