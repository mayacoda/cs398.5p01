
#include "EvadeSneak.h"
#include "../../character/Character.h"
#include "WanderSneak.h"
#include "StandSneak.h"

void EvadeSneak::enter(Character* stateMachine) {
    if (globals::debug) std::cout << *stateMachine << "enter evade sneak" << std::endl;

    stateMachine->setTarget(m_target);
    stateMachine->turnOnBehavior(SteeringBehaviors::fEvade);
}

void EvadeSneak::exit(Character* stateMachine) {
    if (globals::debug) std::cout << *stateMachine << "exit evade sneak" << std::endl;

    stateMachine->setTarget(nullptr);
    stateMachine->turnOffBehavior(SteeringBehaviors::fEvade);

    State::exit(stateMachine);
}

void EvadeSneak::execute(Character* stateMachine) {
    static int escaped = 0;

    if (!m_target->canDetect(stateMachine)) {
        escaped++;
        if (escaped > 1000) {
            escaped = 0;
            stateMachine->changeState(new WanderSneak());
        }
    } else {
        escaped = 0;
    }

    State::execute(stateMachine);
}