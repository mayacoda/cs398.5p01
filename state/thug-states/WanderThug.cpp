
#include "WanderThug.h"
#include "PursueThug.h"
#include "AttackThug.h"

void WanderThug::execute(Character* stateMachine) {

    Character* enemy = stateMachine->seekEnemies();

    // detected an enemy in the field of view
    if (enemy != nullptr) {
        // thug will only worry about health if he's attacking
        if (stateMachine->closeEnoughToAttackMelee(enemy)) {
            stateMachine->changeState(new AttackThug(enemy));

        } else {
            stateMachine->changeState(new PursueThug(enemy));
        }
    }

    State::execute(stateMachine);
}

void WanderThug::enter(Character* stateMachine) {
    std::cout << *stateMachine << "enter wander thug" << std::endl;

    WanderState::enter(stateMachine);
}

void WanderThug::exit(Character* stateMachine) {
    std::cout << *stateMachine << "exit wander thug" << std::endl;

    WanderState::exit(stateMachine);
}