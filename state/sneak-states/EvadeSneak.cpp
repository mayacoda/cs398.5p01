
#include "EvadeSneak.h"
#include "../../character/Character.h"
#include "WanderSneak.h"
#include "StandSneak.h"

void EvadeSneak::enter(Character* stateMachine) {
    std::cout << "entering evade" << std::endl;

    stateMachine->setTarget(m_target);
    stateMachine->turnOnBehavior(SteeringBehaviors::fEvade);
}

void EvadeSneak::exit(Character* stateMachine) {
    std::cout << "exiting evade" << std::endl;

    stateMachine->setTarget(nullptr);
    stateMachine->turnOffBehavior(SteeringBehaviors::fEvade);

    State::exit(stateMachine);
}

void EvadeSneak::execute(Character* stateMachine) {

    if (stateMachine->hasEscaped()) {

        stateMachine->changeState(new StandSneak(stateMachine->getPos() + stateMachine->getHeading()));
    }

    State::execute(stateMachine);
}