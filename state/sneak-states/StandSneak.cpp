
#include "StandSneak.h"
#include "../../character/SteeringBehaviors.h"
#include "../../character/Character.h"
#include "EvadeSneak.h"

void StandSneak::enter(Character* stateMachine) {
    if (globals::debug) std::cout << *stateMachine << "enter stand sneak" << std::endl;

    stateMachine->setDestination(stateMachine->getPos());
    stateMachine->turnOnBehavior(SteeringBehaviors::fArrive);
    State::enter(stateMachine);
}

void StandSneak::exit(Character* stateMachine) {
    if (globals::debug) std::cout << *stateMachine << "exit stand sneak" << std::endl;

    State::exit(stateMachine);
}

void StandSneak::execute(Character* stateMachine) {

    Character* enemy = stateMachine->seekEnemies();

    if (enemy != nullptr) {
        if (enemy->getHealth() > stateMachine->getHealth()) {
            stateMachine->changeState(new EvadeSneak(enemy));
        } else {

            // start stalking enemy
        }
    }

    State::execute(stateMachine);
}

