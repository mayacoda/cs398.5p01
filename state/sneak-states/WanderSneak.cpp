
#include "WanderSneak.h"
#include "EvadeSneak.h"
#include "StalkSneak.h"
#include "AttackSneak.h"

void WanderSneak::execute(Character* stateMachine) {

    Character* enemy = stateMachine->seekEnemies();

    if (enemy != nullptr) {
        if (enemy->getHealth() > stateMachine->getHealth()) {

            stateMachine->changeState(new EvadeSneak(enemy));

        } else {
            if (stateMachine->closeEnoughToAttackRanged(enemy)) {
                // if enemy can be attacked, do so
                stateMachine->changeState(new AttackSneak(enemy));
            } else {
                // start stalking enemy
                stateMachine->changeState(new StalkSneak(enemy));
            }
        }
    }
}

void WanderSneak::enter(Character* stateMachine) {
    std::cout << *stateMachine << "enter wander sneak" << std::endl;

    WanderState::enter(stateMachine);
}

void WanderSneak::exit(Character* stateMachine) {
    std::cout << *stateMachine << "exit wander sneak" << std::endl;

    WanderState::exit(stateMachine);
}
