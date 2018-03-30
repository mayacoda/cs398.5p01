
#include "WanderSneak.h"
#include "EvadeSneak.h"
#include "StalkSneak.h"
#include "AttackSneak.h"

void WanderSneak::enter(Character* stateMachine) {
    std::cout << "entering wanderSneak" << std::endl;
    stateMachine->turnOnBehavior(SteeringBehaviors::fWander);
}

void WanderSneak::exit(Character* stateMachine) {
    std::cout << "exiting wanderSneak" << std::endl;
    State::exit(stateMachine);
    stateMachine->turnOffBehavior(SteeringBehaviors::fWander);
}

void WanderSneak::execute(Character* stateMachine) {

    Character* enemy = stateMachine->seekEnemies();

    if (enemy != nullptr) {
        if (enemy->getHealth() > stateMachine->getHealth()) {

            stateMachine->changeState(new EvadeSneak(enemy));

        } else {
            if (stateMachine->closeEnoughToAttack(enemy)) {
                // if enemy can be attacked, do so
                stateMachine->changeState(new AttackSneak(enemy));
            } else {
                // start stalking enemy
                stateMachine->changeState(new StalkSneak(enemy));
            }
        }
    }
}
