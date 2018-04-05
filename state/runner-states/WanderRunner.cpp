
#include "WanderRunner.h"
#include "FleeRunner.h"
#include "PursueRunner.h"

void WanderRunner::execute(Character* stateMachine) {
    State::execute(stateMachine);

    Character* enemy = stateMachine->seekEnemies();

    if (enemy != nullptr) {
        if (stateMachine->getHealthRatio() < .25) {
            stateMachine->changeState(new FleeRunner(enemy));
        } else {
            stateMachine->changeState(new PursueRunner(enemy));
        }


    }
}

void WanderRunner::enter(Character* stateMachine) {
    if (globals::debug) std::cout << *stateMachine << "enter wander runner" << std::endl;
    WanderState::enter(stateMachine);
}

void WanderRunner::exit(Character* stateMachine) {
    if (globals::debug) std::cout << *stateMachine << "exit wander runner" << std::endl;
    WanderState::exit(stateMachine);
}
